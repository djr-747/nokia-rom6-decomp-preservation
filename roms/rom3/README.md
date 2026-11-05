# ROM3 — unsupported slot (no image)

No recovered ROM3 program image exists, and no ROM3-range block table
has been observed in local images (all 5110/5110i builds fingerprinted
so far are ROM4; 5110 is now judged probably ROM4-only). No phone is
currently attached to ROM3 — it stays a slot, not a claim.
Expected geometry when one lands: 64K-word C54x program space,
big-endian words, vectors at `0xFF80`, `PMST=0xFFA8` boot config.

Landing checklist: fingerprint the build (`tools/fingerprint.py` —
expect a range below the ROM4 band), add SHA-256 to
`docs/03-image-catalog.md`, teach `tools/verify_images.py` the
filenames, mirror `roms/rom6/` structure.
