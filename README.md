# Nokia DCT3 LEAD (TMS320C54x) DSP ROM preservation & decompilation

A clean-room decompilation of the Nokia DCT3 **LEAD** DSP mask ROMs — the
customised TMS320C54x baseband processor that does the actual GSM Layer-1
work (modulation, synchronisation, channel coding, voice codec, RF control)
behind the ARM7 MCU firmware.

Goal: replace the black box with annotated ground truth — what each ROM
routine does, **what stimulus it receives** (MCU mailbox, HPI doorbell,
uploaded code pages, frame interrupt, RF samples), and how Nokia fit a GSM
baseband into a late-90s DSP budget.

## ROM-family layout

One directory per DSP ROM revision. The family shares the seventeenths
tools and docs; only the bytes, symbols, and annotations differ.

| dir | revision | era / phones | status |
|-----|----------|--------------|--------|
| [roms/rom6](roms/rom6/) | ROM6 | 2000+ (3310, 3410, 6210, 8210, 8250, 8850) | **active — current wall** |
| [roms/rom4](roms/rom4/) | ROM4 | 1998–99 (5110, 6110, 3210, 7110) | parked, images catalogued |
| [roms/rom3](roms/rom3/) | ROM3 | unsupported slot (no image yet) | placeholder |
| [roms/rom5](roms/rom5/) | ROM5 | unsupported slot (no image yet) | placeholder |

ROM3/ROM5 have no recovered image and no emulator backend; their slots
exist so a future dump has somewhere to land. This mirrors the emulator's
rule: unknown, analysis-only, incompatible and missing images fail before
any backend is created.

## Bring your own bytes

ROM dumps are copyrighted and **never committed** (enforced by
[.gitignore](.gitignore)). Each `roms/romN/` README names the required
files, their SHA-256, and where to place them (`images/`, gitignored).
`make verify` checks hashes before any other target runs.

The paged program images — the C54x code blocks the MCU uploads into DSP
RAM at boot — are extracted from **your own** MCU flash dumps with
`tools/extract_blocks.py`. They are part of the DSP's code, not data:
uploaded pages execute in place and far-branch back into the mask ROM.

## Layout

- `docs/` — family-wide architecture notes (memory map, boot/upload,
  stimulus catalog, methodology).
- `roms/romN/` — per-revision README, symbol table, curated listings,
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

Sibling project `nokia-dct3-emu` emulates the ARM7 + LEAD faithfully
through MO/MT calls and SMS on ROM4; **ROM6 is the work in progress**.
Every verified finding here becomes emulator ground truth — see
[docs/06-emulator-ground-truth.md](docs/06-emulator-ground-truth.md) for
the handoff format. Nothing here is derived from hidden test or grader
material; sources are the ROM bytes, the MCU firmware's DSP driver, and
TI's public C54x documentation.
