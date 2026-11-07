#!/usr/bin/env python3
"""Recombine checked-in asm sources and byte-compare against the ROM image.

Each src/asm/<rom>/NNN_name.asm carries `; ORIGIN 0xXXXX`. The file is
assembled with tic54x-as (TI C54x COFF, little-endian words), flattened with
tic54x-objcopy -O binary, byte-swapped to big-endian, and compared word for
word with the loader image slice at ORIGIN. Any DIFF fails the run.

Toolchain: tools/build_tic54x_as.sh (binutils 2.42 --target=tic54x-coff).
Override: TIC54X_AS / TIC54X_OBJCOPY env, --image for the BE16 loader image.

Usage:
    python3 tools/recombine.py --rom rom6 [--src src/asm/rom6]
"""
import argparse
import os
import re
import shutil
import subprocess
import sys
import tempfile

IMAGES = {"rom6": "../nokia-dct3-emu/firmware/dsp/rom6/program.be16"}


def tool(name, env, default):
    p = os.environ.get(env) or shutil.which(default) or shutil.which(name)
    if p and os.path.exists(p):
        return p
    sys.exit(f"missing {name}: run tools/build_tic54x_as.sh or set {env}=...")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--rom", default="rom6")
    ap.add_argument("--src", default=None)
    ap.add_argument("--image", default=None)
    ap.add_argument("--filter", default=None,
                    help="only verify modules whose path contains this substring")
    a = ap.parse_args()
    flt = a.filter
    src = a.src or os.path.join("src", a.rom)
    img = a.image or IMAGES[a.rom]
    as_ = tool("assembler", "TIC54X_AS", "tic54x-as")
    oc = tool("objcopy", "TIC54X_OBJCOPY", "tic54x-objcopy")
    rom = open(img, "rb").read()
    files = []
    for dp, _, fns in os.walk(src):
        files += [os.path.join(dp, f) for f in fns if f.endswith(".asm")]
    files.sort()
    if flt is not None:
        files = [f for f in files if flt in f]
    if not files:
        sys.exit(f"no .asm modules under {src}")
    matched, matched_info, failed = 0, [], []
    with tempfile.TemporaryDirectory() as td:
        for f in files:
            rel = os.path.relpath(f, src)
            txt = open(f).read()
            m = re.search(r";\s*ORIGIN\s+0x([0-9A-Fa-f]+)", txt)
            if not m:
                failed.append((rel, "no ORIGIN"))
                continue
            org = int(m.group(1), 16)
            tag = rel.replace(os.sep, "_")
            asm, obj, out = (os.path.join(td, tag + s) for s in (".s", ".o", ".bin"))
            open(asm, "w").write(txt)
            # -w: warnings (e.g. *+ARx read) are noise; the LE->BE
            # byte-compare below is the real gate.
            r = subprocess.run([as_, "-w", "-mfar-mode", asm, "-o", obj],
                               capture_output=True, text=True)
            if r.returncode:
                tail = " | ".join(r.stderr.strip().splitlines()[-30:])
                failed.append((rel, "as: " + tail))
                continue
            r = subprocess.run([oc, "-O", "binary", obj, out], capture_output=True, text=True)
            if r.returncode:
                failed.append((rel, "objcopy: " + r.stderr.strip()))
                continue
            le = open(out, "rb").read()
            if not le:
                failed.append((rel, "empty module (vacuous match rejected)"))
                continue
            be = b"".join(le[i + 1 : i + 2] + le[i : i + 1] for i in range(0, len(le), 2))
            ref = rom[2 * org : 2 * org + len(be)]
            if be == ref:
                print(f"MATCH {rel} origin=0x{org:04X} words={len(be)//2}")
                matched += len(be) // 2
                matched_info.append((rel, org, len(be) // 2))
            else:
                where = next(i for i, (x, y) in enumerate(zip(be, ref)) if x != y)
                exp = int.from_bytes(ref[where & ~1 : (where & ~1) + 2], "big")
                got = int.from_bytes(be[where & ~1 : (where & ~1) + 2], "big")
                failed.append((rel, f"DIFF word 0x{org + (where//2):04X} rom={exp:04X} got={got:04X}"))
    print(f"recombine: {len(files)-len(failed)}/{len(files)} modules MATCH, {matched} words")
    for f, why in failed:
        print(f"FAIL {f}: {why}")
    if flt is None:
        import json
        os.makedirs("build", exist_ok=True)
        man = {"modules": [{"file": f, "origin": o, "words": w}
                            for f, o, w in matched_info]}
        man["total_words"] = matched
        json.dump(man, open("build/recombine.json", "w"), indent=1)
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
