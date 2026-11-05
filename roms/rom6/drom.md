# ROM6 upper-mask map (`0xB000-0xFD00`, clean window)

Source: `program.be16` == `maskrom-acquired.be16` here (byte-verified).
Listing: `build/rom6/drom.lst`. Density = RET/FB/CALL per 256-word
window (objdump TID decodes data as code; density separates them).

| window | density | shape |
|---|---|---|
| `0xB000-0xB5FF` | 16-40 | code (upper subroutines) |
| `0xB600-0xC9FF` | 0-12 | mixed code + tables |
| `0xCA00-0xCDFF` | 0 | table A, 1024 words, full-range values, no zeros |
| `0xCE00-0xE9FF` | 0-12 | mixed code + tables |
| `0xEA00-0xF0FF` | 0 | table B, 1792 words, small structured values |
| `0xF100-0xFCFF` | 0-3 | table C, mixed |

Head of `0xB000`: config words (`0x2938` ×3, then 500/1000/1540/2500).
Longest runs: zeros ×172, `0x7FFF` ×64 (padding/saturation).

## Open typing

- Table B head (`2D0C 030B 0308 010F …`) is not symmetric: not FIR
  coefficients. Low-byte tags (`0x09/0x0B/0x0C/0x0F`) suggest packed
  control/state tables. Owner routine open.
- Table A (full-range, zero-free): coefficient or twiddle candidate.
  correlating user open (which routine reads `0xCAxx`).
- Table C (`0xF1xx-0xFCxx`): untyped.
- Uploaded data pages `block04/block17` (332 words, near-identical,
  config words + `0x0CC0` runs + zero tail) mirror this style:
  per-build parameter pages, not code.
