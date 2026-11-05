# ROM6 upper-mask map (`0xB000-0xFD00`, clean window)

Source: `program.be16` == `maskrom-acquired.be16` here (byte-verified).
Listing: `build/rom6/drom.lst`. Density = RET/FB/CALL per 256-word
window (objdump TID decodes data as code; density separates them).

| window | density | shape |
|---|---|---|
| `0xB000-0xB5FF` | 16-40 | code (upper subroutines) |
| `0xB600-0xC9FF` | 0-12 | mixed code + tables |
| `0xCA00-0xCDFF` | 0 | DSP kernel code: straight-line MAC loops (`RPTBD`, `MPY`/`ST \|\| MPY`), no internal CALL/RET (hence density 0). Not a data table (retracted 2026-11-05: `CALL 0xCA69` from `0xC910`; fall-through kernel at `0xCA0B`) |
| `0xCE00-0xE9FF` | 0-12 | mixed code + tables |
| `0xEA00-0xF0FF` | 0 | table B, 1792 words, small structured values |
| `0xF100-0xFCFF` | 0-3 | table C, mixed |

Head of `0xB000`: config words (`0x2938` ×3, then 500/1000/1540/2500).
Longest runs: zeros ×172, `0x7FFF` ×64 (padding/saturation).

## Flash-side sources (not DSP tables)

Config seeds at `0x329308` / `0x3292DC` (3310 v5.79, emulator
`CANONICAL-dsp`): byte streams, nibble-range gain steps plus a
1dB-step curve (`0x0135, 0x0185, 0x01EA, 0x0269 …` LE u16, ×1.26
each). DSP tables are word tables. The MCU converts byte→word when
it builds tune records. Seeds are the source, not the table.

## Consumers (static)

Table B (`0xEA00-0xF0FF`) is read by mask-ROM routines in
`0xD6xx-0xDExx` via `STM #imm,ARx` pointer loads (objdump-verified,
`program.be16`):

| Load site | Table address loaded |
|---|---|
| `0xD31F` | `0xEAFE` |
| `0xDB01`, `0xDB19` | `0xEB3F` |
| `0xD6AF`, `0xD6BC`, `0xD719`, `0xD9A1`, `0xDE0A` | `0xEB9E` |
| `0xDE47` | `0xEBA8` |
| `0xDE56` | `0xEDA8` |

Table C (`0xF100-0xFCFF`) is read by mask routines in
`0xCFxx-0xE5xx` via `STM #imm,ARx` (objdump-verified,
`program.be16`), 11 distinct entries:

| Load site(s) | Table address |
|---|---|
| `0xDE65`, `0xDE72` | `0xF1A8` |
| `0xDEA4` | `0xF5A8` |
| `0xDEB3` | `0xF9A8` |
| `0xE510` | `0xFB5A` |
| `0xE512` | `0xFB9B` |
| `0xDD79` | `0xFBA6` |
| `0xDCA6`, `0xDD06` | `0xFBB6` |
| `0xD171`, `0xD827` | `0xFBD6` |
| `0xD5E7` | `0xFC44` |
| `0xD962` | `0xFC58` |
| `0xCF2F` | `0xFCA9` |

`0xF1A8/0xF5A8/0xF9A8` step `0x400`: record array. Typing of
the records stays open.

Former "table A" (`0xCA00-0xCDFF`) is code, not data:
fall-through from `0xC9F0` (`BD 0xCA0C`, RPT-39 loop,
`CALL 0xE54B`) into an `RPTBD 0xCA0B` MAC kernel
(`MPY *ar2+,a`, `SFTA 9`, `ST a,*ar3+ || MPY *ar2+,a`),
plus a `CALL 0xCA69` entry from `0xC910`. No data-space
consumers exist because there is no table. Table C
(`0xF1xx-0xFCxx`): untyped, consumers open.

## Open typing

- Table B head (`2D0C 030B 0308 010F …`) is not symmetric: not FIR
  coefficients. Low-byte tags (`0x09/0x0B/0x0C/0x0F`) suggest packed
  control/state tables. Five consumer sites share one entry
  (`0xEB9E`): common sub-table or record base.
- Former table-A claim retracted (see Consumers): density-0 does
  not imply data. Straight-line `RPTB`/`RPTBD` kernels have no
  RET/FB/CALL by construction. Lesson: confirm code vs data with
  a caller/branch-in scan, not density alone.
- Table A (full-range, zero-free): coefficient or twiddle candidate.
  correlating user open (which routine reads `0xCAxx`).
- Table C (`0xF1xx-0xFCxx`): untyped.
- Uploaded data pages `block04/block17` (332 words, near-identical,
  config words + `0x0CC0` runs + zero tail) mirror this style:
  per-build parameter pages, not code.
