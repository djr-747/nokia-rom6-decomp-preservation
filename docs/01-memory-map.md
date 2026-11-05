# 01 — C54x / LEAD memory model (the contract)

Grounded in TI SPRU131G (CPU & peripherals) and SPRS039C (LC54x datasheet).
LEAD-specific addresses are firmware-correlated and marked as such.

## Terminology (these get confused — fixed definitions)

- **Mask ROM**: the factory-programmed on-chip ROM silicon itself. One
  physical array, two bus views (below).
- **PROM**: the *program-space view* of on-chip ROM — what the fetch unit
  sees (code). Our classifier's "PROM-code zone" means call targets in
  program space, not a separate chip.
- **DROM**: the *data-space view* of the same silicon — tables the DSP
  reads with data-bus instructions when `PMST.DROM=1`. Same bits as PROM,
  different bus.
- **`maskrom-acquired.be16`**: RAW dump off real hardware (proxy shim +
  cycle-gate reader over HPI) of program space **`0xB000–0xFFFF` only**
  (20480 words). Upper 20K. Nothing above is inferred; nothing below is
  included.
- **`program.be16`**: the loader's full-64K program-space runtime image
  (BE words). Upper 20K (`0xB000+`) is byte-identical to the clean
  `maskrom-acquired` window (verified by direct comparison); the low
  part is real content too (low/subprobe/block sweeps, stitched —
  see `sweeps/`, `archive/program-stitched-*`). It is the *promoted
  reconstruction*, not the raw acquisition (different hash, kept
  separately — see doc 03). Cite an address as silicon only with its
  window's provenance: clean-window vs stitched-low.
- **`drom.txt`**: data-space-view dump (`addr: word` text) from `0xB000`
  up, i.e. the DROM face of the same silicon.
- **Low ROM / lowrom**: program space below `0xB000`. Recovered via
  a different read path (shim/gadget sweeps, stitched) than the clean
  upper window — full-coverage in `program.be16`, but tag the provenance
  per address. (Separate concern: the emulator's *cosim compose flow*
  fills `0x0000–0x7FFF` with zeros + a ROM4-homology transplant window for
  trap-net discovery. That composed build artifact is NOT `program.be16`;
  never mix the two.)

## Overlay dynamics (per-mask — annotation must be mask-aware)

Boot `PMST = 0xFFA8`: `OVLY=1, MP/MC=0` (on-chip ROM live), `DROM=1`,
`IPTR=0x1FF` (vectors at `0xFF80`, always mask ROM).

`OVLY=1` maps DARAM over program space `[0x0080, ovly_end)` — and the end
**differs by silicon** (emulator bench + profile ground truth):

| mask | `ovly_end` | `[0x2000,0x2800)` fetches as | paging |
|------|-----------|------------------------------|--------|
| ROM4 (5110) | `0x2800` | uploaded DARAM (~500 F-block refs, RTOS tick `@0x241A`) | banked (`0x8000–0xDFFF` window, XPC, 2-word far frames) |
| ROM6 (8210) | `0x2000` | **mask ROM** (razor edge `0x1FFF→0x2000` = `F074`) | C542 single-page (fetch ignores XPC, PC-only far frames) |

Consequences: the same fetch address can be RAM on one mask and ROM on
the other; `FRET`/far-call semantics differ per mask; and the reset
vector's `B 0x0F00` lands in the OVLY window — i.e. boot flows through
*uploaded* code almost immediately, so "PROM annotation" that ignores
the uploader misses the boot path.

## The one structural fact

On-chip DARAM is a **single dual-access memory**. With `PMST.OVLY=1` it
is mapped into **both program and data space at the same addresses** —
fetch, read, and write of a DARAM address hit one cell. The HPI RAM is
a 2K-word block of that same DARAM, dual-ported to the MCU host. Model
it as **one store** shared by fetch, DSP data access, and the MCU
window, or uploaded code "never lands".

## Map (word addresses)

| range | space | contents |
|-------|-------|----------|
| `0x0000–0x007F` | low | MMRs + scratch (`0x00–0x1F` CPU, `0x20–0x5F` peripheral) |
| `0x0080–…` | OVLY DARAM | uploaded pages, RTOS state, rings, buffers |
| HPI RAM (LEAD, empirical) | dual-port DARAM | DSP `0x0800–0x0FFF` ↔ MCU `0x10000–0x10FFF` |
| `0x9000–0xFF7F` | on-chip ROM | PROM routines + DROM tables (`0xB000+` clean-window dump; below = stitched sweeps, see Terminology) |
| `0xFF80–0xFFFF` | vectors | `IPTR<<7 + vec*4`; reset `0xFF80` |

Boot `PMST = 0xFFA8`: OVLY=1, MP/MC=0 (on-chip ROM live), DROM=1,
IPTR=`0x1FF` (vectors at `0xFF80`).

## HPI control (MMR `0x2C`, SPRU131G Table 8-23)

| bit | writer | function |
|-----|--------|----------|
| DSPINT | host only | host→DSP doorbell (write 1 = interrupt the DSP; reads 0) |
| HINT | DSP sets / host clears | DSP→host interrupt |
| SMOD | DSP | 0 at reset = host-only; DSP sets 1 for shared-access mode |
| BOB | host | byte order select |

Host indexes the RAM with `HPIA & 0x7FF` (11 LSBs → 2K block).

## LEAD HPI window (firmware-correlated)

Window word `k` ↔ DSP `0x800+k` ↔ MCU `0x10000+2k`:

| field | word | DSP | MCU | dir |
|-------|------|-----|-----|-----|
| MDISND ring / tail / head | `0x00 / 0x52 / 0x53` | `0x800 / 0x852 / 0x853` | `0x10000 / 0x100A4 / 0x100A6` | M→D |
| UPLOADREQUEST / ready (`=0x12`) | `0x71` | `0x871` | `0x100E2` | D↔M |
| UPLOADREPLY | `0x72` | `0x872` | `0x100E4` | M→D |
| UPLOADHEADER (5-word descriptor) | `0x7B–0x7F` | `0x87B–0x87F` | `0x100F6–0x100FE` | M→D |
| MDIRCV ring / tail / head | `0x80 / 0xE4 / 0xE5` | `0x880 / 0x8E4 / 0x8E5` | `0x10100 / 0x101C8 / 0x101CA` | D→M |

MCU-side signals: doorbell = MCU `0x30000` bit2 (HPIC DSPINT);
DSP reset hold/release = MCU `0x20002` bit0.

Overlay run addresses (`0x926`, `0xD00`, `0xD80`, `0xF00`, …) fall
**inside** the HPI RAM — uploaded code executes where it lands.

## Prerequisites before PROM annotation (checklist)

1. Fetch-vs-data resolution for every annotated address: is this word
   reached via the program bus (PROM face) or the data bus (DROM face)?
   Same silicon, different semantics — label which.
2. Mask tag on every routine: ROM4-banked vs ROM6-single-page calling
   convention at each far call/return site.
3. Provenance tag per address: clean-window (`0xB000+`, cycle-gate
   dump) vs stitched-low (sweep/subprobe reads — striping-risk, see
   emulator `tools/archive/dsp_romdump.c` notes). Never present a
   stitched-low word with clean-window confidence.
4. Uploader-provided code treated as first-class: reset path, loader,
   and paged API pages are part of the executed image (doc 02, doc 08).
