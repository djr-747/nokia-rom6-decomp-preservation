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

## MCU side (3310 v5.79 symbols, static)

D→M opcodes with named handlers: `0x83` RSSI, `0x84` RA_INFO,
`0x88` neighbour timing, `0x89` channel changed, `0x8B` all-RSSI.
M→D vocabulary: open. Sender is `SWDSP_DSPMSG_HANDLER` (`0x278248`);
block01 holds the runtime dispatch (indirect via AR3, opener at head:
`FRAME 1`, flag `*(0x3EC8)`, `CMPM *(0x22C),#9`). No mask routine calls
into block01 (only reset → `0x0F00` does). Entry comes from uploaded
space: the `0x05DA/0x05E8/0x05F4` DARAM mini-kernel. Its source is the
pre-manifest HPI bootcode blob in the FLS. Recover that blob next.
