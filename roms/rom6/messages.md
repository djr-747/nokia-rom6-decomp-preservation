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

## DSP-side producer switch (mask `0x53F0+`, objdump-verified)

Message-ID compares on `*(0x573)` select builder chains. Observed
selectors: `0xAF57` (→ `0x5409`, else `B 0x54BB`), `0xA249`
(→ `0x5420`). Taken paths call ordered builder chains —
`CALL 0x8641`, `CALL 0x864E`, `CALL 0xB6E6`, `CALL 0xC717`,
`CALL 0x9FA8` — then `LD *(0x3FC7/0x3FC9)`, `CALL 0x54A4`
(fetch), `B 0x54BB`. Head shapes flags first: `ANDM *(0x51D)`,
`ANDM *(0x263A)`, `MVDK 0x3F12→*(0x57B)`, `LD *(0x2477)`,
`*(0x51C)` RMW with `XC`, `CMPM *(0x573)`.

Convergence `0x54BB`: `CALL 0x6E6`, zero-fill envelope
(`ST #11264 → *(0x1F3/0x243)`, `ADD #11264,a` →
`*(0x54A/0x54B)`), BRC-631 `RPTBD 0x54B9` clear loop
(`AR1=0x2C00`, `STL *ar1+`), `RET` at `0x54BA`.

Mask-side producers reach the same builders from `0xA7xx`
(stitched-low mask code, no setB block contains it):
`ANDM *(0x243)`, `MVMD ar3,0x243`, `CALL 0x8641`,
`ST #12854 → *(0x337C/0x337D)` (round-robin reset, same
`0x3236` constant as `STATE_RR_PTR`), `CALL 0xBA56`,
`CALLD 0xAB78/0x8BDE`, `CALL 0x8C0A/0x867E`, `MVDK 0x2799→*ar4+`
(RPT-75). So builder routines `0x8641/0x864E/0x9F28/0x9F35`
serve three producer groups: dispatcher switch (`0x54xx`),
mask code (`0xA7xx`), and the ISRs (`COBBA_WORKER`,
`STATE_DISPATCH_WORKER`). Opcode-to-identity mapping
(MSID/SIMLOCK/IMEI/tune) stays open: the `0x573` selector
values are the next attribution target.

## `*(0x573)` selector census (image-wide, exact `60F8 0573` scan)

Four values, 13 sites. Routing shape everywhere: `CMPM`,
`BC ...,ntc` — the ntc-taken (non-equal) path does the work,
the equal path joins convergence `0x54BB`.

| value | sites | taken-path behavior |
|---|---|---|
| `0xA249` (-23991) | `0x53BC`, `0x540B`, `0x5436`, `0x546D`, `0xC8C2` | switch: `ANDM`, `ST #0,*(0xB68)`, `CALL 0xD970`, `LD #1→*(0xC4C)`, `ST #3,*(0xA5A)` …; worker site `0xC8C2` (`STATE_DISPATCH_WORKER`) |
| `0xAF57` (-20649) | `0x5402`, `0x9DA0`, `0x9DFB`, `0x9E38`, `0xAB11` | switch + four block-code sites: `CALL 0x6BE`, `LD *(0x85D)`, BRC-159, mode-bit tests, `RPTBD` loop consuming the `0x29C9` STATE_ISR buffer (`LD *ar3+`, `ADD *ar2`) |
| `0xB11C` (-20196) | `0x5464`, `0x8796` | equal path skips to `0x54BB`; non-equal falls into the `A249` test |
| `0xAFAB` (-20565) | `0x53B3` | equal path skips to `0x54BB`; non-equal `CALL 0x672`, then `A249` test whose taken path issues far-call-form `0xF981` sequences (target decode uncertain) |

Block sites (`0x9Dxx-0xABxx`) sit in uploaded block code
(dest `0x1C6`→`0x9C6` run range). No selector test names an
identity opcode yet: the `0x573` values select producer
groups, not individual MSID/SIMLOCK/IMEI messages. The
per-opcode builders of doc-04 §M→D remain the next hop.

## Builder bodies (objdump-verified, `program.be16`)

Message construction is table-driven fill + staged copy.
All `MVDK` sources are *data-space* addresses: their runtime
content is staged, not visible in-mask (program-space at the
same numbers holds unrelated mask code — do not conflate).

- `0x8641-0x864D` (`MSG_BUILDER_8641`): sub-call chain
  `0x592 → 0x8BD5 → 0x8F97 → 0x8813 → 0x8653 → 0x8675`,
  `RET`.
- `0x864E-0x8652` (`MSG_BUILDER_864E`): `CALL 0x592`,
  `CALL 0x8A45`, `RET`.
- `0x8653-0x8674` (`MSG_FILL_8653`): `CALL 0x592`,
  `ANDM #-8,*(0x51E)`; `AR2=0x3025`, RPT-24
  `MVDK 0xB373→*ar2+`; BRC-2 `RPTB 0x8663` over RPT-16
  `MVDK 0xB37B→*ar2+`; `AR2=0x119C`, RPT-7 `MVDK 0xB373`;
  `RPTZ`, `STL → *ar2+`, `*(0x55A)`; `AR3=0x3025`,
  `CALLD 0x86E3`; `AR4=0x118B`, `RET`.
- `0x9F28-0x9F34` (`MSG_STAGE_9F28`): `AR2=0x1100`,
  `AR3=0x093A`, `CALLD 0x9F19` copy engine, BRC=139, `RET`.
- `0x9F35-0x9F41` (`MSG_STAGE_9F35`): same engine,
  `AR2=0x1000`, `AR3=0x093A`, BRC=119, `RET`.
- Copy engine `0x9F19` serves both stagers (body open).
- Follower `0x9F42`: `CALL 0x614`, FRCT set,
  `BITF *(0x577),#1024` → `0x9F50`, `BITF *(0x2B08),#2` …
  (tail open).
