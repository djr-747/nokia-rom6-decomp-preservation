#!/usr/bin/env python3
"""Regression tests for the bulk-classifier verdict rules (tools/classify.py).

Uses synthetic counts shaped like the validated cases:
  3310 self (R6), 5110 self (R4), 8210-A (R5-witness), 5190-A1 (R3-witness),
  and the phantom-noise case (high ref overlap + a few misses).
"""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                "..", "tools"))
from classify import verdict  # noqa: E402

NR4, NR6 = 29, 30  # reference subset sizes (validated sets)


def test_rom6_self_validates_despite_phantom_misses():
    assert verdict("R6", 0, 30, 16, NR4, NR6, 30) == "ROM6"


def test_rom4_self_validates():
    assert verdict("R4", 29, 0, 0, NR4, NR6, 29) == "ROM4"


def test_r5_witness_needs_triple():
    assert verdict("R6", 0, 0, 24, NR4, NR6, 37) == "R5-witness"
    # same shape but landing clean => ambiguous, not ROM6 (no ref cover)
    assert verdict("R6", 0, 0, 0, NR4, NR6, 37) == "ambiguous"
    # same shape but band R4 => not R5
    assert verdict("R4", 0, 0, 24, NR4, NR6, 37) == "R3-witness"


def test_r3_witness():
    assert verdict("R4", 2, 0, 11, NR4, NR6, 99) == "R3-witness"


def test_small_tables_stay_ambiguous():
    assert verdict("R6", 0, 0, 50, NR4, NR6, 4) == "ambiguous"


def test_cross_phone_subset_validates_by_coverage():
    # 2100-style: 27/28 overlap with the 30-entry R6 ref subset
    assert verdict("R6", 0, 27, 3, NR4, NR6, 28) == "ROM6"
    # partial overlap below half the ref => ambiguous, not validated
    assert verdict("R6", 0, 10, 3, NR4, NR6, 28) == "ambiguous"


if __name__ == "__main__":
    fns = [v for k, v in sorted(globals().items()) if k.startswith("test_")]
    for fn in fns:
        fn()
        print(f"PASS {fn.__name__}")
    print(f"{len(fns)} tests passed")
