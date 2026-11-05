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

Two channels (emulator static RE, MDISND task `0x2E9F6C`, 3310 v5.79):

- Word doorbell: staged 16-bit words → `[0x100DC]`, busy-gated
  (DSP zeroes to unblock), then kick `[0x30000]=4`, raise
  `[0x20008]=2`. Channels 1/2 (`0x100E4`/`0x100E0`) are dead:
  sole caller passes `r0=3` always.
- Payload ring: 82 halfword slots at `0x10000`, head `[0x100A4]`,
  tail `[0x100A6]`. Free-space `>= [msg+2]+2` to publish.

| code | layout | status | evidence |
|------|--------|--------|----------|
| subtype 2 | full message → 25-slot batch → ring | static | MDISND `0x2EA066` |
| subtype 3 | 16-bit word → 10-slot ring → doorbell | static | MDISND `0x2EA022` |
| subtype 5 | free batch queue (teardown) | static | MDISND `0x2E9FF4` |
| per-opcode builders | unmapped to opcodes | open | producers outside MDISND zone |

## D→M dispatch (operational, latch `[0x111861]!=0`)

| opcode | route | evidence |
|---|---|---|
| `0x8D/0x8E/0x95` | task8 | MDIRCV `0x2EDBE6` |
| `(id&0xF0)==0x70` | local `0x2EDC0E` (incl. SIML `0x74`) | MDIRCV `0x2EDBFA` |
| `0x80` | OP_80 | MDIRCV `0x2EDB2A` |
| `0x8F/0x99` | run-state gate (WEAK: state-enum open) | MDIRCV `0x2EDB38` |
| `0xE4` | keep-alive tick (not SIM timeout) | MDIRCV `0x2EDC4C` |

Boot dispatch (latch `==0`): jump table `0x2EDB48`, sub-ids
`0x80, 0x83-0x8F`.

## Block01 dispatch first

Disassemble block01 from `build/rom6/blocks/`. Extract it with
`tools/extract_blocks.py` from 3310 v5.79 `@0x300CD8`. Enumerate its
MDISND dispatch table. Promote each code with a capture reference.
