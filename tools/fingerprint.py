#!/usr/bin/env python3
"""Determine which LEAD DSP ROM revision a firmware build targets.

Method (no reference images needed): scan the .fls for candidate
loader-0 headers (BE words FD00 FF80), walk each candidate descriptor
table (same layout as tools/extract_blocks.py), harvest every
`F073 xx` (C54x `B addr`) PROM call target from the block payloads,
and classify by target RANGE — the cleanly bimodal discriminator:

    ROM4 targets span 0x0926-0xF870     (dsp_boot_ready 4)
    ROM6 targets span 0x0940-0xFF85     (dsp_boot_ready 6)

Rule: any target above 0xF870 => ROM6 (above the ROM4 ceiling);
any target below 0x0940 => ROM4 (below the ROM6 floor).
A phone model can ship several revisions across builds/units — the
verdict is per BUILD, never per model. A build matching neither band
is reported as a range, not forced.

Caveats: the walk must be complete for the range to mean anything
(payload-block inventory is validated 20/20 against the committed
3310 manifest; zero-slot counts are "as found" and may exceed factory
slot numbering — only payload blocks feed the verdict). The bands are
confirmed on ROM4/ROM6 tables only; a first ROM3/ROM5 table tests them.

Usage:
    python3 tools/fingerprint.py --fls /path/to/phone.fls [--tables-only]
"""
import argparse
import struct
import sys

FLASH_BASE = 0x200000
ROM4_LO, ROM4_HI = 0x0926, 0xF870
ROM6_LO, ROM6_HI = 0x0940, 0xFF85


def hw(buf, off):
    return (buf[off] << 8) | buf[off + 1]


def header_at(buf, o):
    """Read the 6-word descriptor at byte offset o; None if out of range."""
    if o + 12 > len(buf):
        return None
    entry, ctrl, size, dest, blen, z = (hw(buf, o + 2 * k) for k in range(6))
    return {"entry": entry, "ctrl": ctrl, "size": size,
            "dest": dest, "len": blen, "zero": z}


def fits(buf, o, size):
    return 1 <= size <= 0x2000 and o + 12 + 2 * size <= len(buf)


def is_data(buf, o, h):
    """A real block header: zero tag, fitting payload, sane target.

    entry is a TARG-space load address (never zero page); dest is the
    staging word (observed up to 0xF00 — block1B runs at 0x1700, outside
    the HPI RAM, so no tight window bound is safe). entry==0 (or padded
    FFFF) is trailing code, not a header.
    """
    return (h["zero"] == 0 and fits(buf, o, h["size"])
            and h["entry"] not in (0x0000, 0xFFFF) and h["dest"] < 0x1000)


def is_placeholder(h):
    """A placeholder slot: zero tag, zero size (entry/dest/len retained)."""
    return h["zero"] == 0 and h["size"] == 0


def walk(buf, start, max_blocks=256, max_drift=32):
    """Walk a descriptor table; return (blocks, end_off) or (None, None).

    Blocks are followed by small zero padding, so after each payload we
    resync forward up to max_drift bytes. Zero slots are recorded as
    placeholders only when the walk continues cleanly afterwards;
    otherwise they are skipped as padding, so a real header can never
    be overshot and code is never mistaken for a header.
    """

    def continues(o2):
        h = header_at(buf, o2)
        if h and (is_data(buf, o2, h) or is_placeholder(h)):
            return True
        for d in range(2, max_drift + 1, 2):
            h = header_at(buf, o2 + d)
            if h and (is_data(buf, o2 + d, h) or is_placeholder(h)):
                return True
        return False

    def accept(o):
        """Return o (or a drifted o) holding a committable header, else None."""
        h = header_at(buf, o)
        if h and (is_data(buf, o, h)
                  or (is_placeholder(h) and continues(o + 12))):
            return o
        for d in range(2, max_drift + 1, 2):
            h = header_at(buf, o + d)
            if h and (is_data(buf, o + d, h)
                      or (is_placeholder(h) and continues(o + d + 12))):
                return o + d
        return None

    blocks, o = [], start
    while len(blocks) < max_blocks:
        nxt = accept(o)
        if nxt is None:
            break
        h = header_at(buf, nxt)
        if (blocks and h["entry"] == 0xFD00 and h["ctrl"] == 0xFF80):
            break  # adjacent table: a new loader block starts a new table
        o = nxt
        h = header_at(buf, o)
        data = [hw(buf, o + 12 + 2 * w) for w in range(h["size"])]
        blocks.append({"flash": FLASH_BASE + o, **h, "data": data,
                       "placeholder": is_placeholder(h)})
        o += 12 + 2 * h["size"]
    # Trailing all-zero slots are post-table padding, not placeholders.
    while (blocks and blocks[-1]["placeholder"]
           and all(blocks[-1][k] == 0
                   for k in ("entry", "ctrl", "size", "dest", "len", "zero"))):
        blocks.pop()
    if not blocks or blocks[0]["entry"] != 0xFD00 or blocks[0]["ctrl"] != 0xFF80:
        return None, None
    return blocks, o


def targets(blocks):
    out = []
    for b in blocks:
        d = b["data"]
        for i, w in enumerate(d[:-1]):
            if w == 0xF073:
                out.append(d[i + 1])
    return out


def verdict(ts):
    if not ts:
        return "no-F073-targets"
    lo, hi = min(ts), max(ts)
    if hi > ROM4_HI:
        return "ROM6"
    if lo < ROM6_LO:
        return "ROM4"
    return f"ambiguous-range-{lo:04X}-{hi:04X}"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--fls", required=True)
    ap.add_argument("--tables-only", action="store_true")
    a = ap.parse_args()

    buf = open(a.fls, "rb").read()
    cands = []
    o = buf.find(b"\xFD\x00\xFF\x80")
    while o != -1:
        if o % 2 == 0:  # descriptors are halfword-aligned; odd hits are data
            cands.append(o)
        o = buf.find(b"\xFD\x00\xFF\x80", o + 2)
    print(f"# {a.fls} ({len(buf)} bytes, {len(cands)} FD00/FF80 candidates)")
    for c in cands:
        blocks, end = walk(buf, c)
        if blocks is None:
            continue
        addr = FLASH_BASE + c
        if a.tables_only:
            print(f"table @0x{addr:06X} ({len(blocks)} blocks)")
            continue
        ts = targets(blocks)
        v = verdict(ts)
        rng = f"{min(ts):04X}-{max(ts):04X}" if ts else "-"
        print(f"table @0x{addr:06X}: {len(blocks):2} blocks, "
              f"{len(ts):3} F073 targets {rng}  => {v}")


if __name__ == "__main__":
    main()
