#!/usr/bin/env python3
"""Discriminate two DSP block sets from one firmware image (dual tables).

Answers: same PROM or different PROMs? Method:
  1. Pair payloads across sets (exact hash, else best similarity).
  2. For paired blocks, align word streams; collect per-callsite target
     pairs (A-target, B-target) at F073/F074/F980/F847/F274/F880 sites —
     any operand position whose opcode matches on both sides.
  3. Cluster (A-B) deltas by zone. Systematic non-zero deltas with
     parallel runs (same delta across consecutive services/tables) mean
     two distinct PROM layouts (e.g. ROM stepping change). Delta ~0 with
     high payload identity means same-PROM variants.
  4. Zone overlap stats (PROM/DROM/DARAM/VEC) as a cross-check.

Usage:
    python3 tools/compare_sets.py --a build/8210-v529-setA --b build/8210-v529-setB
"""
import argparse
import hashlib
import json
import os
import struct
import sys
from difflib import SequenceMatcher

CALL_OPS = (0xF073, 0xF074, 0xF980, 0xF847, 0xF274, 0xF880, 0x7712, 0x7716)


def load(d):
    m = json.load(open(os.path.join(d, "manifest.json")))
    out = {}
    for b in m:
        if b.get("placeholder"):
            continue
        raw = open(os.path.join(d, "block%02d.bin" % b["idx"]), "rb").read()
        out[b["idx"]] = struct.unpack(">" + str(len(raw) // 2) + "H", raw)
    return out


def zone(t):
    if 0x2800 <= t <= 0xAFFF:
        return "PROM"
    if 0xB000 <= t <= 0xEFFF:
        return "DROM"
    if 0x0800 <= t <= 0x27FF:
        return "DARAM"
    return "VEC"


def targets(w):
    return {w[j + 1] for j in range(len(w) - 1) if w[j] == 0xF073}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--a", required=True)
    ap.add_argument("--b", required=True)
    a = ap.parse_args()
    A, B = load(a.a), load(a.b)
    ha = {hashlib.sha256(struct.pack(">" + str(len(w)) + "H", *w)).hexdigest(): i
          for i, w in A.items()}
    hb = {hashlib.sha256(struct.pack(">" + str(len(w)) + "H", *w)).hexdigest(): i
          for i, w in B.items()}
    exact = [(i, ha[h]) for i, w in B.items()
             for h in [hashlib.sha256(struct.pack(">" + str(len(w)) + "H", *w)).hexdigest()]
             if h in ha]
    print(f"# A={a.a}: {len(A)} payloads | B={a.b}: {len(B)} payloads")
    print(f"# exact payload matches: {len(exact)}/{len(B)}")
    pairs, used_a = [], set()
    for i, w in B.items():
        h = hashlib.sha256(struct.pack(">" + str(len(w)) + "H", *w)).hexdigest()
        if h in ha:
            pairs.append((ha[h], i, 1.0))
            used_a.add(ha[h])
            continue
        best = None
        for j, v in A.items():
            if j in used_a or abs(len(v) - len(w)) > max(8, len(w) // 10):
                continue
            r = SequenceMatcher(None, list(v), list(w), autojunk=False).ratio()
            if best is None or r > best[0]:
                best = (r, j)
        if best and best[0] > 0.5:
            pairs.append((best[1], i, best[0]))
            used_a.add(best[1])
    print(f"# paired blocks (exact or sim>0.5): {len(pairs)}/{len(B)}")
    deltas = []
    re_targeted = 0
    struct_diff = 0
    for ai, bi, sim in sorted(pairs):
        v, w = A[ai], B[bi]
        sm = SequenceMatcher(None, list(v), list(w), autojunk=False)
        for tag, i1, i2, j1, j2 in sm.get_opcodes():
            if tag == "equal":
                continue
            if tag != "replace" or (i2 - i1) != (j2 - j1):
                struct_diff += 1  # insertion/deletion: structural, not a re-target
                continue
            for k in range(i2 - i1):
                a_w, b_w = v[i1 + k], w[j1 + k]
                if a_w == b_w:
                    continue
                pre_a = v[i1 + k - 1] if i1 + k > 0 else None
                pre_b = w[j1 + k - 1] if j1 + k > 0 else None
                if pre_a == pre_b and pre_a in CALL_OPS:
                    deltas.append((a_w - b_w, zone(a_w), ai, bi, pre_a))
        if sim > 0.9:
            re_targeted += 1
    print(f"# structural (insert/delete) diff hunks: {struct_diff}")
    print(f"# high-similarity pairs (re-targeted same source): {re_targeted}")
    by_zone = {}
    for d, z, ai, bi, op in deltas:
        by_zone.setdefault(z, []).append(d)
    for z in ("PROM", "DROM", "DARAM", "VEC"):
        ds = by_zone.get(z, [])
        if not ds:
            print(f"# {z} deltas (A-B): none"); continue
        from collections import Counter
        c = Counter(ds)
        top = ", ".join(f"{d:+#x}x{k}" for d, k in c.most_common(6))
        print(f"# {z} deltas (A-B) n={len(ds)}: {top}")
    ta = set().union(*[targets(w) for w in A.values()]) if A else set()
    tb = set().union(*[targets(w) for w in B.values()]) if B else set()
    for z in ("PROM", "DROM", "DARAM", "VEC"):
        sa = {x for x in ta if zone(x) == z}
        sb = {x for x in tb if zone(x) == z}
        print(f"# {z} F073: A={len(sa)} B={len(sb)} overlap={len(sa & sb)}")


if __name__ == "__main__":
    main()
