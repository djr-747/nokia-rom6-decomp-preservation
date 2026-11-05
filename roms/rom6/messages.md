# ROM6 MCU↔DSP message vocabulary (grows with annotation)

Conventions: word addresses, DSP-space. `M→D` is the MDISND ring
(`0x800–0x853`). `D→M` is the MDIRCV ring (`0x880–0x8E5`). Status per
code: `verified` | `static` | `hypothesis` (see
`docs/05-methodology.md`). Unknown codes stay `UNKNOWN_xx`.

## D→M (DSP reports)

| code | layout | status | evidence |
|------|--------|--------|----------|
| boot-ready `DSP_BOOT_READY` (=6, unconfirmed) | version word at MBOX | hypothesis | ROM revision number is what the MCU accepts at boot |
| `0x84` `RA_INFO` | random-access burst transmitted | hypothesis | emulator ROM4 path; ROM6 layout unconfirmed |
| `0x12` `UPLOAD_READY` | `[0x871]=0x12` | static | window field map, doc 01 |
| `0x83` RSSI | via `0x2C3690`, gated `0x110FE0==1` | static | disfw 3310 v5.79 |
| `0x88` neighbour timing | via `0x2C3CFC`; advances camping if status `!=0x1A` | static | disfw 3310 v5.79 |
| `0x89` channel changed | via `0x2C3D4C` | static | disfw 3310 v5.79 |
| `0x8B` all-RSSI | via `0x2C3FC4` | static | disfw 3310 v5.79 |
| `0x74` local response | subtypes `0x34/0x35/0x0D/0x36`; consumer `0x2C1948` | static | emulator static RE, 3310 v5.79 |

## M→D (MCU commands)

| code | layout | status | evidence |
|------|--------|--------|----------|
| *unmapped* | — | — | block01 (`TARG 13D2–1F7C`, "main code / runtime MDI handler") is the dispatch site to annotate first |

## Block01 dispatch first

Disassemble block01 from `build/rom6/blocks/`. Extract it with
`tools/extract_blocks.py` from 3310 v5.79 `@0x300CD8`. Enumerate its
MDISND dispatch table. Promote each code with a capture reference.
