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

## Opcode dispatch is table-indirect (`0x5100+`, objdump-verified)

The `0x2F61/0x2F62` cells are not constants but table handles:
`AR5=0x2F61`, `LD *ar5,a`, `SFTA a,-8`, `SUB #43` → table index,
`BC 0x515E,beq`, then flag shaping on `*(0x264E)`/`*(0x2662)`
(`BITF #4`, `ORM #64`, XC-gated `STL`). The record-compare at
`0x5190+` then scans the unpack zone for the selected marker.
Only 6 references to `0x2F61/0x2F62` exist image-wide, all
inside this clause — the tables themselves are staged DARAM,
unreadable statically. Consequence for the identity goal: the
opcode→MSID/SIMLOCK/IMEI/tune map cannot be recovered from
mask bytes; it needs the staged table contents (runtime read
of `0x2F61`-rooted tables) or the ARM-side MDISND builder
constants that fill them.

## Opcode dispatch is record-compare (`0x5190+`, objdump-verified)

Upstream of the producer switch, a clause compares the unpacked
6-byte record (`*(0x36B-0x375)`, the dispatcher unpack zone)
against expected patterns: `LD *(0x36F/0x375/0x374)`, loop with
`MAR *ar1-`, expected bytes scaled from `*(0x2F61/0x2F62)` tables
(`LD …,-8,a` / `LD …,8,b`, `AND #255`, `SUB`, `BC aeq`), `BANZ`
over the field count, `B 0x51D4` on full match into the gated
producer-call sequence (`CALLD 0x425F`, `CALL 0x57FE`,
`CALL 0x52C4`, `CALL 0x573B`, `CALL 0x520C`, then `LD *(0x250F)`
post-check). So opcodes reach builders by record match, not by a
jump table — the VALUES in the `0x2F61/0x2F62` pattern tables are
the opcode→identity map and are still unread (data-space tables,
staged at runtime).

## Block-code producer chain (`0x9C99+`, objdump-verified)

Worker mode words are block-driven: `*(0x85D)` referenced at 17
sites, `*(0x860)` at 14, nearly all in uploaded block code
`0x9C9F-0x9ED2` (plus the worker itself). Representative chain
at `0x9C99`: `CALL 0x6D4`, `CALL 0x6BE`,
`LD *(0x860) → STL *ar2+` (`AR2=0x29C8`, the STATE_ISR
round-robin zone); `AR3=0x85C`, BRC-159 `RPTBD` scaling loop
(`TMPY *ar2,*ar3`, `STH *ar2+` — 160-tap keyed transform of
the worker buffer); `BITF *(0x860),#144` → `0x9CCF`;
`CALL 0x9F35` (stager), `CALLD 0x8BDE`, `AR4=0x29C9`,
`CALL 0x8C0A`, `CALL 0x9F35` again; `CMPM *(0x2F03),#0`;
`ANDM/ORM` on `*(0x860)`; `CALLD 0x86E3` (fill engine).
Decode-transform-stage in one chain: worker state in,
scaled buffer out, staged message via the same builders the
ISRs use. Simlock-candidate shape (decode then reply), but no
lock-data constants observed yet — identity-opcode match is
the next hop.

## Simlock anchor: negative result (recorded 2026-11-05)

Emulator `docs/dct3-identity-provisioning.md` says the ROM's
SIMlock decode writes DSP words `[0x1202..0x1207]`. Exhaustive
static search finds no reference to that range in mask ROM:
zero absolute-operand hits (`0x1202-0x1207` never appears as a
word in `program.be16` `0x2800-0xFFFF`), zero `STM #imm,ARx`
loads of it (nearest staged pointers: `0x123C/0x124C/0x125A`),
and zero hits in any setB uploaded block. Consequence: the
decode either addresses the buffer AR-relative/computed, or
the doc addresses are MCU-side. Either way the simlock
routine is not locatable by buffer anchor from static DSP
bytes. The remaining route is ARM-side: match MDISND
per-opcode builder constants (doc-04) against the DSP
record-compare pattern tables (`0x2F61/0x2F62`) and the
`0x36B-0x375` unpack zone at runtime.

## Tune-config flow: staged keys, worker application

Transform key material is never mask-written: `0x85C` appears
only as `STM AR3/AR4` address loads at five block-code sites
(`0x9CA3/0x9CA9/0x9D39/0x9D86/0x9D94`); `0x857` once
(`AR4=0x857` in the worker). Both are read-only pointers into
staged DARAM — the MCU-uploaded tune config (NVRAM/eeprom
records → MCU → upload, per the identity description). The
`0x9C99` chain applies them: mode from `*(0x860)`, 160-tap
`TMPY` transform against the `0x85C` key over the `0x29C8`
worker buffer, `MPYU` scaling from `0x857` into `0x4CD`,
bitfield extracts into tune cells `0x4C3/0x4C4`. Lane cell
`0x572` is worker-read, worker-written (`ST t`), block-read at
`0xA0C7/0xA0DB/0xC624`. Mode/counter cell `0x2B08` is tested
21× (`BITF`) across block code `0x9F4C-0xA117` and
compared/subtracted in the worker — the most-polled identity
state cell in the image. Tune path closed at the mechanism
level; key VALUES are staged, not in mask.

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
