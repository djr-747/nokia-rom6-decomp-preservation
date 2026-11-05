# ROM6 runtime interrupt table + handler inventory (3310 v5.79, static)

Mask table: all slots are `RETF` stubs except reset. Source:
[vectors.md](vectors.md). The working table is uploaded.

## Runtime table image

`build/3310-v579/block23.bin` (manifest block0F, runs `0x0A00-0x0A68`)
is a full 26-slot IVT image. Head mirrors the mask table (reset +
stubs, offsets `0x00-0x3F`). Populated slots use the 4-word hardware
form `PSHM XPC / PSHM ST0 / FB handler`. Offset `/4` = vector number.

| vector | slot image | handler | note |
|---|---|---|---|
| V16 | `FB 0x22DA` | `0x22DA` | full context save; `CALL 0x05DA` first |
| V17 | `FB 0x27CD` | `0x27CD` | shared ×3 |
| V18 | `FB 0x27CD` | `0x27CD` | mask V18 instead runs resident `0x3598` |
| V19 | `FB 0x05FA` | `0x05FA` | DARAM; no static source (open §4) |
| V20 | `FB 0x25DF` | `0x25DF` | clears RSA/REA (repeat-safe ISR) |
| V24 | `FB 0x27CD` | `0x27CD` | shared ×3 |
| V25 | `FB 0x2B53` | `0x2B53` | polls HPI words `*(0x866/0x870)` |
| rest | `RETF` stubs | — | no handler |

Vector-to-line map (V16-21 = INT0-5, V24 = TINT0, V25 = BRINT0) follows
SPRU131 convention. LEAD wiring unconfirmed.

## Handler prologues (from `program.be16`, BE words)

- `0x22DA`: `CALL 0x05DA`, then PSHM ST1/AL/AH/AG/BL/BH/BG/T/
  AR1/AR6/AR0/AR4/AR5/AR2/AR3/BRC/RSA. Callee runs pre-save.
- `0x27CD`: `CALL 0x05F4`, then PSHM incl. `PSHD *(0x60)`, `PSHD *(0x61)`.
  `*(0x60/0x61)` are Viterbi state (callsite-sigs). This is the
  frame-processing ISR.
- `0x25DF`: `CALL 0x05E8`, then PSHM incl. BK/RSA/REA, then
  `STM #0,RSA / STM #0,REA`.
- `0x2B53`: no pre-call. `ORM #2,*(0x866)`; `LDU *(0x870)`; branch on
  `*(0x4C2)-4`. HPI words, not ports. Continuation open.
- Resident `0x3598` (mask, V18 fallback): loads mailbox word via AR2,
  masks `#0xFF`, stores via AR6, sets flag `*(0x54F)`, dispatches via
  `CALL 0x2E2F` / `B 0x2E64`. Entry matches the emulator's host-ISR
  description. Downstream port ops live in the callees.

## Block00 branch table (software dispatch, not the IVT)

`build/3310-v579/block00.bin` head (`0x0D00+`): 2-word slots,
`F073 addr` or `FC00 F495` filler. 12 live slots branch to
`0x1BC9/1BD8/1BA8/1B7B/1C08/1C20/1C2F/1C3E/1B9C/1845/18EC/1938`.
Targets sit in uploaded-code space. Table ends `0x0D6A`
(`F4E5 F495`).

## Loader1 sequence (`0x0F00`, block00 tail; 3310 v5.79)

`STM SP/SWWSR/CLKMD` (PLL on), zero DARAM (`0x60+`, `0x1000+`),
`MVPD 0xFF80→0x0780` (mask vectors to DARAM), `STM #0x07A8,PMST`
(IPTR `0x0F`: runtime base `0x0780`), `MVPD 0x0D00→0x0590`
(branch table to mini-kernel), upload engine on UPLOADHEADER
(`0x87B-0x87F`). The `0x05DA/0x05E8/0x05F4/0x05FA` callees are
copies of block00 code, not separate uploads.

Late page block48 (runs `0x0F00`, overwrites loader): re-inits,
`ST #6,*(0x803)`, `MVPD 0xFF87→*(0x802)`. Mask `0xFF87` is the
version constant: `6` on ROM6, `4` on ROM4 (byte-verified both).
MCU poll `[0x10004]` = HPI word 2 = `*(0x802)`. Full version path:
silicon constant → HPI word → version word → set gate (doc 08).
Predicts `5`/`3` on R5/R3 silicon. Untested: no images.

## FRAME_ISR_ENTRY `0x27CD` (V17/V18/V24, mask)

Prologue: `CALL 0x05F4`, full PSHM incl. `PSHD *(0x60/0x61)`,
RSA/REA zero, `ST1 = (ST1 & 0x2000) | 0x4900` (FRCT-class mode set).

Sample combine: `AR2=0x021E`; `A = ~(port2) & (port1)`.
`BITF *(0x20FF),#0x400` reads a mask-ROM status word (DROM face).

Dispatch cascade on A (bit → target):

| bit(s) | target | note |
|---|---|---|
| 12 | `0x296A` | local |
| `0x1C` | `0x2875` | local |
| DROM `#0x400` | `0x2811` | mask |
| 8 | `0x952E` | drom-band code |
| 9 | `0x953C` | drom-band code |
| else | `0x2819` | mask fall-through |
| 8 | `0xC806` | mask |
| 9 | `0xC7B1` | mask |
| 10 | `0x94F0` | drom-band code |
| 7 | `0x2AFC` | local |
| 1 | `0x2867` | local |
| 0 | `0x2873` | local |
| 5,6 | `0x2B45` | local (shared) |
| 14 | `0x2BA1` | local |
| 11 | `0x2BAA` | local |
| 15 | `0x2C03` | local |

Fall-through (no bits): re-read port2, echo the sample back
(`PORTW pa2`), full POPM restore incl. `*(0x60/0x61)`, `FRETE`.
Code after `FRETE` is the next mask routine, not the ISR.

## SAMPLE_ISR_ENTRY `0x22DA` (V16, mask)

RX signal-processing ISR. Entry pre-calls `0x05DA`, then the same
ST1 mode prologue as the frame ISR.

Handshake: `PORTR pa33→*(0x8)`, OR `#0x0C00`, `PORTW pa33` back.
Dispatch on request kind `*(0x22C)`: `==1 → 0x2468`,
`==2 → 0x257D` (matches the `RX_REQUEST_KIND_FLAGS` values).

Filter kernel: `BK=16` circular, `ASM=0`, `BRC=7`, coeffs at
`AR5=0x3EBD`, input `AR4=0x204`, output `AR6=0x200`. Dual-MAC FIR
(`TMPY/MAC/MACR` on A and B), sample stream in via
`PORTR pa39,*AR6+%`. Tail computes squared distance (`SQDST`,
`DST`) = Viterbi branch metrics, then `CALL 0x05DC` and a BCD loop
over `*(0x22F)`.

This ISR feeds the Viterbi decoder. Coeff table `0x3EBD` length
open (8 taps implied by `BRC=7`; confirm against consumer reads).
`0x05DC` body open (mini-kernel, same source question as
`0x05DA/0x05E8/0x05F4`).

## COBBA_CMD_ISR_ENTRY `0x2B53` (V25, mask)

HPI-word request ISR. Entry saves ST1/AL/AH/AG/BL/BH/BG, sets
`*(0x866)` bit 1, then gates: `*(0x870)==0` → skip;
`*(0x4C2)>=4` → skip. `*(0x870)` is HPI word `0x70` = MCU
`0x100E0`, the Cobba-command slot. The DSP honors it here even
though 3310's MDISND task never writes channels 1/2.

On take: full save incl. `*(0x60/0x61)`, RSA/REA zero,
`CALL 0xB4F8` (mask-zone worker), toggle `*(0x29)`,
`ST #0,*(0x870)` (consume the request), full restore, `FRETE`.

Post-`FRETE` neighbor at `0x2BA1` (also a frame-cascade target,
bit 14): `ST/PORTW pa1` sequences with delays, `PORTR pa56`
status poll, `B 0x283D` gate. pa1/pa56 handshake routine.

## COBBA_WORKER `0xB4F8` (mask, called from V25)

`CALL 0x6CA`, full save. `LD *(0x85D)`, `AND #255`,
`LD #2,b`, `BC 0xB534,aeq`; `BITF *(0x4C2),#2` →
`0xB530`; `CALL 0xC717`; `BITF *(0x860),#144` →
`0xB530`. Bit-1 path (`0xB522`): `BITF *(0x85D),#2`
→ `0xB522`; `CALL 0x9F28`, `CALL 0x864E`, `CALL 0x9F28`,
`B 0xB52D`. Bit-2 path: `CALL 0x9F35`, `CALL 0x8641`,
`CALL 0x9F35`, `ANDM #-873,*(0x537)`, `LD #2,b`,
`CALL 0xB461`, `LD #1,a`, `CC 0xB4A8,aeq`. Restore,
`CALL 0x6D2`, `CALL 0x6B2`, `LD *(0x4C2),b`,
`CC 0xB461,bneq`. Then `AR4=0x85E`, `MVDK *ar4+→*(0x577)`
(byte move), lane split (`AND #255`, `SFTL -8`, `STLM b,t`),
`SUB *(0x572),b` → `0xB55B` else `ST t,*(0x572)`,
`ST #3277,*(0x2AFE)`, `ST #10,*(0x2AFD)`, `STLM a,t`,
`SUB *(0x2B08),a,b` → `0xB56F`, `LD *(0x2510)`,
`AND #240`, `SUB #192` → `0xB56F` else `ST t,*(0x2B08)`,
`CALL 0xB6E6`, `CALL 0xC717`, `BITF *(0x7),#0x800`,
`SSBX INTM`, `ANDM #-8193,*(0x51E)` → `0xB57B`, else
`ORM #8192,*(0x51E)`; pa0 strobe (`PORTR`, `OR #12`,
`PORTW`, RPT #20); `BITF *(0x51E),#8192` → `0xB58C`;
`RSBX INTM`; `LDU *(0x854)`, `SFTL -12`;
`CMPM *(0xB),#9` → `0xB5A1`, `AND #4095` → `*(0x58D)`;
`CMPM *(0x125C),#0` → `0xB5B1`; `AND #3855`,
`OR *(0x125E)`; `CMPM *(0xB),#8` → `0xB5B1`;
`BITF *(0x4C2),#15` → `0xB5AF`, `AND #2559`, `B 0xB5B1`
else `OR #1536`, `AND #4095`, `CALL 0x4007` (port-0
transaction reused as RF writer); `LD *(0x856)`,
`AND #1` → `0xB5FF aeq`; `LD *(0x4C2)`, `AND #1` →
`0xB5C5 aneq`; zero `0x4C6-0x4CC` (RPT #6); bitfield
extracts from `*(0x856)` (`AND #7,2`, `SFTL -2`,
`ADD #-17533` → `LD *ar3` → `*(0x4C3)`; `AND #7,5`,
`SFTL -5`, `ADD #-17541` → `*(0x4C4)`; `ST #0,*(0x4C5)`);
`CALL 0x6B4`; `T=8389`, `MPYU *ar4+(0x857)`,
`SFTA -12` → `*(0x4CD)` (×2 lanes). Epilogue `0xB5FB`:
`LD #1,b`, `CALL 0xB461`, `RET` at `0xB5FE`. Followers
`0xB5FF` (`ST #3,*(0x4C5)`, `CALL 0x6B4`, `RET`) and
`0xB606` (SUBC divide loop, `RET`) are separate subroutines.

## STATE_WORKER `0xC851` (mask, called from V20)

`CALL 0x5EA` (mini-kernel window — zeros in-mask, live at
runtime via loader copy). `ANDM #-3073,*(0x51C)`,
`ANDM #-1792,*(0x20F4)`, `ORM #2,*(0x20F4)`, zero
`*(0x20F5/0x20F6/0x20F9)`, `ST #0,*(0x20FA)`,
`ST #-1,*(0x2203)`; `PORTR pa0`, `OR #28`, `PORTW pa0`
(RPT #20); `LD #8,b`, `CALL 0xB461`, `RET` at `0xC85C`.
(Correction: the next routine starts at `0xC85D`, not
`0xC86C`; `0xC86C` is its pa1-strobe line.)

## STATE_DISPATCH_WORKER `0xC85D-0xC91B` (mask)

`CALL 0x5EA` (mini-kernel), `*(0x51C)` flag RMW
(`ANDM #-8989`, `ORM #4`, `ANDM #-65`), `LD #768,b`,
`PORTW pa1` (RPT #22), `PORTR pa2` with `ANDM #-769`,
`PORTW pa2`; `LD *ar6`, `ANDM #-257,*ar6`, lane split
(`AND #1536` → `*(0x20F9/0x20F5)`, `*ar7`; `SFTA -8`,
`ADD #-14175`), `BACC a` into jump table
(`B 0xC8A9/0xC8B6/0xC8B8/0xC8BA`). Case: save AR4,
`CALL 0xB6E6`, `CALL 0xC717`, `CALL 0x9FA8`,
`ORM #7328,*(0x577)`, restore, `B 0xC8D4` (×3 cases).
Convergence `0xC8D4`: `CALL 0xC717`,
`ANDM #-7329,*(0x577)`, `ST #0,*(0x2B08)`,
`CMPM *(0x573),#-23991` → `0xC8D4`; `LD #8,b`,
`CALL 0xB461`; `LD #1538,a` + `LD #8,b`, `CALL 0x4007`;
`LD #2372,a` + `LD #9,b`, `CALL 0x4007`; `AR2=0x20F7`,
`AR3=0x20F9`, pa54 status poll (`PORTR pa54`,
`AND #8192` → `0xC8EF` else `PORTW`), delay loop,
`CALLD 0xC91C`, `CALLD 0xC965`, `CALL 0xC9E3`,
`CALL 0xCA69` (DSP kernel; the caller already on record),
`CALLD 0xCE05`, `CALL 0xCEB4`, `RET` at `0xC91B`.

## STATE_ISR_ENTRY `0x25DF` (V20, mask)

State-machine ISR, no ports in the head stretch. `BITF *(0x51F)`
gate → `0x2603`; copy `*(0x20)→*(0x21)`; `BITF *(0x51C)` gate →
`0x2610`; counter `*(0x20FA)-5`, skip if below; `CALL 0xC851`
(drom-band code) then `CALL 0x05F0` (mini-kernel).

McBSP path: `LDM DRR0` (serial receive), shift/scale block with
`SAT` saturation, conditional calls `CC 0x6A0/0x69A` on
`*(0x577)` flags, then `CALL 0x6CC` and a nested save. AGC/gain
scaling shape with saturating arithmetic.

Tail (objdump-verified, `program.be16`): `BITF *(0x4C2),#4` →
`0x2679`; `LD *(0x85D)`, `AND #20`, BEQ → `0x2679`; round-robin
store through `AR3=*(0x2A69)` with `CC 0x69A` on
`*(0x577)` bit 8; wrap check `*(0x2A69)` vs 13013 (`0x32D5`):
at wrap, `ST #12854` (`0x3236`) to `*(0x2A69)` and RPT-160
`MVDD 0x3236→0x29C9`, `ORM #8192,*(0x57C)`; restore, `CALL 0x714`;
`BITF *(0x58F),#15` → `0x26BC`.

Second half: save, `ADDM #1,*(0x2967)` frame counter, compare vs
80 with `*(0x2966)` vs 2 gate → `0x26B5`; BK=320 block loop over
`AR2=*(0x296A)` vs `*(0x2969)` vs 320 → `0x26AD`, `ADDM #1,*(0x2968)`
else per-lane `STL` to `*AR2+%` and `*(0x2977)`, `ADDM #1,*(0x2969)`;
`AR3=*(0x1F3)`, BK=632; `BITF *(0x51C),#1024` → `0x26D2`;
`BITF *(0x4C2),#4` → `0x2702`; `CALL 0x724`, store to `*AR3+%`,
`BD 0x2702`.

Port-54 poll loop (`AR2=0x20F7`): `PORTR pa54`, `AND #8192`,
BEQ → `0x26EB`; `LD *(0x20F9)`, BEQ → `0x26ED`; `LD *AR2+1`,
`PORTW pa52`, `DELAY *AR2`, `ADDM #-1,*(0x20F9)`, `B 0x26F3`;
else `PORTW *(0x8),pa52`, `B 0x2702`. Then `LD *(0x20F9)`,
BNEQ → `0x26FE` else `STL` to `*AR2+1`, `ST #1,*(0x20F9)`;
else `STL` to `*AR2`, `ST #2,*(0x20F9)`. `CALL 0x5F2`.

Coefficient block on `*(0x220B)` bit 0 → `0x271E`: T-load from
`*(0x521)`, `LD/MAC/TMPY` chain (`#-25457`, `#-12930`, `#28193`,
`#14097`) with `DELAY`, `SFTA 3`, `SAT`; `CALL 0x6CE`.

Exit: `BITF *(0x4C2),#4` → `0x2769`; `BITF *(0x85D),#4` and
`BITF *(0x58F),#15` → `0x273E`; `LD *(0x85D)`, `AND #2`,
`AR3=*(0x57E)` round-robin vs 13013 → `0x2769`; at wrap
`ST #12854,*(0x57E)`, `ORM #16384,*(0x57C)`, `LD *(0x57C)`,
`AND #4096` → `0x2765` else `AR3=0x32D6`, `AR2=0x3236`,
RPT-160 fill, then `0x2765`: `ANDM #-4097,*(0x57C)`, `B 0x2769`.

Convergence `0x2769`: RPT-160 `STL b,*AR2+` (`AR2=0x3236`),
restore, `CALL 0x716`, `BITF *(0x58F),#15` → `0x2775`;
`XOR a`, `BITF *(0x577),#516` → `CC 0x69C`, `MVMD ar3,0x54B`;
`BITF *(0x4D1),#1` → `0x27B2`; save AL/AH/AG, `CALL 0xB634`,
`SFTA a,-16`, `AR3=*(0x1F3)` BK=632 circular accumulate
(`MAR *ar3-%`, `LD *ar3`, `ADD`, `STL`), restore, `ADD b,a`,
`CALL 0x6D0`; `BITF *(0x4C2),#4` → `0x27B2`;
`LD *(0x85D)`, `AND #16`, `AR3=*(0x2A69)` round-robin store vs
`#12854` → `0x27B2`; `BITF *(0x577),#64` → `0x27BC`;
save AR6, `CALL 0x6B8`, restore, `SFTA a,3` / `SFTA a,-3`,
`STLM a,DXR0` (McBSP0 transmit register write). Full restore,
`FRETE` at `0x27CC`. `FRAME_ISR_ENTRY` follows at `0x27CD`.

## DISPATCHER_ENTRY `0x2E2F` (mask, shared spine head)

Multi-clause dispatcher, called by 3+ blocks and the resident ISR.
Clauses (offsets from entry, `program.be16`):

- `+0x00`: `CALL 0x05A0`; `BITF *(0x54D),#4`, RC; `MVKD *(0x54C)→*(0x853)` (MDIRCV-side word move); RET.
- `+0x0A`: `BITF *(0x549),#32` gate; `ANDM #-33,*(0x549)`; `CALL 0x2C88`; `BITF *(0x54D)` gate; `CALL 0x2E64`; RET.
- `+0x23`: `CALL 0x37D8`; `BITF *(0x866),#3` gate; `BITF *(0x2628),#0x4000` gate; `BITF *(0x250F),#0xD0` gate; `CALL 0x2E64`; RET.
- `+0x35`: `CALL 0x05A0`; `BITF *(0x54D)` gate; `CALL 0x942E` (drom-band); opcode match (`AND #255; XOR #0xF4`, shift, `XOR #5`); store kind `*(0x54D)`; RET.
- `+0x60`: `BITF *(0x866),#1` gate; `CALL 0x2D8F`; crit section (`SSBX INTM`): `PORTW pa1`, clear `*(0x866)` bit 1, `PORTR pa2`, mask, `PORTW pa2`; `RSBX INTM`. Direct port I/O under lock.
- `+0x7E` (`0x2EAD`): `BITF *(0x866),#2` → RC; `ANDM #-3,*(0x866)`; `CALL 0x2DE4`; RC aeq; `CALL 0x620`; `STLM b,ar4`; opcode-range check (`SUB #87` → `0x2ECD` bleq; `SUB #112` → `0x2EC6` bneq): in-range 88-112 → `CALL 0x43BA`; then `B 0x2E64`. Out-of-range high path: `LD #9,b`, recursive `CALL 0x2E2F`, `CALL 0x4590`, `B 0x2E64`.
- Computed jump: `ADD #-20415,a`, `LD *ar1,a` through saved AR1, `BACC a`. Landing zone shapes flags (`AR3=0x51E`/`AR4=0x54F` BITF/XC/ANDM/ORM from `*ar2` bits 10/9/8; `LD #0/1 → *(0x374)`), then a 6-field byte unpack (`*AR2+%`, `AND #255` lanes) to `0x36B/0x36D-0x36F/0x375/0x370-0x372` plus `MVDD/MVDK` moves to `0x2477/0x2544/0x2546`.
- Block-move cases: `TMPYU`, RPT-34/4 `MVDD *ar3+→*ar4+`, `BITF *(0x3EC8),#64` select, `ORM *(0x2627)`, recursive `CALL 0x2E2F`, `B 0x2E64`; flag-set cases (`ORM *(0x54F)` bits 10/7, `ST #0,*(0x545)`, zero-fill at `0x38B`, RPT-3 `MVDD`), each re-entering `CALL 0x2E2F` and converging `B 0x2E64`.
- `0x2E64` is the match loop, not an epilogue: `CALL 0x05A0`, `BITF *(0x54D),#4` gate, `CALL 0x942E` (drom-band), opcode match (`AND #255; XOR #0xF4`, shift, `XOR #5`), kind store `*(0x54D)`. Clause exits are RC/RET; every `B 0x2E64` re-enters matching.

## Shared spine: port-transaction routines (mask)

- `0x3986` command dispatch: `CALL 0x62E`; `SSBX INTM`;
  `ANDM #-3,*(0x263A)`; `BITF *(0x2639),#512` → skip strobe;
  `PORTW pa15` (RPT #6 delay); `RSBX INTM`; `IDLE 1`; relock,
  `BITF *(0x263A),#2` → recheck; unlock, clear, `RET` at
  `0x399D`.
- `0x399E` stream writer (follows the RET): `CALL 0x630`;
  `PORTW pa60` selects 3 then 5; BRC-3 `RPTB` loop over
  `PORTW *ar3+,pa57` with `LD/SFTA/ADD` lane math; `PORTW pa60`
  selects -4 then 2; `BITF *(0x7),#0x800`; `SSBX INTM`;
  `PORTR pa0`, `OR #96`, `PORTW pa0` (RPT #21); `XC`;
  `PORTR pa56` poll.
- `0x3EE1` RF-program sweep, `RET` at `0x3FC3`: `CALL 0x63E`;
  double `PORTR pa13` masked `0x3FFF`, `SUB`, loop until equal
  (two matching reads); `CALL 0x640`; `SSBX INTM`; `PORTR pa2`
  with `ANDM #-25` / `ORM #6148` on `*AR2` (`AR2=0x60` staging);
  sequenced writes `pa14←4999`, `MVDK *ar2→*(0x36A)`,
  `pa15←15000`, `pa4/9/5/7/10/47`, `pa13←0`, `pa11`, `pa8`,
  `pa0` (`ORM #13`, `ANDM #-481`), `pa1←-1796`; `RSBX INTM`;
  `pa32←0`; `pa33` triple-write (`ST #1154,*ar2+`, `ST #5250`,
  `PORTW *ar2` / `*ar2-`); `AR3=0x3E91`, `pa42←*ar3`;
  `pa48←187`; `pa3←0`; `BITF *(0x3EC8),#32` → `0x3FC4`;
  `CMPM *(0x3E7E),#2`; XC-selected `pa43←640/1696`;
  `BITF *(0x3EB5),#1024`; two `CALL 0x4007`
  (`LD #1696`; `LD #0` + `LD #13,b`); `RET`.
- `0x4007` port-0 transaction (single routine, `RET` at `0x40A0`;
  `0x4055` is its phase-two label): `CALL 0x652`; save regs;
  `BITF *(0x7),#0x800`; `SSBX INTM`; `PORTR pa0`, `OR #12`,
  `PORTW pa0` (RPT #22 delay); `*(0x3EB5)` bit-1 check
  (table-zone flag next to `FIR_COEFF_TABLE`). Phase one:
  `SUB #7` select, `PORTW pa40`, `LD #13,b` + `CALL 0x40A1`,
  `AND #3` select, `PORTR pa45` poll (`AND #4096`),
  `PORTW pa45/pa44`, RC. Phase two (`0x4055`): second pa0
  strobe, `0x3EB5` retest, `CALL 0x40A1` pairs with
  `AND #12/SUB #12` select and `AND #2048` check, `RC`/`RET`.
- `0x40A1` port-45 poll: `CALL 0x652`; `PORTR pa45`,
  `AND #4096` → skip; `OR #16,b`, `PORTW pa44` (RPT #14),
  `B 0x40B4` wait loop (`PORTR pa45`, `AND #4096`, `BNEQ`);
  `RET`.

## Open

1. Runtime IVT base per build. 3310 image runs the table at `0x0A00`.
   The emulator observed IPTR `0x0B` (base `0x0580`) on another
   build. Both cannot hold for one image. Needs per-build check.
2. `0x05xx` mini-kernel (`0x05DA/0x05DC/0x05E8/0x05F0/0x05F4/0x05F6`).
   Proven zero-filled in `program.be16` (verified all-zero
   `0x05C0-0x0610`): unobservable in-mask. Runtime source is the
   loader's `MVDP *AR2+(0x0D00)→0x590` ×421-word copy
   (loader.md `0x0F2B`). FLS hunt: no setB descriptor carries
   dest `0xD00` (3310 v5.79 table `0x300CD8`, 49 slots, 20 live;
   placeholders are consecutive 12-byte zeroed descriptor slots,
   e.g. idx 2/3 at flash 3156292/3156304). Two candidates left:
   (a) the payload hides in a zeroed/elsewhere descriptor —
   5110 documents block0 staged at DSP `0x0D00` by the HPI
   hardware boot (emulator `docs/dsp-boot-upload-architecture.md`
   §6); (b) the MCU HPI-writes the 421 words straight from ARM
   bootcode with no DSP descriptor. Masked callers into the
   window are real: `0xC851` head is `CALL 0x5EA`. Only
   referrer of `0x05FA` is the vector image itself.
3. Vector-to-line wiring (INT0-5, TINT, BRINT/BXINT) against LEAD.
4. `0x2B53` continuation past the HPI prologue (RF vs audio edge).
5. Callee bodies `0x05DA/0x05E8/0x05F4` (need `0x05xx` source first).
