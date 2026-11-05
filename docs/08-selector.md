# 08 — Dual-set selector: DSP version reply picks the block set

This mechanism comes from MCU disassembly (`disfw`, Thumb). Three dual
firmwares confirm it. It closes the open selector question in doc 02.
Selection is by the **DSP's self-reported mask version**, polled over
the HPI mailbox after the common loader boots. It is not an MCU-side
ASIC-ID branch selecting tables up front. (The ASIC ID is still read:
`0x2CB3AE` copies I/O `0x20000` to HPI `0x101E2` = DSP scratch, for the
DSP's own use. That function is 3 instructions long and touches no
table cells.)

## 1. Dual-set directory (flash)

The directory starts with magic `DC0000DC`. Each set follows as
`(stride, ram_cell, table_ptr...)`, terminated by a zero word. The cell
holds the *current* master pointer at upload time. Stride is the byte
distance between the two cells.

| firmware | dir VA | set 1 (cell / first table) | set 2 (cell / first table) |
|---|---|---|---|
| 8210 v5.29 | `0x30CC50` | `0x135810` / `0x30DD68` | `0x13579C` / `0x314E98` |
| 5190 v6.11 | `0x2B2300` | `0x10AD40` / `0x2B2C54` | `0x10ACD0` / `0x2B8B94` |
| 3210 v6.00 | `0x2B67B4` | `0x110CC0` / `0x2B73D4` | `0x110C4C` / `0x2BC994` |

Each set's list holds table pointers to `FD00FF80`-headed block tables.
`tools/extract_blocks.py --table <first ptr>` reproduces our set builds
exactly: 8210-setA `@0x30DD68`, 8210-setB `@0x314E98`, 5190-A
`@0x2B2C54`, 5190-B `@0x2B8B94`.

## 2. Version poll (8210 v5.29, `0x2CAB00` region)

- `ldrh r1,[r4,#4]` reads HPI mailbox `0x10004`. While the mailbox
  holds the parked `0xFFFF`, the code retries. The loop is bounded and
  calls a delay.
- `ldrh r0,[r4,#4]` then `strh r0,[r8,#8]` writes the DSP's reply to
  **`[0x13577C]`**. That cell is the version word.
- Accept gate: `cmp r0,#6; beq ok` / `cmp r0,#5; bne fail`. Only 5 or 6
  proceeds. Anything else aborts the upload (`0x2CABD0`).

## 3. Set-select gates

**8210 v5.29 @ `0x2CAD16`:** `ldrh r0,[0x13577C]; cmp r0,#5; bne else`.
`==5` uses `[0x135810]` (set 1). Any other value uses `[0x13579C]`
(set 2). `ldr r6,[r0]` then walks the 5-word upload header from that
master.

**5190 v6.11 @ `0x28F7F0`:** `ldrh r1,[0x10ACAE]; cmp r1,#3; bne else`.
`==3` loads cell `0x10AD40` (set 1). Any other value loads `0x10ACD0`
(set 2).

**3210 v6.00 @ `0x290C54`:** `ldrb r0,[0x110C2D]; cmp r0,#0; beq set1`.
Flag `==0` uses cell `0x110CC0` (set 1). Any nonzero value uses
`0x110C4C` (set 2). (`disfw` symbols name `0x110C2C` DSP_UPLOADED,
`+1` DSP_TABLE_FAMILY_FLAG, cells at `+0x1F`/`+0x93`.) The flag's
writer (version→flag mapping) is not yet traced. Open: which version
sets the flag nonzero.

## 4. Version → set → ROM assignment

| firmware | version | cell → set | set content (doc 07 verdict) |
|---|---|---|---|
| 8210 | 5 | `0x135810` → set 1 | R5-witness (band R6, `R6ref=0`, miss ~9/37) |
| 8210 | 6 | `0x13579C` → set 2 | **ROM6** (27/28 PROM + 12/12 DROM vs 3310) |
| 5190 | 3 | `0x10AD40` → set 1 | R3-witness (band R4, `R4ref=2`, miss 10/89) |
| 5190 | 4 | `0x10ACD0` → set 2 | **ROM4** (`R4ref=23`, miss 0–1/46) |
| 3210 | flag 0 | `0x110CC0` → set 1 | **ROM4** (`R4ref=23`, miss 0/48) |
| 3210 | flag ≠0 | `0x110C4C` → set 2 | **ROM6** (`R6ref=20`, miss 1/24; page-identical to 8210-B: 19/24 PROM + 12/12 DROM overlap, 0 vs 8210-A) |

R3 is the set a version-3 DSP is served. R5 is the set a version-5 DSP
is served. Mechanism backs that assignment.
Byte-proof of the R3/R5 mask ROMs still needs mask images (or an MCU
version-byte site). No public source provides one. ROM4/ROM6 sides are
byte-validated against the emulator loader images.

Consequences: 3210 v5.36/v6.00 is an R4/R6 dual (not R4/R5). 3210
≤v5.26 is ROM4-single. 8290/8890/8850/2100 singles classify with the
R5-witness shape. They ship version-5 sets. 6150 v5.17–v5.23 is
ROM4-single here.

## 5. Open questions

- open: boot-time init that copies directory list heads into the RAM
  cells. The uploader only reads `[cell]` per block. That init is
  untraced.
- open: 3210 version→flag writer (which version sets the flag
  nonzero).
- open: loader-vs-paged split inside a set list. 5190/3210 show an
  internal zero separator: 11 + 14 table-ptrs. 8210 set 1 is one run
  of 28.
- Trailing metadata words follow each directory. They contain small
  ints 2/3/4 and RAM addresses. They are NOT version→set maps. 8210's
  tail shows 3/4 markers while its gate is 5/6. Do not cite them as
  selector evidence.
- inferred: the DSP-side version source is a mask-ROM register the
  bootcode reads. observed: the MCU side above.
