# 02 — Boot chain and the paged program API

> Dual block sets: one firmware image can carry **two** DSP block
> tables (confirmed: 8210 v5.29/v5.31). The MCU selects by the DSP's
> self-reported mask version over the HPI mailbox — see
> [doc 08](08-selector.md) for the directory format, poll, and gates.
> Fingerprint per build, never per model.
>
> Independent corroboration: the NSM-3 (8210) service manual §3 describes
> MAD2 WD1 as containing the "TI Lead DSP core" with "DSP code download,
> MCU interrupt handling vectors (in DSP RAM) and DSP booting" — the
> paged-download boot is documented Nokia service fact, not just our
> inference. The manual names no mask-ROM revisions; ROM3–6 live in the
> firmware world (DSP version byte + block sets), which is why this repo
> fingerprints images instead of quoting docs.

## Reset → run

1. MCU holds the DSP in reset (`0x20002` bit0 = 0) and drops bootstrap
   words into DARAM through the HPI window.
2. MCU releases reset (bit0 0→1 = "upload done" edge).
3. DSP boots from the mask ROM reset vector (`0xFF80`), sets
   `PMST=0xFFA8`, enables shared-access mode (SMOD=1), and enters the
   PROM superloop (ROM4: `0x3000`-region; ROM6: see `roms/rom6/`).
4. The MCU's DSP driver (3310 v5.79: real driver `0x2BC882`, serviced
   from IRQ4/DSP handler `0x2BCEF0`) uploads code blocks in two phases:
   a poll-driven bootcode download (`[0x100FE]` ping-pong) then
   interrupt-driven per-block upload.
5. Each block carries a 5-word header
   `{target, w1, size, offset, blocksize}`; `target` is the DSP run
   address, `offset` the staging word in the HPI window. The loader
   checksums in place — it does **not** copy — so window writes must
   hit the same cells the DSP fetches (see doc 01).

## Descriptor tables live in flash

The upload list is a RAM table of **flash pointers** to block
descriptors (3310 v5.79: table in RAM at `0x1107C0`), not one flat
array. Zero-length slots (`hdr.size == 0`) are placeholders, not
missing data. Relocation is **per-block**: branch targets inside a
block live in that block's TARG/link space, and the DSP↔TARG skew
differs per block (e.g. DSP `0D00`↔TARG `FD00` for block00).

## Observed on 8210 v5.29 (live boot trace, verified)

- MCU function at `0x2CB3AE` reads the silicon ID (`ldrb` from I/O
  `0x20000` = MAD2 ASIC ID) and copies it to DSP `0x8F1` via the HPI
  mailbox (`strh` to MCU `0x101E2`). Trace: mailbox cleared (`00`,
  PC `0x2CAE72`), then `0xA2` written (PC `0x2CB5CC`) — MAD2 rev 2.
- The uploader then walks master table A (`0x30CC58` → blocks from
  `0x30DD68`: entries `13D2/3E7E/09C6…` observed in UPLOADHEADER
  writes) — i.e. on `0xA2` silicon the **R5 set** is selected.
- Master table layout: header `[0000 0074 0013 <x>]` (`0x13` = 19 =
  payload count) + BE flash pointers; array A @`0x30CC58`, array B
  @`0x30CCD4`. Both tables sit adjacent in flash (same pattern on
  3210/5190/6190 images); the walker splits on a second loader block.
- NOT found: no `CMPM`/`BITF` test of `*(0x8F1)` exists in the ROM6
  PROM or either 8210 block set (searched `60xx 00A2` and
  `61F8 …8F1` forms) — the DSP-side check in the emulator profile
  comment is unconfirmed; the MCU-side copy + table choice is what
  the trace shows. The exact MCU branch between master A/B is still
  open (HPI-write PC attribution is unreliable; code region TBD).

## What "paged program API" means here

The uploaded blocks are overlays paged by the MCU: only a subset is
resident at once, staged through window regions (buffers A/B at DSP
`0x900–0xAFF` / `0xB00–0xCFF`), and they far-branch into PROM
services. So the PROM's callees only make sense with the callers:
annotate PROM routines together with the block call sites that target
them (`F073` targets), and record the direction — *page in, execute,
call down into ROM, return, replaced by the next page*.
