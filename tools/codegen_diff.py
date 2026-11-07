#!/usr/bin/env python3
"""cl500 codegen-vs-EXPECT pass (C5000 CGT 4.2.0, -v548 -O2).

For each src/rom6/**/*.c: compile with cl500, extract .text words via
ofd500 --obj_display=rawdata, diff against the file's EXPECT word list.
Writes build/codegen.json: per-file {origin, expect_n, got_n, match,
note}. MATCH means byte-identical codegen: the paired .asm is then
redundant (deletion is a separate, reviewed step -- this tool only
reports). Requires ~/ti/c5400_4.2.0/bin on PATH (or edit CGT_BIN).
"""
import json
import os
import re
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "src", "rom6")
CGT_BIN = os.path.expanduser("~/ti/c5400_4.2.0/bin")
CL500 = os.path.join(CGT_BIN, "cl500")
OFD500 = os.path.join(CGT_BIN, "ofd500")

ENV = dict(os.environ)
ENV["PATH"] = CGT_BIN + os.pathsep + ENV.get("PATH", "")


def parse_c(path):
    txt = open(path).read()
    mo = re.search(r"ORIGIN\s+0x([0-9A-Fa-f]+)", txt)
    me = re.search(r"EXPECT:\s*([0-9A-Fa-f ]+)", txt)
    if not (mo and me):
        return None, None
    return int(mo.group(1), 16), me.group(1).split()


def compile_c(src_path, workdir):
    base = os.path.splitext(os.path.basename(src_path))[0]
    sub = os.path.join(workdir, base)
    os.makedirs(sub, exist_ok=True)
    p = subprocess.run(
        [CL500, "-v548", "-O2", "-c", src_path],
        cwd=sub, env=ENV, capture_output=True, text=True, timeout=120)
    obj = os.path.join(sub, base + ".obj")
    if not os.path.exists(obj):
        return None, (p.stdout + p.stderr)[-600:]
    return obj, ""


def text_words(obj):
    p = subprocess.run(
        [OFD500, "--obj_display=rawdata", obj],
        env=ENV, capture_output=True, text=True, timeout=60)
    lines = p.stdout.splitlines()
    hx = []
    in_text = False
    for ln in lines:
        if ln.startswith(' Raw Data for Section ".text"'):
            in_text = True
            continue
        if in_text:
            if ln.startswith(" Raw Data for Section"):
                break
            if not ln.strip():
                if hx:
                    break
                continue
            parts = ln.split()
            for tok in parts[1:]:
                if re.fullmatch(r"[0-9a-fA-F]{2}", tok):
                    hx.append(tok)
                else:
                    break  # ASCII gutter
    if not hx or len(hx) % 2:
        return None
    return [int(hx[i + 1] + hx[i], 16) for i in range(0, len(hx), 2)]


def main():
    only = sys.argv[1:]  # optional basename filters
    files = []
    for dp, _, fns in os.walk(SRC):
        for fn in sorted(fns):
            if fn.endswith(".c") and (not only or fn in only or
                                      os.path.splitext(fn)[0] in only):
                files.append(os.path.join(dp, fn))
    out = {"tool": "cl500 -v548 -O2 (C5400 CGT 4.2.0)", "files": {}}
    with tempfile.TemporaryDirectory(prefix="codegen_") as td:
        for i, fp in enumerate(files):
            rel = os.path.relpath(fp, SRC)
            org, exp = parse_c(fp)
            if org is None:
                out["files"][rel] = {"match": False,
                                     "note": "no ORIGIN/EXPECT"}
                continue
            obj, err = compile_c(fp, td)
            if obj is None:
                out["files"][rel] = {"match": False,
                                     "note": "cl500 fail: " + err.strip()
                                     .replace("\n", " | ")[-200:]}
                continue
            got = text_words(obj)
            if got is None:
                out["files"][rel] = {"match": False, "scope": "data",
                                     "note": "data-only (const/table), "
                                     "no .text in obj"}
                continue
            exp_u = [w.upper() for w in exp]
            got_u = ["%04X" % w for w in got]
            match = (exp_u == got_u)
            rec = {"origin": "0x%04X" % org, "expect_n": len(exp_u),
                   "got_n": len(got_u), "match": match}
            if not match:
                n = next((k for k, (a, b) in
                          enumerate(zip(exp_u, got_u)) if a != b), -1)
                rec["first_diff"] = n
                rec["got_head"] = " ".join(got_u[:12])
            out["files"][rel] = rec
            if (i + 1) % 50 == 0:
                print(f"... {i + 1}/{len(files)}", flush=True)
    os.makedirs(os.path.join(ROOT, "build"), exist_ok=True)
    jp = os.path.join(ROOT, "build", "codegen.json")
    if os.path.exists(jp):
        try:
            prev = json.load(open(jp))["files"]
        except (OSError, ValueError, KeyError):
            prev = {}
        prev.update(out["files"])
        out["files"] = prev
        out["tool"] = "cl500 -v548 -O2 (C5400 CGT 4.2.0)"
    json.dump(out, open(jp, "w"), indent=1)
    n_ok = sum(1 for r in out["files"].values() if r.get("match"))
    n_cl = sum(1 for r in out["files"].values()
               if r.get("note", "").startswith("cl500 fail"))
    print(f"codegen: {n_ok} MATCH / {len(out['files'])} files, "
          f"{n_cl} compile failures -> {jp}")


if __name__ == "__main__":
    main()
