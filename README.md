# Nokia DCT3 LEAD (TMS320C54x) DSP ROM preservation & decompilation

A clean-room decompilation of the Nokia DCT3 **LEAD** DSP mask ROMs. The
LEAD is a customised TMS320C54x baseband processor. It does the GSM Layer-1
work (modulation, synchronisation, channel coding, voice codec, RF control)
behind the ARM7 MCU firmware.

Goal: replace the black box with annotated ground truth. Ground truth covers
what each ROM routine does. It covers **what stimulus it receives** (MCU
mailbox, HPI doorbell, uploaded code pages, frame interrupt, RF samples). It
covers how Nokia fit a GSM baseband into a late-90s DSP budget.

## ROM-family layout

One directory per DSP ROM revision. The family shares the same tools and
docs. Only the bytes, symbols, and annotations differ.

| dir | revision | phones (census) | status |
|-----|----------|-----------------|--------|
| [roms/rom6](roms/rom6/) | ROM6 | 2100, 3210‡, 3310 fam, 3410, 3610, 5210, 5510, 6210, 6250, 8210‡, 8250, 8290‡, 8850‡, 8855, 8890‡ | **active — current wall** |
| [roms/rom4](roms/rom4/) | ROM4 | 3210‡, 5110, 5130, 5190‡, 6110, 6130, 6150, 6190‡, 7110, 8810 | parked, images catalogued |
| [roms/rom3](roms/rom3/) | ROM3 | witness sets only: 5110, 5130, 5190‡, 6110, 6130, 6190‡ | placeholder, no image |
| [roms/rom5](roms/rom5/) | ROM5 | witness sets only: 8210‡, 8290‡, 8850‡, 8890‡ | placeholder, no image |

‡ = dual-set firmware: both revisions ship in one firmware file, MCU picks by
DSP version (`docs/08-selector.md`). Census: 58 ROM6, 36 ROM4, 17
R5-witness, 10 R3-witness tables, 0 ambiguous (`docs/07-classification.md`).
RF split follows the ROM: ROM4-era is PLUSSA/CRFU (5110, 6110),
ROM6-era is HAGAR (`docs/04-stimulus-catalog.md` §7a).

ROM3/ROM5 have no recovered image and no emulator backend; their slots
exist so a future dump has somewhere to land. This mirrors the emulator's
rule: unknown, analysis-only, incompatible and missing images fail before
any backend is created.

## Required dumps

ROM dumps are copyrighted and **never committed** (enforced by
[.gitignore](.gitignore)). Each `roms/romN/` README names the required
files, their SHA-256, and where to place them (`images/`, gitignored).
`make verify` checks hashes before any other target runs.

The paged program blocks are C54x code blocks. The MCU uploads them into DSP
RAM at boot. Extract them from **your own** MCU flash dumps with
`tools/extract_blocks.py`. They are part of the DSP's code, not data.
Uploaded pages execute in place. They far-branch back into the mask ROM.

## Layout

- `docs/` — family-wide architecture notes (memory map, boot/upload,
  stimulus catalog, methodology).
- `STYLE.md` — writing rules. All prose follows them. No exceptions.
- `roms/romN/` — per-revision README, symbol file, curated listings,
  C decomp sources.
- `tools/` — `verify_images.py`, `disasm_c54x.py`, `extract_blocks.py`.
- `build/` — everything generated (gitignored). Reproduce with `make`.

## Quick start (ROM6)

```sh
# 1. Drop your dumps in images/ (see roms/rom6/README.md for names+hashes)
make verify
# 2. Full annotated listing -> build/rom6/
make disasm-rom6
# 3. Curated entry-point review
less roms/rom6/vectors.md
```

## Relationship to the emulator

Sibling project `nokia-dct3-emu` emulates the ARM7 + LEAD. It covers MO/MT
calls and SMS on ROM4. **ROM6 is the work in progress**.
Every verified finding here becomes emulator ground truth. See
[docs/06-emulator-ground-truth.md](docs/06-emulator-ground-truth.md) for
the handoff format. Nothing here is derived from hidden test or grader
material. Sources are the ROM bytes, the MCU firmware's DSP driver, and
TI's public C54x documentation.
