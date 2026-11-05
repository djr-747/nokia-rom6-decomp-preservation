# Worklog + ROM image understanding / coverage

This log is a running record. Entries run newest first. Dates are UTC.

## 2026-11-05 — night five: 60 symbols, reproducible coverage (46.5%)

- 10 teams + critic + entry-linear validation; 60 new symbols (427
  total), 66/66 entry-exit pairs objdump-verified, 9 apparent
  mismatches resolved as bound-vs-exit confusion, YAML valid,
  `make test` 6 pass. Commit `dd7dadc`, pushed.
- Landed: 56FC-5F4A lane (8), 6B14-78B5 DSP chain (14), BFAA-C5F8
  normalize lane (9), 3xxx port writers (9), ISR/dispatch + 50B2
  feeder (7), 9FCF EB9E-table gater, 7937 mode-22 leaf, small-gaps
  west (9). 0x50B2 feeds 0x2D5E ISR (calld @50F9) and stages IDBUS
  words 0x2F61/0x2F62 (`F072 5194` rptbd fill).
- Corrections: 2D5E not sole-called from 50F9 (9 image-wide F274
  callers); 4F5F calld opcodes; 6B26 head extent; 56FC dedup;
  3E53 split around 0x3EBD FIR table word (bounds 3E53-3EBC +
  3EBE-3EE0).
- Coverage method fixed: `tools/coverage.py` parses bound/first-RET/
  true-end/RET-at/words-to/adjacent/len patterns from notes, merges
  intervals, `make coverage`. 25,715w = 46.5% of 0x2800-0xFFFF.
  Supersedes ad-hoc 24,558w/42.4%. Window size corrected: the
  window holds 55,296 words, not 57,856 (that size is 0x1E00-0xFFFF).
  Six parsed bounds spot-verified against image bytes. 50% needs
  27,648w; 1,933w remain.

## 2026-11-05 — night four: 50 symbols, RETE + callerless rulings

- 8 teams + critic + follow-up + gap-followup (whole-image linear
  sweep closed the caller-alignment caveat for 34/34 7Cxx callers:
  1272/1274 F074 + 549/549 F274 sweep-recognized, only 2
  non-call F074 are immediates). 50 new symbols (367 total), all
  entry/exit pairs re-verified, YAML valid, `make test` 6 pass.
- 96BD RETE RULING: first fall-through exit is trete @96FF, not
  TRETE @96FD (0x96FD is F074 call 0x97DD -- stale identity-chain
  note corrected); bound 96BD-96FF unless rete counts as exit.
- C7A4 callerless FALSIFIED: C721 F930 cc 0xC7A4,tc is the sole
  image-wide static transfer in (full 64K operand scan, one hit).
- 95A9 = computed table-dispatch via bacc (no table at 95AA);
  AF57 = 6-way selector dispatch CONFIRMED (AF64-AF69 tables,
  handler heads verified, calld 0xa2b9 lanes).
- 2F61/2F62 CLOSED at ROM level too: mask writers 0x4BD7
  (staged fill 2F5D-2F68) and 0xB750 (120-iter RPTBD walk
  2F18-2F8F); DP-relative avenue bounded-negative (DP
  setter/closure audit: DP=0/20/22 airtight, no 0x5E evidence).
- Corrections applied: 97DD has FOUR callers (9530/96FD/9735/
  9747); 95A8 is 4813 ldm ar3,a; A74C is 14 calls (ccd @A794 is
  FB20 to BAC2); B767 elided stms restored; 4BD5 b is pre-entry.
- Open: 952E/953C/A815 bounds, 61C4 label, 283D semantics,
  staged VMA, E9EE 8-vs-16 width, AED9 consumer, 56BD role,
  fcall-form caller convention, rc/cc exit-rule convention.

## 2026-11-05 — night-three leftovers: 2F61 writer found, 7 bounds shrunk

- 8 teams + critic + follow-up + synthesis; 53 new symbols (317
  total), all entry/exit pairs re-verified (51/51 clean), YAML
  valid, `make test` 6 pass.
- `0x2F61/0x2F62` feeder hunt CLOSED at block level: block06
  file-off 0x134 writes *(0x2F62)=0xFFFF (+C1BF/FFEE/FFF9,
  zero-fill); block06 file-off 0x1F0 RMW path; block09 file-off
  0x504 pointer + calld 0x0D6C (overlay-RAM callee, store
  unverified). MCU-staged fill confirmed; DP-relative stores not
  exhaustively excluded.
- D3BE overlap RULED: no single D3BE-D5D5 routine (interior
  true-called entries break it); span = 5 called routines + 4
  forward-chained shared tails, all with own ret/retd.
- C7A4+ RULED: C7A4-C7B0 is a boundable callerless routine;
  C7B1-C850 is a bounded negative (zero FC00/FE00, noreturn
  worker, exits to C878/C8F8/C8FE/283D).
- All-paths upgrades on 14 routines: 7 spans shrunk (E674->E794
  fbacc, E837->E854 fbacc, E583->E59C retd, 8675->867D retd,
  86FB->872A retd, 8821->8853 bacc, E923->E9A0 fbacc), 5 kept with
  new head-rc exits (A4D5/B358/D0BE/A4DE + B3B1/CFBD single-exit
  confirmed).
- 96BD RETE convention: first fall-through exit is RETE @9737
  (F4EB objdump-verified); bound semantics open, symbol untouched.
- Post-exit remainders (E795-E79C, E855-E8E3, E59D-E625,
  E9A1-E9C7) and cap-overflow drafts (DB4A/DB8C/DC77/DD3A/DD77/
  DD9B/DFCF + caller-less tails) deferred to night four.

## 2026-11-05 — night-two span survey: high region is code

- 8 teams + critic + follow-up + synthesis; 101 new symbols after
  parent validation (264 total). Every entry/RET pair re-verified
  against image bytes; 9 bounds SHRUNK after entry-linear decode
  exposed interior retd exits the FC00-only scans missed (0xCEB4,
  0xE06A, 0xE38A, 0xE4DD, 0xE526, 0x7E4D, 0x7FC6, 0x807F, 0x90F8);
  2 claimed bounds confirmed against operand traps (0x9004,
  0x918C: interior FC00 words are immediates, not exits).
- All-paths exit upgrades: 0x62F2 ends retd 0x63D7 (FC00 0x643D
  belongs to 0x63DA), 0x676A 4 exits, 0xA4DE head rcd + downstream
  chain exits. STATE_WORKER 0xC851 has no own RET (0xC85C is E900;
  falls through into 0xC85D).
- Killed: mopup 0x9F42 (duplicate of existing AUDIO_ENGINE_9F42).
  Ruled out: D3BE as single routine (interior true-called entries
  D447/D55E/D571 break it; left undrafted).
- Negative results standing: 0x2F61/0x2F62 writer (no direct store
  in image), ROM-resident FIR taps 0x3400-0x4000 (true taps are
  data-space 0x3EBD+), F000-FBFF (data tables, code ends E9C7).
- Open: mid-routine F274/F072/FB labels, 26 undrafted D-span
  entries, inner labels 0x7E88/0x7F95, C7A4+ tails (no FC00 to
  0xC851), D3BE overlap, E9C8-E9D5/F000-FBFF table semantics.

## 2026-11-05 — night-one span survey: 13.5% bounded (was 5.3%)

- 9 span teams + critic + follow-up + synthesis (workflow); 46 new
  symbols, all entry/RET pairs re-verified against image bytes
  (47th claim, 0x4348 FC00 exit, falsified and corrected to RETD
  0x434C). 163 symbols total, YAML valid, `make test` 6 pass.
- Coverage metric: bounded routine/table words over 0x2800-0xFFFF
  (57,856). Now 7,810 words = 13.5%. 50% needs ~28.9K.
- Landed: A-cluster message setup (A482/A4DE 11 callers/B3B1 12
  callers), audio pair A7B7/A7EB, RF_MEAS B461, span-8674 dozen
  (superblock 8C0A len 465), B/C-series workers (FIR B743, BA32,
  BCC8, B6E6, BCFC, BF8C, C5F9, C717, BE22, BBEF), 3460-39A4
  dispatch band, 40BC-44A5 port/arith band, 4660 poster-loop head,
  51D8 dispatch head. Roles stay HYPOTHESIS; bounds first-RET.
- Open: all-paths exits, role proofs, 0x0590 slot contents,
  0x2F61/0x2F62 feeder writer, 0x3EBD FIR taps (claim disproved
  there), 43EA/44BD-class entry via 4433 cala table.

## 2026-11-05 — repo published; memory-map terms fixed; RF topology in

- Repo live: `djr-747/nokia-rom6-decomp-preservation`, baseline commit
  `1f8bfb0`. observed: the pushed tree holds zero ROM bytes (no
  `.be16/.bin/.fls/.img/.hex` in `git ls-files`).
- `docs/01-memory-map.md`: fixed PROM/MaskROM/DROM/program.be16/lowrom
  definitions after byte-verifying `program.be16[0xB000:]` ==
  `maskrom-acquired.be16` and nonzero low content. Provenance tags
  (clean-window vs stitched-low) replace the old "undumped gap" claim.
- `docs/04-stimulus-catalog.md` §7a: added PLUSSA_CRFU vs HAGAR contract
  split (RACH report edge, capture geometry) plus per-phone map.
- `docs/08-selector.md`: confirmed 3210-B as ROM6 by page-identity with
  8210-B (19/24 PROM, 12/12 DROM, 0 vs 8210-A).

## 2026-11-04/05 — selector mechanism closed (prior session)

- 8210 v5.29: HPI mailbox poll → version word `[0x13577C]`, accept 5/6.
  `==5` selects set 1 (R5-shape). Other values select set 2 (ROM6,
  27/28+12/12).
- 5190 v6.11: `==3` selects set 1 (R3-witness). Other values select set
  2 (ROM4).
- 3210 v6.00: flag gate selects set 1 ROM4 / set 2 ROM6.
- Documented dual-set directory format (`DC0000DC`,
  stride/cell/pointer-lists).
- Counted bulk: 58 ROM6, 36 ROM4, 17 R5-witness, 10 R3-witness, 0
  ambiguous.

## ROM image coverage tracker

State words: `done` / `partial` / `open`. "Understanding" means
annotated meaning. "Coverage" means fraction of window disassembled
plus inventoried.

| image / window | provenance | disasm | understanding |
|---|---|---|---|
| ROM6 `program.be16` `0xB000–0xFFFF` | clean cycle-gate dump, byte-verified | done (`vectors/branch/prom.lst`) | partial (reset path verified; handler inventory open) |
| ROM6 `program.be16` below `0xB000` | stitched sweeps (striping-risk) | done (same listings) | open (provenance-tag per address first) |
| ROM6 `drom.txt` (`0xB000+`, data face) | acquisition text dump | open | open (DROM-shape catalog = goal item) |
| ROM6 uploaded blocks (3310 etc.) | per-build manifests committed | partial (payloads in `build/`) | partial (Viterbi cluster sig'd; full xrefs open) |
| ROM4 `program.be16` / `drom.txt` | loader images, verified hashes | done (`build/rom4/prom.lst`) | partial (runs in emu; annotation ports open) |
| ROM3 / ROM5 mask images | none (witness sets only) | n/a | open (mechanism-backed, no bytes) |
| MCU DSP driver (3310/8210/5190/3210) | `disfw` static reads | partial (poll, gates, uploader) | partial (call/SMS + RF/audio edges open) |

## 2026-11-05 (later) — static ROM6 completion

- `roms/rom6/ivt.md`: runtime IVT image (block23 = block0F), 7 populated
  vectors with FB handlers, prologues for `0x22DA/0x27CD/0x25DF/0x2B53`,
  resident `0x3598` entry, block00 branch table (12 slots).
- `roms/rom6/edges.md`: 391 port sites (PA<64, clean window),
  per-handler edges, port bank roles, MCU D→M opcode list.
- `roms/rom6/drom.md`: upper-mask segmentation (code `B000-B5FF`,
  tables `CA00-CDFF` / `EA00-F0FF`).
- `roms/rom6/homology.md`: ROM4→ROM6 analogue ports with deltas.
- `roms/rom3/README.md`, `roms/rom5/README.md`: rewritten with witness
  census (10 R3 tables / 6 phones; 17 R5 tables / 4 phone lines).
- Style pass complete and verified: facts intact.
- xrefs staged at `/tmp/xref/3310-setB-xrefs.json` (block01: 47 ROM
  targets; shared core `0x2E2F` = ROM4 `3900`).
- Loader1 decoded: IPTR `0x0F` (vectors → `0x0780`), `0x0590`
  mini-kernel = block00 copy, upload engine on `0x87B-0x87F`.
- Version path closed: mask `0xFF87` (`6` ROM6 / `4` ROM4, verified)
  → `*(0x802)` → MCU `[0x10004]` → gate. Block48 publishes it.
- Method rule: annotate in bring-up order (doc 05). Dedicated mode
  comes last.
- Identity dance grounded in emulator static RE: `0x70/0x74` family,
  subtype map, 24-byte record loop, table `0x10EB48`, bridge
  `0x287BE8`, evaluator, accept gate (edges.md). DSP decode routine
  and COBBA-ID read site still open.
- RSSI/camping grounded: ingest fns `0x83/0x88/0x89/0x8B`, gate
  `0x110FE0`, camp ladder states, `0x88` advance rule (edges.md,
  messages.md). DSP producer mapping open (AR-indirect writes).
- Tuning consumer side mapped (block08 structs + AR2 streams to
  pa48/49/50); boot-time tune opcode open.
- Cosim worklog mining (plan, all static): hardware/RAM cell table +
  MDIRCV routes in edges.md; flash seeds (nibble gains + 1dB curve,
  byte-side source) in drom.md; span deltas + closure/flywheel/tool
  rules in homology.md; MT-call sequence (PAGE→TCH ASSIGNMENT) noted
  for stages 6-7. 5110 call worklog is runtime E2E (no routine pins);
  registration worklog likewise (timings only). 12/12 tests pass.
- Cosim worklogs mined: MDISND two-channel contract (doorbell
  `0x100DC` + 82-slot ring, subtypes 2/3/5, ch1/2 dead) and MDIRCV
  dispatch (boot table `0x2EDB48`, operational routes, `0xE4`
  keep-alive) folded into messages.md. Latch `[0x111861]`,
  DSP_STATE `[0x111390]`, liveness `[0x111862]` noted.
- Payload identity resolved (build idx → manifest → run range);
  upload is phased with overwrites (`0x0A00`, `0x0F00`, `0x0930`).
  Cross-phase static call graph needs the phase order (xrefs.md).

## Goal mapping

Active goal "Static ROM6 completion" maps to tracker rows. Vector and
handler inventory maps to ROM6 upper plus blocks understanding. RF and
audio edges map to MCU driver plus §7a. Block↔ROM xrefs map to blocks
understanding. DROM shapes map to `drom.txt`. Homology ports map to the
ROM4 row.
