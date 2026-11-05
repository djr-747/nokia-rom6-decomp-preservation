# ROM6 hardware edges: DSP ports + handler use (3310 v5.79, static)

Method: exact PORTR/PORTW decode per ti-c54x catalog
(`0x7400/0x7480/0x74F8`, `0x7500/0x7580/0x75F8`). 391 sites in the
clean window (`0x2000-0xB000`). Port address < 64 only. `build/rom6`
listings carry the full decode.

## Per-handler edges (from `roms/rom6/ivt.md` bodies)

| handler | vectors | edge use |
|---|---|---|
| `0x22DA` | V16 | `PORTR pa33` + `PORTW pa33`; `PORTR pa39,*AR6` ×4 (sample stream in) |
| `0x27CD` | V17/18/24 | `PORTR pa1/pa2`, `PORTW pa2`; `BITF *(0x20FF)` (mask-ROM status) |
| `0x25DF` | V20 | no ports; flags `*(0x51F/0x51C/0x577/0x4C2)` only |
| `0x2B53` | V25 | `PORTW pa1` ×2, `PORTR pa56`; HPI prologue `*(0x866/0x870)` |
| `0x3598` | resident V18 | no ports; mailbox + flags only |

## Port bank roles (all sites, clean window)

- pa1/pa2: frame traffic. Read and written by the frame ISR.
- pa33: bidirectional sample/control. W+R pairs across six routines.
- pa39: sample stream. Reads in V16; a 9-store write burst at
  `0x3B94-0x3BD3`.
- pa56: status read. V25 plus four mask routines.
- pa48/49/50: write-only control, eleven routines each. RF synth
  programming candidate. Owner list open.
- pa60: write ×14 cluster at `0x39A8-0x3ADA`. TX sample path candidate.
- pa0: R/W pairs (control/status ping-pong) at seven routines.

## Block attribution (payload port scans, PA<64)

- Audio/codec pages: block13 + block15 own pa1/pa2 (15: 4+11 sites).
  Matches `938c` McBSP/codec-init homology (port 0 R/W).
- RF programming pages: block01 + block06 + block08 own pa48/49/50.
  Audio pages never touch them. Split is clean.
- block08 is the mixed page: pa3/4, pa33/39 sample path, pa43-45,
  pa48-50 control.

## Identity dance (SIM-lock / MSID / COBBA ID)

Family protocol `0x70` (M→D) / `0x74` (D→M). Grounded in emulator
static RE (`simlock-table.md`, `00-mdi-catalog.md`, 3310 v5.79).

M→D subtypes: `0x13` MSID setup, `0x16` 24-byte SIML block,
`0x0D` aliveness, `0x17` final validation. D→M subtypes: `0x34`
(MSID), `0x35` (24-byte echo), `0x0D`, `0x36` (validation pass=0).
Consumer `0x2C1948`; OPER dispatch `(op&0xF0)==0x70`.

Record loop: MCU sends a 30-byte frame (`0x1A 0x70 0x16`, len 24)
with the encrypted record from nonvolatile offset `32+24*cursor`.
Backing store is per-model ground truth (emulator profiles):
I2C EEPROM on 3210 (NSE8), 5110/5110i/5130/5190/6190 (NSE1),
6110/6130 (NSE3), 6150 (NSM1), 8810 (NSE6); in-flash EEPROM on
the rest (3310 family, 8210 family, and later);
DSP decodes and returns it in d2m `0x74` (`msg[+12..35]`,
more-records flag in low nibble, eor checksum at `msg[+60]`);
`0x287BE8` copies it to table `0x10EB48+cursor*24` (24-byte stride,
10 records). Table compare mask `[0..7]` (packed-BCD IMSI,
reject-all seed `8×0xEE`) comes only from the ROM seed or the DSP
copy. Evaluator `0x286F68`; accept gate `0x21C630`.

DSP-side decode routine still unlocated (no absolute opcode store
in any setB payload; writes go through pointers). COBBA-ID read
site open.

## RSSI and camping (3310 v5.79, static)

D→M reports enter via `GU2_MDIRCV_BOOT_DISPATCH_TABLE`, gated on
`GU2_DSP_MEAS_OPER_GATE (0x110FE0)==1`, then forwarded with
`TASK_SEND_TYPED #10`. Ingest fns: `0x83` RSSI `0x2C3690`,
`0x88` neighbour timing `0x2C3CFC`, `0x89` chan changed `0x2C3D4C`,
`0x8B` all-RSSI `0x2C3FC4`.

Camping is a state ladder in `GU3_NET_CAMP_STATUS (0x110F96)`:
states `0x1A/0x20/0x30/0x40/0x44/0x80`, dispatch at `0x22EB50`
(RR region `0x224xxx-0x231xxx`). The `0x88` handler advances camping
when status `!= 0x1A` (sends `GU3_TASK10_ADVANCE_TEMPLATE`).
DSP producers use AR-indirect writes (no absolute opcode store in
any payload); producer-side mapping open.

## Tuning upload (NVRAM → DSP)

Consumer side (block08, 3310 setB): absolute forms
`PORTW *(0x8/0x9/0xB),pa{3,4,5,7,8,12,32,48,50}` and
`PORTR pa{1,2,3,33}` plus AR2-streamed `PORTW *AR2,pa{33,36,49}`.
Tune/control structs live in low DARAM; tables stream through AR2
to synth ports 48/49/50. The MDISND opcode that fills those structs
at boot stays open (candidate: channel-configure family around
`0x02→0x89`; trace the boot-time builders, not the traffic path).
Tune values come from the per-model store (I2C vs in-flash, above).

## Hardware line and shared cells (3310 v5.79, emulator static RE)

| cell | width | role |
|---|---|---|
| `0x100DC` | u16 | m2d doorbell, busy-gate (`==0` writable) |
| `0x30000` / `0x20008` | wr | DSP kick / raise, after word write |
| `0x100E4` / `0x100E0` | — | m2d ch1/ch2, dead (sole caller passes `r0=3`) |
| `0x10000` | ring | shared APIRAM ring storage |
| `0x101C8` / `0x101CA` | u16 | d2m head (DSP-advanced) / tail (MCU-advanced) |
| `0x100A4` / `0x100A6` | u16 | m2d ring head / tail, 82 slots |
| `0x2000C` | u8 | IRQ mask (saved/restored in crit section) |
| `0x2000A` | u8 | DSP set/ack flag, drain clears bit1 |
| `0x2006D` | u8 | ASIC serial-bus status, busy-poll `bits[1:0]==3` |
| `0x20011` | u8 | HW id/status, folded into anti-tamper checksum |
| `0x111861` | u8 | operational latch (0=BOOT, 1=OPERATIONAL) |
| `0x111862` | u16 | DSP-liveness counter |
| `0x111390` | u8 | DSP_STATE, bit0 = DSP up |
| `0x110F96` | u8 | run-state enum `{16..24,26,80,81,82}` — WEAK, semantics open |
| `0x11FF94` | u32 | reboot reason latch |

`0x9E` joins the operational fan-out (`0x8D/0x8E/0x95`, `0x70`-family);
no separate handler found.

## MCU side (3310 v5.79 symbols, static)

D→M opcodes with named handlers: `0x83` RSSI, `0x84` RA_INFO,
`0x88` neighbour timing, `0x89` channel changed, `0x8B` all-RSSI.
M→D vocabulary: open. Sender is `SWDSP_DSPMSG_HANDLER` (`0x278248`);
block01 holds the runtime dispatch (indirect via AR3, opener at head:
`FRAME 1`, flag `*(0x3EC8)`, `CMPM *(0x22C),#9`). No mask routine calls
into block01 (only reset → `0x0F00` does). Entry comes from uploaded
space: the `0x05DA/0x05E8/0x05F4` DARAM mini-kernel. Its source is the
pre-manifest HPI bootcode blob in the FLS. Recover that blob next.
