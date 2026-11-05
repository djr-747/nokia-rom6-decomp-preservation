#!/usr/bin/env python3
"""Bulk-classify every local DCT3 firmware image's DSP block tables.

For each image: find loader tables, walk each, harvest F073 targets,
zone-split, score against the validated ROM4/ROM6 reference caller sets,
and landing-test PROM-code targets in the band-indicated ROM image.

Verdict rules per table (all three must agree for a validated verdict):
  band  : max F073 > 0xF870 => R6-band; min < 0x0940 => R4-band.
  refs  : PROM-code-zone overlap with the 5110 (R4) / 3310 (R6) sets.
  land  : operand-landing rate in the band image's PROM-code zone
          (0x2800-0xAFFF; DROM tables excluded — landing is meaningless
          in data). Baselines run 0-2%; witnesses run 11-17%.
  ROM6 (+refs, land ok) | ROM4 (+refs, land ok)
  R5-witness: R6-band, ~0 ref overlap, high miss rate.
  R3-witness: R4-band, ~0 ref overlap, high miss rate.
  anything else => ambiguous (numbers printed, no forcing).

Usage:
    python3 tools/classify.py [--emu-root ../nokia-dct3-emu] [--out docs/07-classification.md]
"""
import argparse
import glob
import json
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from fingerprint import FLASH_BASE, hw, walk  # noqa: E402

ROM4_HI, ROM6_LO = 0xF870, 0x0940
CALL2 = (0xF073, 0xF074, 0xF980, 0xF880, 0xF847, 0xF274)


def is2(op):
    return op in CALL2 or 0x7700 <= (op or 0) <= 0x77FF \
        or 0x7500 <= (op or 0) <= 0x75FF


def zone(t):
    if 0x2800 <= t <= 0xAFFF:
        return "PROM"
    if 0xB000 <= t <= 0xEFFF:
        return "DROM"
    if 0x0800 <= t <= 0x27FF:
        return "DARAM"
    return "VEC"


def verdict(band, m4, m6, rate, nr4, nr6, nprom):
    """Verdict for one table. Reference *coverage* validates (a phone's
    set need only cover half the reference subset — subsets differ by
    phone); the miss rate only witnesses (phantoms put noise on it).
    A witness needs the full triple: right band, ~no ref overlap, and
    a miss rate clearly above the 0-2% genuine baseline.
    """
    if band == "R6" and m6 >= max(2, nr6 // 2):
        return "ROM6"
    if band == "R4" and m4 >= max(2, nr4 // 2):
        return "ROM4"
    if band == "R6" and m6 <= 2 and rate >= 8 and nprom >= 10:
        return "R5-witness"
    if band == "R4" and m4 <= 2 and rate >= 8 and nprom >= 10:
        return "R3-witness"
    return "ambiguous"


def load_img(path):
    return open(path, "rb").read()


def words(buf):
    return struct.unpack(">" + str(len(buf) // 2) + "H", buf)


def table_targets(buf, start):
    blocks, _ = walk(buf, start)
    if not blocks:
        return None, None
    ts = set()
    for b in blocks:
        if b.get("placeholder"):
            continue
        d = b["data"]
        ts.update(d[i + 1] for i in range(len(d) - 1) if d[i] == 0xF073)
    nd = sum(1 for b in blocks if not b.get("placeholder"))
    return {"n_desc": len(blocks), "n_pay": nd}, ts


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--emu-root", default="../nokia-dct3-emu")
    ap.add_argument("--out", default="docs/07-classification.md")
    ap.add_argument("--ref4", default="firmware/5110/NSE-1/v5.30/Nokia 5110 NSE-1 v5.30 A.fls")
    ap.add_argument("--ref4-table", default="0x2948EC")
    ap.add_argument("--ref6", default="firmware/3310/NHM-5/v5.79/Factory Reset 3310 NR1 v5.79.fls")
    ap.add_argument("--ref6-table", default="0x300CD8")
    a = ap.parse_args()

    rom4 = words(load_img(os.path.join(a.emu_root, "firmware/dsp/rom4/program.be16")))
    rom6 = words(load_img(os.path.join(a.emu_root, "firmware/dsp/rom6/program.be16")))
    rb4 = load_img(os.path.join(a.emu_root, a.ref4))
    rb6 = load_img(os.path.join(a.emu_root, a.ref6))
    _, t4 = table_targets(rb4, int(a.ref4_table, 16) - FLASH_BASE)
    _, t6 = table_targets(rb6, int(a.ref6_table, 16) - FLASH_BASE)
    r4 = {t for t in t4 if zone(t) == "PROM"}
    r6 = {t for t in t6 if zone(t) == "PROM"}
    print(f"# refs: R4 PROM n={len(r4)}, R6 PROM n={len(r6)}", file=sys.stderr)

    files = sorted(set(glob.glob(os.path.join(a.emu_root, "firmware/*/*/*/*.fls"))))
    files = [f for f in files
             if "EEPROM" not in os.path.basename(f).upper()
             and "eeprom" not in f and "virgin" not in f and "nvram" not in f]
    rows = []
    for f in files:
        buf = load_img(f)
        short = f.split("firmware/")[-1]
        o = buf.find(b"\xFD\x00\xFF\x80")
        cands = []
        while o != -1:
            if o % 2 == 0:
                cands.append(o)
            o = buf.find(b"\xFD\x00\xFF\x80", o + 2)
        if not cands:
            rows.append((short, "—", "no table", "", ""))
            continue
        for c in cands:
            info, ts = table_targets(buf, c)
            if info is None:
                continue
            prom = {t for t in ts if zone(t) == "PROM"}
            lo, hi = (min(ts), max(ts)) if ts else (None, None)
            if not ts:
                band = "empty?"
            elif hi > ROM4_HI:
                band = "R6"  # band edges live outside PROM-code: full range
            elif lo < ROM6_LO:
                band = "R4"
            else:
                band = "amb"
            m4, m6 = len(prom & r4), len(prom & r6)
            img = rom6 if band == "R6" else rom4
            iname = "R6" if band == "R6" else "R4"
            miss = [t for t in prom if t < len(img) and is2(img[t - 1])]
            rate = 100 * len(miss) // max(len(prom), 1)
            v = verdict(band, m4, m6, rate, len(r4), len(r6), len(prom))
            rng = f"{lo:04X}-{hi:04X}" if ts else "-"
            ev = (f"pay={info['n_pay']} range={rng} R4ref={m4} R6ref={m6} "
                  f"miss@{iname}={len(miss)}/{len(prom)}")
            rows.append((short, f"0x{FLASH_BASE + c:06X}", band, v, ev))
    with open(a.out, "w") as fh:
        fh.write("# Firmware DSP-table classification (generated)\n\n"
                 "Regenerate: `python3 tools/classify.py` (see tool header for rules).\n"
                 "Refs: 5110 v5.30 (ROM4) + 3310 v5.79 (ROM6). "
                 "Only F073 PROM-code-zone (0x2800–0xAFFF) targets count; "
                 "DROM/DARAM/VEC excluded.\n\n"
                 "| image | table | band | verdict | evidence |\n"
                 "|---|---|---|---|---|\n")
        for short, tab, band, v, ev in rows:
            fh.write(f"| {short} | {tab} | {band} | **{v}** | {ev} |\n")
    n_tab = sum(1 for r in rows if r[1] != "—")
    print(f"# wrote {a.out}: {len(rows)} images, {n_tab} tables")
    for short, tab, band, v, ev in rows:
        if "witness" in v or v == "ambiguous":
            print(f"  ! {short} {tab} => {v} ({ev})")


if __name__ == "__main__":
    main()
