#!/usr/bin/env python3
"""Recombination gate: every checked-in src/asm module must reassemble
byte-identical to the ROM image (tools/recombine.py exit 0), and the
matched-word total must not regress below the pinned floor.

When adding modules, raise RECOMBINE_WORD_FLOOR to the new total printed
by `make recombine`.
"""
import re
import subprocess
import sys

RECOMBINE_WORD_FLOOR = 53682  # wave-12: overlap pass removed all double-counted words (959 spans, 0 overlaps); MATCH still byte-exact


def main():
    r = subprocess.run([sys.executable, "tools/recombine.py", "--rom", "rom6"],
                       capture_output=True, text=True, cwd=".")
    sys.stdout.write(r.stdout)
    assert r.returncode == 0, "recombine.py reported DIFF/FAIL"
    m = re.search(r"(\d+) words$", r.stdout.strip().splitlines()[-1])
    words = int(m.group(1))
    assert words >= RECOMBINE_WORD_FLOOR, f"recombine words {words} < floor"
    print(f"test_recombine: OK ({words} words >= floor {RECOMBINE_WORD_FLOOR})")


if __name__ == "__main__":
    main()
