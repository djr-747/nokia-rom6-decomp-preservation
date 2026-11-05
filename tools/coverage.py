#!/usr/bin/env python3
"""Reproducible ROM6 bounded-words coverage from symbols.yaml notes.

Method: parse explicit `bound AAAA-BBBB [+ CCCC-DDDD]*` ranges from each
symbol note (hex words, with or without 0x prefix, case-insensitive).
Merge all ranges (no double-count of overlaps). Report merged word count
over the 0x2800-0xFFFF window (57,856 words) plus the list of symbols
whose notes carry no parseable bound (coverage gap, not code absence).

Bounds live in prose notes; anything not matching the pattern is
reported, never guessed.
"""
import re
import sys
import yaml

WINDOW_LO, WINDOW_HI = 0x2800, 0xFFFF
WINDOW = WINDOW_HI - WINDOW_LO + 1  # 55,296; earlier worklog wrote 57,856
# in error (that size is the 0x1E00-0xFFFF window). Corrected 2026-11-05.

BOUND = re.compile(
    r"[Bb]ounds?\s+(0[xX])?([0-9A-Fa-f]{4})-(0[xX])?([0-9A-Fa-f]{4})"
    r"(?:\s*\+\s*(0[xX])?([0-9A-Fa-f]{4})-(0[xX])?([0-9A-Fa-f]{4}))*"
)
# "119 words to 0x0F76" anchored at the symbol entry address.
WORDS_TO = re.compile(r"(\d+)\s+words?\s+to\s+0[xX]([0-9A-Fa-f]{3,4})")
# "ends adjacent existing A06B": routine runs to the word before.
ADJACENT = re.compile(
    r"ends?\s+adjacent\s+existing\s+(0[xX])?([0-9A-Fa-f]{4})")
# "superblock 8C0A len 465": N counted in C54x words from the anchor.
ANCHOR_LEN = re.compile(
    r"(?:superblock\s+|block\s+)?(0[xX])?([0-9A-Fa-f]{4})\s+len\s+(\d+)")
# "RET at 0x864D" / "RET at 0x3FC3": routine runs entry to the RET word.
RET_AT = re.compile(
    r"(?:RET|RETE|RETD)\s+at\s+0[xX]([0-9A-Fa-f]{3,4})")
# "true end 867D span 9" / "true end retd 0x63D7": all-paths exit word.
TRUE_END = re.compile(
    r"true end\s+(?:(?:retd|ret|rete)\s+)?@?(?:0[xX])?([0-9A-Fa-f]{3,4})")
# "first-RET FC00 @0xA4B9" / "first exit ret FC00 @855E" /
# "first fall-through exit is trete @96FF": first-exit word.
FIRST_EXIT = re.compile(
    r"first(?:-RET|\s+(?:fall-through\s+)?exit|\s+RET)[^@]{0,40}"
    r"@(?:0[xX])?([0-9A-Fa-f]{3,4})")


def ranges_in(addr, note):
    out = []
    note = note or ""
    for m in BOUND.finditer(note):
        segs = re.findall(r"(0[xX])?([0-9A-Fa-f]{4})-(0[xX])?([0-9A-Fa-f]{4})",
                          m.group(0))
        for _, a, _, b in segs:
            out.append((int(a, 16), int(b, 16)))
    for m in WORDS_TO.finditer(note):
        out.append((addr, int(m.group(2), 16)))
    for m in ADJACENT.finditer(note):
        out.append((addr, int(m.group(2), 16) - 1))
    for m in ANCHOR_LEN.finditer(note):
        a, n = int(m.group(2), 16), int(m.group(3))
        out.append((a, a + n - 1))
    for m in RET_AT.finditer(note):
        out.append((addr, int(m.group(1), 16)))
    for m in FIRST_EXIT.finditer(note):
        out.append((addr, int(m.group(1), 16)))
    for m in TRUE_END.finditer(note):
        out.append((addr, int(m.group(1), 16)))
    return out


def main(path="roms/rom6/symbols.yaml"):
    d = yaml.safe_load(open(path))
    syms = [x for v in d["spaces"].values() for x in v.get("symbols", [])]
    ivs, unparsed = [], []
    for x in syms:
        rs = ranges_in(x["address"], x.get("note", ""))
        if rs:
            ivs.extend(rs)
        else:
            unparsed.append("0x%04X %s" % (x["address"], x.get("name", "?")))
    ivs.sort()
    merged = []
    for a, b in ivs:
        if b < WINDOW_LO or a > WINDOW_HI:
            continue
        a, b = max(a, WINDOW_LO), min(b, WINDOW_HI)
        if merged and a <= merged[-1][1] + 1:
            merged[-1][1] = max(merged[-1][1], b)
        else:
            merged.append([a, b])
    tot = sum(b - a + 1 for a, b in merged)
    print("symbols: %d  with parseable bounds: %d  without: %d"
          % (len(syms), len(syms) - len(unparsed), len(unparsed)))
    print("merged bounded words in 0x2800-0xFFFF: %d / %d = %.1f%%"
          % (tot, WINDOW, 100.0 * tot / WINDOW))
    if "--list-gaps" in sys.argv:
        print("--- symbols without parseable bounds ---")
        for u in unparsed:
            print(u)


if __name__ == "__main__":
    main(*sys.argv[1:2] if len(sys.argv) > 1 and not
         sys.argv[1].startswith("--") else [])
