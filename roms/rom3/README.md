# ROM3 — witnessed, no image

No recovered ROM3 mask image exists. Ten witness tables exist across
six phones: 5190 (v6.11, v6.71), 6190 (v6.13 ×2), 6110 (v4.06, v5.47,
archive), 6130 (v5.00), 5110 (v5.27), 5130 (v5.61).

Witness shape (doc 07): ROM4 band (`0926-F470`), 17-18 payload words,
`R4ref=2`, miss ~10/84-89. Not ROM4, not ROM6, predates both: closed
set `{3,4,5,6}` leaves 3.

Mechanism (doc 08): the 5190 gate serves this set when the DSP reports
version 3 (`==3` → cell `0x10AD40` → first table `0x2B2C54` / `0x2B35A4`).
R3 is the set a version-3 DSP is served.

A future dump has this expected geometry: 64K-word C54x program space,
big-endian words, vectors at `0xFF80`, `PMST=0xFFA8` boot config.

Landing checklist: fingerprint the build with `tools/fingerprint.py`.
Expect a range below the ROM4 band. Add the SHA-256 to
`docs/03-image-catalog.md`. Teach `tools/verify_images.py` the
filenames. Mirror `roms/rom6/` structure.
