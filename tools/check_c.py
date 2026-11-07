#!/usr/bin/env python3
"""Bind C intent sources to ROM ground truth.

Each src/**/*.c carries `ORIGIN 0xXXXX` and an `EXPECT:` word list in its
header comment. This checker compares those words to the loader image slice.
It does NOT verify compiler codegen (no cl500 here); it proves the C file
specifies the same bytes the verified .asm produces. Skips cleanly when the
proprietary image is absent (public CI without images).
"""
import json
import os
import re
import sys

IMAGES = {"rom6": "../nokia-dct3-emu/firmware/dsp/rom6/program.be16"}


def main():
    rom_name = "rom6"
    img = IMAGES[rom_name]
    if not os.path.exists(img):
        print("check_c: SKIP (no loader image)")
        return 0
    rom = open(img, "rb").read()
    n_ok, n_fail = 0, 0
    spans = []
    for dp, _, fns in os.walk(os.path.join("src", rom_name)):
        for fn in sorted(fns):
            if not fn.endswith(".c"):
                continue
            p = os.path.join(dp, fn)
            txt = open(p).read()
            mo = re.search(r"ORIGIN\s+0x([0-9A-Fa-f]+)", txt)
            me = re.search(r"EXPECT:\s*([0-9A-Fa-f ]+)", txt)
            rel = os.path.relpath(p, os.path.join("src", rom_name))
            if not (mo and me):
                print(f"FAIL {rel}: missing ORIGIN/EXPECT");
                n_fail += 1
                continue
            org = int(mo.group(1), 16)
            exp = [int(w, 16) for w in me.group(1).split()]
            spans.append((rel, org, len(exp)))
            asm_mo = re.search(r"Verified encoding:\s*(\S+?)\s*\(recombine", txt)
            if asm_mo and os.path.exists(asm_mo.group(1)):
                pass  # asm path: ROM-compare below
            elif re.search(r"Codegen:\s*cl500[^\n]*MATCH", txt):
                try:
                    cg = json.load(open(os.path.join("build",
                                                     "codegen.json")))
                    rec = cg["files"].get(rel, {})
                except (OSError, ValueError, KeyError):
                    rec = {}
                if not (rec.get("match") and rec.get("origin")
                        == "0x%04X" % org):
                    print(f"FAIL {rel}: codegen MATCH claim not in "
                          f"build/codegen.json")
                    n_fail += 1
                    continue
            else:
                print(f"FAIL {rel}: stated asm span missing "
                      f"({asm_mo.group(1) if asm_mo else 'none'})")
                n_fail += 1
                continue
            got = [int.from_bytes(rom[2 * org + 2 * i:2 * org + 2 * i + 2], "big")
                   for i in range(len(exp))]
            if got == exp:
                print(f"OK {rel} origin=0x{org:04X} words={len(exp)}")
                n_ok += 1
            else:
                bad = next(i for i, (x, y) in enumerate(zip(exp, got)) if x != y)
                print(f"FAIL {rel}: word 0x{org + bad:04X} expect={exp[bad]:04X} rom={got[bad]:04X}")
                n_fail += 1
    for i, (r1, o1, n1) in enumerate(spans):
        for r2, o2, n2 in spans[i + 1:]:
            lo, hi = max(o1, o2), min(o1 + n1, o2 + n2)
            if hi - lo < 2:
                continue
            print(f"FAIL overlap: {r1} [0x{o1:04X}+{n1}] vs "
                  f"{r2} [0x{o2:04X}+{n2}]")
            n_fail += 1
    print(f"check_c: {n_ok} OK, {n_fail} FAIL")
    return 1 if n_fail else 0


if __name__ == "__main__":
    sys.exit(main())
