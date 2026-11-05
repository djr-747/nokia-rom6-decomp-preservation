#!/usr/bin/env python3
"""Disassemble a LEAD C54x program image with correct big-endian handling.

The tic54x BFD target is hardwired little-endian, so every 16-bit word is
byte-swapped into a temp file before objdump runs (the LE-vs-BE trap that
poisoned early block disassemblies). The BFD is word-addressed, hence
--adjust-vma=<base> yields true DSP word addresses.

Usage:
    python3 tools/disasm_c54x.py --rom rom6 [--image images/rom6-program.be16]
        [--objdump ../nokia-dct3-emu/build/tic54x-objdump]
        [--regions vectors,branch,prom] [--out build/rom6]

Regions (word addresses, per docs/01-memory-map.md):
    vectors  FF80-FFFF   reset + interrupt vector table
    branch   FD00-FF7F   PROM branch table
    prom     2800-B000   low PROM routines (superloop, ISRs)
    drom     B000-FD00   data-ROM view (tables/code; objdump reads words)
    full     0000-FFFF   whole program space (large)
"""
import argparse
import os
import re
import shutil
import subprocess
import sys
import tempfile

REGIONS = {
    "rom6": {
        "vectors": (0xFF80, 0xFFFF),
        "branch": (0xFD00, 0xFF7F),
        "prom": (0x2800, 0xB000),
        "drom": (0xB000, 0xFD00),
        "full": (0x0000, 0xFFFF),
    },
}
REGIONS["rom4"] = dict(REGIONS["rom6"])
REGIONS["rom3"] = dict(REGIONS["rom6"])
REGIONS["rom5"] = dict(REGIONS["rom6"])

DEFAULT_IMAGE = {"rom6": "images/rom6-program.be16", "rom4": "images/rom4-program.be16"}


def find_objdump(hint):
    cands = [hint, shutil.which("tic54x-objdump") or ""]
    for c in cands:
        if c and os.path.exists(c):
            try:
                if "c54x" in subprocess.run(
                    [c, "--info"], capture_output=True, text=True
                ).stdout:
                    return c
            except Exception:
                pass
    sys.exit("no tic54x-capable objdump; pass --objdump=... (see emulator tools/dsp/disasm.sh)")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--rom", default="rom6")
    ap.add_argument("--image", default=None)
    ap.add_argument("--objdump", default="")
    ap.add_argument("--regions", default="vectors,branch,prom")
    ap.add_argument("--out", default=None)
    a = ap.parse_args()

    if a.rom not in REGIONS:
        sys.exit(f"unknown rom: {a.rom}")
    image = a.image or DEFAULT_IMAGE.get(a.rom)
    if not image or not os.path.exists(image):
        sys.exit(f"image not found: {image} (bring your own; see docs/03-image-catalog.md)")
    if a.rom in ("rom3", "rom5"):
        sys.exit(f"{a.rom} is an unsupported slot with no catalogued image.")

    od = find_objdump(a.objdump)
    out = a.out or os.path.join("build", a.rom)
    os.makedirs(out, exist_ok=True)

    raw = open(image, "rb").read()
    if len(raw) % 2:
        sys.exit("odd-length image; C54x images are whole 16-bit words")
    nwords = len(raw) // 2
    le = bytearray(len(raw))
    for i in range(0, len(raw), 2):
        le[i], le[i + 1] = raw[i + 1], raw[i]
    tmp = tempfile.NamedTemporaryFile(delete=False, suffix=".le16")
    tmp.write(le)
    tmp.close()

    for name in a.regions.split(","):
        name = name.strip()
        lo, hi = REGIONS[a.rom][name]
        lo = max(lo, 0)
        hi = min(hi, nwords - 1)
        dest = os.path.join(out, f"{name}.lst")
        p = subprocess.run(
            [od, "-D", "-b", "binary", "-m", "tic54x", "-EL",
             f"--adjust-vma=0x0", tmp.name],
            capture_output=True, text=True,
        )
        kept = []
        for ln in p.stdout.splitlines():
            m = re.match(r"\s+([0-9a-f]+):", ln)
            if m and lo <= int(m.group(1), 16) <= hi:
                kept.append(ln)
        with open(dest, "w") as f:
            f.write(f"# {a.rom} region {name} words 0x{lo:04X}-0x{hi:04X}\n")
            f.write(f"# source image bytes {len(raw)} ({nwords} words), BE->LE swapped for tic54x BFD\n")
            f.write("\n".join(kept) + "\n")
        print(f"wrote {dest} ({len(kept)} lines)")
    os.unlink(tmp.name)


if __name__ == "__main__":
    main()
