# DSP PC-coverage oracle: 8210 boot to registration, 2026-11-06

## Run

- Image: `firmware/8210/NSM-3/v5.31/Nokia 8210 NSM-3 v5.31 A (EEPROM).fls`
  (curated 8210 pick in `run`; ROM6 DSP program image).
- Command: `./run 8210 boot DSP54_COSIM=1 DSP54_PCHISTFILE=/tmp/pc_full.txt
  DSP54_DATADUMP=/tmp/dsp_daram_full.bin` (250M ARM steps, headless).
- Result: `REG-RESULT verdict=REGISTERED` (full boot, camping, LU).
  ~205M DSP insns; histogram cumulative from last warm reset (run-mode).
- `pchist.txt`: 10,476 executed DSP program words as `addr count`.
- `emu-oracle.patch`: uncommitted emu worktree diff that produced it —
  app-edge 64K histogram (`DSP54_PCHISTFILE` knob, first-install wins
  over the bridge sampler, atexit dump) plus a 3-line core getter.
  Bridge `PCHIST`/`PCHISTWATCH`/`DATADUMP` facility itself is committed
  upstream work, reused as-is.

## What it proves (ROM6 0x2800-0xFFFF dark gaps)

262 executed gap words in 12 gaps (vs merged `symbols.yaml` bounds):

- `28CF` head + `2917-294C` body execute (~10.7K×): the `28CE` BACC-B
  computed dispatch lands here (`*(0x546)` selects it).
- `2F51-2FD2` executes (6×): a `2ED5` BACC-A RAM-table target block.
- `3273-32ED`, `3306-333B`, `3115-311E` execute from their heads.
- `3779-379E` executes in two dispatch-loop lanes (split at `32B2`-style
  interior `b 2E64` exits per convention).
- `7EEC-7F1B` lane run executes (9×); `3179-3194` executes (2×).
- `345B-345F` execute (9×) into `DISPATCH_CMP_3460`, including the
  `345F` extension word as an instruction head (mid-instruction computed
  entry; corrects the "data, not an entry" verdict).
- `3557-355B` + `35A0-35BA` execute (2×, `bc` lane).
- `AE70` ret-stub (10,682×) and `AE71-AE9F` dispatch prologue (10,682×,
  rare `AE8E` lane 37×) execute; `AEA8-AEAC` leaf executes (10,682×),
  refuting the post-retd-orphan kill.

Unexecuted gap words are NOT claimed (other scenarios — MO/MT call,
SMS — may light them; dedicated-mode code is the expected remainder).
