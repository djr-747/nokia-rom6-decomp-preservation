#!/usr/bin/env python3
"""Extract MCU-uploaded DSP code-block pages from a DCT3 .fls dump.

Descriptor walk verified against the 5110 block map (block0@table + 12 +
size*2 == block1): each descriptor is 6 BE halfwords, then `size` raw data
words (walk logic after the emulator's tools/dsp/extract_flash_blocks.py —
independent re-implementation of the same on-flash layout):

    +0  entry   (0xFD00 for the loader branch-table block)
    +2  ctrl    (DSP control/target, e.g. 0xFF80 program-mem)
    +4  size    (data words following the 12-byte header)
    +6  dest    (DSP data-word dest; runtime addr = 0x0800 + dest)
    +8  len     (runtime length / param)
    +10 zero
    +12 size raw DSP data words (big-endian, as executed)

Known table starts (flash byte addresses, runtime = file + 0x200000):

    rom6: 3310 NHM-5 v5.79 @0x300CD8 | 3410 NHM-2 v5.46 @0x46FBFC
          8850 NSM-2 v5.31 @0x30E22C | 6210 NPE-3 v5.56 @0x21EAB8
    rom4: 5110 NSE-1 v5.30 @0x2948EC | 6110 NSE-3 v5.48 @0x2A7CE4
          3210 NSE-8 v6.00 @0x2B73D4 | 7110 NSE-5 v5.01 @0x2284EC

Usage:
    python3 tools/extract_blocks.py --fls /path/to/3310.fls --table 0x300CD8
        --out build/rom6/blocks
Writes blockNN.bin (BE words, gitignored payload) + manifest.json
(target/size/dest + dsp_range/targ_range; manifest is committable).
"""
import argparse
import json
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from fingerprint import FLASH_BASE, walk  # shared descriptor-table walker


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--fls", required=True)
    ap.add_argument("--table", required=True, help="table start, hex flash addr")
    ap.add_argument("--out", required=True)
    ap.add_argument("--max", type=int, default=256)
    a = ap.parse_args()

    buf = open(a.fls, "rb").read()
    start = int(a.table, 16) - FLASH_BASE
    if not 0 <= start < len(buf):
        sys.exit("table address outside image (flash base is 0x200000)")
    blocks, end = walk(buf, start, a.max)
    ndata = sum(1 for b in blocks if not b["placeholder"])
    print(f"# table @0x{FLASH_BASE + start:06X} .. 0x{FLASH_BASE + end:06X}  "
          f"({len(blocks)} descriptors, {ndata} with payload)")
    print(f"{'blk':>3} {'addr':>8} {'entry':>5} {'ctrl':>5} {'size':>5} {'dest':>5} {'len':>5}  note")
    os.makedirs(a.out, exist_ok=True)
    manifest, idx = [], 0
    for b in blocks:
        note = "placeholder" if b["placeholder"] else ""
        print(f"{idx:3} 0x{b['flash']:06X} {b['entry']:04X}  {b['ctrl']:04X}  "
              f"{b['size']:5} 0x{b['dest']:03X} {b['len']:5}  {note}")
        if b["placeholder"]:
            manifest.append({"idx": idx, "flash": b["flash"],
                             "placeholder": True})
            idx += 1
            continue
        blob = b"".join(struct.pack(">H", w) for w in b["data"])  # BE, as in flash
        open(os.path.join(a.out, f"block{idx:02d}.bin"), "wb").write(blob)
        manifest.append({"idx": idx, "flash": b["flash"], "entry": b["entry"],
                         "ctrl": b["ctrl"], "size": b["size"], "dest": b["dest"],
                         "len": b["len"], "placeholder": False})
        idx += 1
    open(os.path.join(a.out, "manifest.json"), "w").write(json.dumps(manifest, indent=1))
    print(f"wrote {ndata} blocks + manifest.json -> {a.out}")


if __name__ == "__main__":
    main()
