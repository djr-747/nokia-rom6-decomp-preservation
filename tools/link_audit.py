#!/usr/bin/env python3
"""Link-consistency audit for ROM6 decomp spans against src/rom6/link/rom6.cmd.

Reads per-span (origin, words) from build/recombine.json (byte-verified
.asm spans), checks each span against the linker's MEMORY regions, and
reports overlaps (which block a naive single-image link: two owners for
one word) plus uncovered PROM gaps. Writes build/link_audit.json.
Does NOT run a TI link: a true single-image link needs one generated
SECTION per span (965 sections), which rom6.cmd does not yet carry.
Exit 0 with the audit written even when overlaps exist (they are the
finding, not a harness failure).
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)

REGIONS = [
    ("OVLYRAM", 0x0080, 0x0080 + 0x1F80),
    ("PROMLOW", 0x2800, 0x2800 + 0x8800),
    ("PROMHIGH", 0xB000, 0xB000 + 0x4D00),
    ("BRANCH", 0xFD00, 0xFD00 + 0x0280),
    ("VECS", 0xFF80, 0xFF80 + 0x0080),
]


def region_of(addr):
    for name, lo, hi in REGIONS:
        if lo <= addr < hi:
            return name
    return None


def main():
    rec_path = os.path.join(ROOT, "build", "recombine.json")
    mods = json.load(open(rec_path))["modules"]
    spans = sorted(((m["origin"], m["words"], m["file"]) for m in mods))

    outside = [f for o, n, f in spans
               if region_of(o) is None or region_of(o + n - 1) is None
               or region_of(o) != region_of(o + n - 1)]
    overlaps = []
    for i in range(len(spans)):
        o1, n1, f1 = spans[i]
        for j in range(i + 1, len(spans)):
            o2, n2, f2 = spans[j]
            if o2 >= o1 + n1:
                break
            lo, hi = max(o1, o2), min(o1 + n1, o2 + n2)
            if hi > lo:
                overlaps.append({"a": f1, "b": f2, "lo": lo, "n": hi - lo})

    covered = {}
    for o, n, _ in spans:
        for w in range(o, o + n):
            covered[w] = True
    gaps = []
    for name, lo, hi in REGIONS:
        if name in ("OVLYRAM",):
            continue
        run = None
        for w in range(lo, hi):
            if w in covered:
                if run is not None:
                    gaps.append({"region": name, "lo": run, "n": w - run})
                    run = None
            elif run is None:
                run = w
        if run is not None:
            gaps.append({"region": name, "lo": run, "n": hi - run})

    audit = {
        "spans": len(spans),
        "span_words": sum(n for _, n, _ in spans),
        "unique_words": len(covered),
        "outside_regions": outside,
        "overlap_pairs": len(overlaps),
        "overlaps": overlaps[:40],
        "gap_runs": len(gaps),
        "gaps": gaps[:40],
        "gap_words": sum(g["n"] for g in gaps),
    }
    out = os.path.join(ROOT, "build", "link_audit.json")
    json.dump(audit, open(out, "w"), indent=1)
    print(f"link_audit: spans={audit['spans']} span_words={audit['span_words']} "
          f"unique={audit['unique_words']} overlaps={audit['overlap_pairs']} "
          f"outside={len(outside)} gap_runs={audit['gap_runs']} "
          f"gap_words={audit['gap_words']}")
    for ov in overlaps[:10]:
        print(f"  OVERLAP {ov['a']} vs {ov['b']} @0x{ov['lo']:04X}+{ov['n']}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
