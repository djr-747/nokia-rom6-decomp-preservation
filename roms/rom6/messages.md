# ROM6 MCU↔DSP message vocabulary (grows with annotation)

Conventions: word addresses, DSP-space. `M→D` = MDISND ring
(`0x800–0x853`); `D→M` = MDIRCV ring (`0x880–0x8E5`).
Status per code: `verified` | `static` | `hypothesis` (see
`docs/05-methodology.md`). Unknown codes stay `UNKNOWN_xx`.

## D→M (DSP reports)

| code | name | layout | status | evidence |
|------|------|--------|--------|----------|
| boot-ready | `DSP_BOOT_READY` (=6?) | version word at MBOX | hypothesis | ROM revision number is what the MCU accepts at boot |
| `0x84` | `RA_INFO` | random-access burst transmitted | hypothesis | emulator ROM4 path; ROM6 layout unconfirmed |
| `0x12` | `UPLOAD_READY` | `[0x871]=0x12` | static | window field map, doc 01 |

## M→D (MCU commands)

| code | name | layout | status | evidence |
|------|------|--------|--------|----------|
| — | *unmapped* | — | — | block01 (`TARG 13D2–1F7C`, "main code / runtime MDI handler") is the dispatch site to annotate first |

## Next work

Disassemble block01 from `build/rom6/blocks/` (extract with
`tools/extract_blocks.py` from 3310 v5.79 @`0x300CD8`), enumerate its
MDISND dispatch table, and promote each code with a capture reference.
