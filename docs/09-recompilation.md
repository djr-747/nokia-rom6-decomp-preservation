# 09 - Byte-identical recompilation

Goal: rebuild ROM6 from checked-in source to byte-identical words.
Two layers: verified `.asm` encoding, C intent sources beside them.

## Toolchain

- Assembler: `tic54x-as` + `tic54x-objcopy`, built from upstream
  binutils 2.42 (`--target=tic54x-coff`). Recipe:
  `tools/build_tic54x_as.sh`. Same source the emulator uses for
  `tic54x-objdump`. Installed to `$HOME/.local/bin`.
- C compiler: TI C5000 Code Generation Tools (`cl500`). NOT on this
  machine. No FSF or LLVM C54x backend exists. TI gates CGT behind
  myTI registration plus export-compliance acceptance, so this is a
  user step, not a machine step (checked 2026-11-06: no anonymous
  TI download URL serves it; CCS v4 was the last bundled IDE and is
  discontinued). Get **C5000 CGT** (C54x, driver `cl500`, last line
  6.x) -- NOT C5500 CGT (`cl55` targets the C55x ISA and cannot
  compile this tree. Drop the install under `$HOME/ti/` and tell
  the session; the close-the-loop procedure is: for each `src/**.c`,
  `cl500 -v548 -O2 file.c`, disassemble the `.obj`, diff its words
  against the file's EXPECT list, then delete the hand-written
  `.asm` the C reproduces and re-run `make test`.

## TI C54x dialect notes (SPRU103, unconfirmed without cl500)

- `int` is 16 bits, `long` is 32 bits. Accumulators A/B are 40 bits.
- `interrupt` keyword marks an ISR (context save, `rete` return).
- `ioport` qualifier maps variables to memory-mapped registers.
- Single-page C542 memory model: no XPC bank switching (ROM4 differs).
- Calling: first argument and return in A/B; AR2-AR5 are pointer regs.

## How a module is claimed

1. Write `src/rom6/<subsys>/<addr>_<name>.asm` with `; ORIGIN`.
2. `make recombine` assembles each file, byteswaps LE to BE, and
   compares to the loader image slice. MATCH or fail.
3. Write the intent `.c` beside it (same basename) with `ORIGIN` and
   `EXPECT:` words. `tools/check_c.py` binds the C to the same bytes.
4. `make test` runs both gates plus the decomp regression tests.

## Status

| Layer | Count | Words | Gate |
| asm verified | 968 modules (all subsystems) | 54,646 (53,466 unique = 96.7%) | `test_recombine` floor 54646 |
| C intent | 38 files | 853 | `test_c_spec` |

Encoding rules found: `.mmregs`; `-mfar-mode` global (byte-safe on near
code); ports numeric (`paNN` silently misencodes to port 0); MMR fields
raw with bit7 set when <16 (`MMR(2)` -> 130); DP-relative as plain
direct (`DP+0x04` -> `0x04`, <0x80 only); long RPT/LD forced
(`F070`/`F1xx` forms gas will not pick); XC/`rcd`-condition quirks
forced (objdump prints unparseable `b.0?`-style conditions); `-w` for
gas (the byte-compare is the gate, warnings are noise).
Single-line `.word` forcing with reason comment is the escape hatch;
whole-span `.word` (flagged) is the last resort.
952 pure mnemonic, 1 line-forced module, 3 whole-word, 12 data-majority.
Floor counts module-words; ~1,180w double-count via pre-existing
overlapping symbol bounds (symbols.yaml concern, each module verifies
independently).

Not statically recombinable: <0x2800 runtime-DARAM claims (~613w, bytes
are overlay, not ROM) and the unclaimed dark gaps (~980w dedicated-mode,
needs live-peer trace — the blocked goal).

Next: full-ROM link (`rom6.cmd`), then C growth (curated intent files;
mass transliteration waits for `cl500`).
When `cl500` is obtained: compile each `.c`, diff against EXPECT, then
delete the hand-written `.asm` it reproduces.
