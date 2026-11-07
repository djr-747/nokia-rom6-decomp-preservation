# DSP PC-coverage oracle: 3310 mixed chain attempt, 2026-11-06

## Run

- Image: `firmware/3310/NHM-5/v5.79/Factory Reset 3310 NR1 v5.79.fls`;
  DSP image forced to ROM6 (`DSP54_IMAGE=build/rom6_full_stitched.bin`,
  identical bytes to the 8210 ROM6 program image).
- Command: `./run 3310 boot DSP54_COSIM=1 DSP54_IMAGE=... GSM_MIXED_CHAIN=1
  DSP54_PCHISTFILE=/tmp/pc_chain3310.txt` (250M steps, headless).
- Result: chain `FINAL VERDICT=FAIL leg=mt-call-1 transitions=0` (the ROM6
  MT-call wall — no MT leg transitions on either phone), but the run still
  executed 14,391 DSP PCs, 4,677 of them new vs the 8210 boot run, through
  SMS-adapter and 3310-MCU stimulus paths.
- `pchist.txt`: all 14,391 executed DSP program words as `addr count`.

## What it proves (beyond the 8210 boot run)

- `2FD3-3021` executes (1x, hot `2FFF-3001` lane x4): continuation of the
  `SUB_2F51` dispatch block past its `2FD1 b 2E64` tail, split per convention
  at the interior dispatch exit (`2FD3-2FE7` + `2FE8-3021`). Remaining
  `3022-3027` (incl. orphan `retd@3025`) unexecuted, stays dark.
- `8907-891B` executes (3x, `rptbd` body `8913-8914` x12): full 21-word gap
  is a `bitf/brc` repeat-minmax leaf abutting claimed `891C`.
