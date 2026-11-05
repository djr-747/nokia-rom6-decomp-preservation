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

## Open

1. Runtime IVT base per build. 3310 image runs the table at `0x0A00`.
   The emulator observed IPTR `0x0B` (base `0x0580`) on another
   build. Both cannot hold for one image. Needs per-build check.
2. `0x05xx` mini-kernel (`0x05DA/0x05E8/0x05F4`, maybe `0x05FA`).
   No 3310 payload covers `0x0580-0x0600`. Only referrer of `0x05FA`
   is the vector image itself. Hypothesis: pre-manifest bootcode
   (HPI ping-pong phase, bytes in FLS) installs it. Recover from FLS.
3. Vector-to-line wiring (INT0-5, TINT, BRINT/BXINT) against LEAD.
4. `0x2B53` continuation past the HPI prologue (RF vs audio edge).
5. Callee bodies `0x05DA/0x05E8/0x05F4` (need `0x05xx` source first).
