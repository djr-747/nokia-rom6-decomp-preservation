# Worklog + ROM image understanding / coverage

This log is a running record. Entries run newest first. Dates are UTC.

## 2026-11-05 — second half wave-3: 76.5% bounded (was 72.4%)

- 4 teams + critic + parent adjudication; 40 new symbols (652 total),
  STUB_A361 trimmed, 9A82 note fixed, `make test` 6 pass. Commit
  pushed; `make coverage` 42,289w = 76.5%. 13,007w dark remain.
- Critic kills honored: TABLE_AF64 (dup of JTAB), FRAG_6657 (overlaps
  6666), FRAG_4533 (overlaps 454F), 5B5C/86CF/A815/A91C (no valid
  entry), 28CF/7EBC (fall-through-after-BACC validity open), C7B1
  (standing BOUNDED-NEGATIVE ruling, reversal deferred), 9700/970B
  (inside ROUTINE_9682), 2983-single-span (trimmed to first outside
  exit [2983-29B0]), B0E8 (entry claim falsified: B0E6=F073, not
  F820 — byte proof).
- Critic demotions honored: 7DB5/B41C/E8C7 ROUTINE->FRAG (entry class
  insufficient). Critic error corrected with bytes: F273@2A86 is
  UNCONDITIONAL (catalog exact 0xF273), not conditional — FRAG_2A73
  split multi-segment [2A73-2A89]+[2A8A-2ACB] instead of single span.
- STUB_A361 trimmed A361-A3BD->A361-A3A2: interior retd@A3A0 ends it;
  MSG_WORKER2_A3A3 double-claim resolved (trim, other symbol kept).
  3044 verdict: BOTH (Harvard alias — program word F330 inside
  FRAG_303F, data cell RSSI counter; no self-modifying code).
- 9331 written over provisional 9343 point label (interior loop
  descriptor, no entry/exit — 4055-precedent interior label, no
  conflict). A2C3 over-claim investigated: interior F073s all target
  A31D interior — stands, no change. 942E/9459 double-claim recorded,
  no action.
- BACC census: 16 sites, selector idioms mapped (A254/AF63/AFB4/B128/
  B176 + tables; 8346-table arms; 95A9/97FF computed; 2ED5/43CC
  epilogues; 538C vector followers; 8853 unreached into 88B9).
- Open (wave-4): C7B1-reversal, 28CF/7EBC fall-through validity,
  F84x/F072/F808 catalog classes, A269-A2AB/A2AC-A2B8 done this wave;
  dead lanes 3273/2C75/2BED-zone/3802/351D/994F-tail/DA7E/7CB6/7EC5/
  B39E/E855/5DF4/33E8/DARK_2AFC/29B1-2A72/4660-middle/A91C/A815/
  670D-rest/88B9/3044-sliver-3115/A91C/A3CE-stub/AE71-lanes/AEA0-lanes/
  B0E8-dead/AE87/AEA8-arms/929E/9239/3044-zone-tail + residue gaps.

## 2026-11-05 — table-bound batch: 72.4% bounded (was 65.8%)

- Parent synthesis: AFD3-AFF8 rescued as bacc-table-arm frag
  (AFB5-table slot 1 lists AFD3 — same entry class as B12F arms;
  AFAB-table list corrected AFF3->AFD3 per image bytes); A25A/A25F/
  A264 stubs byte-verified (F274 A2B9 + stm + FC00); TABLE_AFB5/
  B129/B177 symbols; parseable Bound sentences on F000-FBFF (3072w),
  E9EE-EB9D (432w), E9C8-E9D5, AE6C, AEAD, 4433, AF64, A249 head+table.
  `make test` 6 pass; `make coverage` 40,034w = 72.4%. 15,262w dark
  in 179 gaps (71 >=80w). Wave-3 = BACC/dispatcher-arm sweep.

## 2026-11-05 — second half wave-2: 65.8% bounded (was 60.4%)

- 6 teams + critic + parent adjudication; 90 new symbols (605 total),
  A249 note corrected, table use-evidence appended, `make test` 6 pass.
  Commit pushed; `make coverage` 36,364w = 65.8%. 18,932w remain.
- Mesh-rule ruling (inside/outside targets, WORKER_3199 precedent):
  interior unconditional branches to interior targets are joins
  (kept); to outside targets are early-outs (trim/split). OVERRIDES
  of critic kills with byte evidence: FRAG_303F stands (3 interior
  joins + single outside exit @3113; bound corrected 303F-3114, FC00@
  311E is 311F boundary ret), FRAG_9C13 stands (single interior join
  9C2B->9C35). Kills upheld: 2983-2B52 (no entry, BACC-reach
  hypothesis), 2EC6-3027 (2F00 overlap), A3/A5/A10, AFD3-AFF8
  (zero external entries re-confirmed), 65AA-old, 2BED-zone splits
  recorded dark with reasons.
- Trims: 2875-28A4 (48w, outs at 28A3/294B), 2BAA multi-segment
  (2BAA-2BEC + 2BED-2C02 via interior 2BE2 join), 2C03 (relabel FRAG,
  2C03-2C74; 2C75-2C87 dark), 3267-3272 (12w), 9BC3-9BF4 (50w),
  6993 split (SUB_6993 698B-69A8, mid-entry 4x ext F274),
  8B9D->ROUTINE (4x F274 entries).
- Landed: 19 T6 88xx-9Dxx/A3xx (incl A3BE/A3C5/A3D5/A3E1 chain,
  89EB/9D0B/33CE frags), 12 T4 57xx-87xx, 7 deferred (incl 6666 lane,
  6973 split-off, 6954), 12 T5 mid posters, 12 B-lanes (F820-fall-
  through paradigm), 13 B-frags (table-arm entries), 8 mesh frags.
- F84C/F84D catalog question recorded (mask arithmetic suggests FB
  far-branch; binutils renders bc + behavioral fall-through evidence
  wins; wave-3 item: run F84C through ti-c54x decoder test).
- Open (wave-3 BACC/dispatcher sweep): all no-entry dark lanes
  (2983-2B52, 28A5-2969, 3273-32ED, 33E8-345A, AFD3-AFF8, 3044-zone
  decider via 0x0B92 audit, A25F-A2B8 arms, 2C75-2C87, B0E8, A91C,
  A815, 670D/6657/372E/3662/3802/351D, 7A4B dead confirmed); pre-
  existing double-claims STUB_A361/A3A3 + A2C3 over-claim (flagged,
  not changed); F981/FB81 far-call review (keep-as-non-call upheld).

## 2026-11-05 — second half wave-1: 60.4% bounded (was 50.4%)

- 6 teams + critic + parent validation; 70 new symbols (515 total),
  2 note fixes, `make test` 6 pass. Commit pushed; `make coverage`
  33,389w = 60.4%. 100% needs 55,296w; 21,907w remain.
- Convention adjudicated vs ti-c54x reference core catalog: F073 =
  B unconditional exit (exact 0xF073); F820 in BC mask F800/FF80 =
  conditional, NOT an exit (fall-through continues); F273 = BD exact
  0xF273 unconditional-delayed, IS an exit (bound ends pc+3);
  F4E2/BACC + F6E2/BACCD end linear bounds (no fall-through);
  F981/FB81 = FCALL/FCALLD per catalog (calls, fall through for
  bounds) — repo branch-convention kept for bounds, deviation
  recorded; FB81/F981 interior-call lists provisional pending
  far-target decode (wave-2 item).
- Killed by adjudication: P2 AF/B lane splits (rested on F820-as-exit,
  contradicted by catalog + objdump bc/bd renders); P5 A3 (overlaps
  existing 2F00 entry), A5 (code-vs-data conflict at 3044, no entry),
  A10 (no static entry); AFD3-AFF8 (zero external entries
  whole-ROM scan); 4533/4590/463B drafts (swallow existing poster
  symbols); 65AA team bound trimmed 6656->65ED (two unconditional
  F273->676A early-outs found by parent check); 4DA7 bound 4DD9 not
  4DDA (catalog BACCD = 1-word op + 2 delays).
- Landed: 12 msg/setup symbols (9B5C/9C4D/9C61/A87F/A8BF/A8D4/A8FE/
  AA7C/AAC7/AB2C/AB56/AB78), E9A1 code + EB9E/FC00 tables + FF40 run
  (3 sub-entries) + FF78 traps + FFC0 BD-vector slots (->22DA/27CD/
  2B53) + 6 AF57 jtab leaves + AF92/AFAB/AFBF (20w, ret@AFD2), 12
  P3 8xxx/5xxx spans, 8 P4 mid spans (4883 frag zero-callers; 4944
  ext-called @A4DB; 4BA8 4x ext; 4DA7 baccd-dispatch), 9 P5
  dispatcher/low spans (B2 169w incl parent-verified joins; B1 weak
  head caveat kept), 12 P6 64xx/68xx/36xx (5 called + 7
  branch-entered frags incl 65EE 9-entry lane).
- Parent validation: 63-claim scripted entry-linear check (7 flags
  all resolved: interior joins verified, AFBF ret@AFD2 found by
  objdump slice, 65EA early-out, 4DD9 delays); 2F00 note capped at
  retd@3025; all new heads/callers byte- or objdump-verified.
- Open (wave-2): P2 killed lanes re-walk (F820-conditional bounds),
  6A1E (bcd->6D47 escapes), AFD3-AFF8 + 33E8-345A + 3044-span
  (no-entry, BACC-sweep), 4533/4590/463B-region branch stretches,
  P1 dark chunks A815-A87E/A91C-AA7B + runner-ups, FB81/F981
  far-call review, S1a loop-guard, 65EE-lane interior verification.

## 2026-11-05 — final push: 50.4% bounded (goal met)

- 2 survey teams + critic on 5282-56DD (1,116w), 5823-59DB, 4F6E-50B1,
  795D-7AE4; 18 new symbols + 3 corrections (445 total), `make test`
  6 pass. Commit pushed; `make coverage` 27,867w = 50.4%.
- Landed: DISPATCH_SLED_A (7 branch-entered fragments, loop-guard
  caveat recorded), DISPATCH_P_ENTRY + 9 P-lanes (all converge 54BB;
  P4/P7b tail-merge via 53CD), TABLE_56BD (33w data), gap1 R-chain
  (5825/58E0 called; 5886/5905/5993/5823 callerless fragments),
  gap2 R-chain (4F6E/4FC2 called; 4FF6/500B/505B fragments, 5009/500A
  delays unowned), SUB_7967, SUB_797C (trimmed 797C-7A4A after
  parent byte-check found 7A49->7AE5 early-out the team missed),
  FRAG_7AB1 (branch-entry tail 7AB1-7ADD).
- Corrections: 54BB note (K3 — RPTBD/RET belong to 54A4; proper body
  is J1+J chain, first exit F073->5503 @54F6); 54A4 bound 54A4-54BA;
  7937 owns delay tail through 7966 (all four 795D refs now
  objdump-verified, resolving the word-only caveat).
- Parent validation: 43 entry/exit pairs byte-checked (2-word
  F073-exit address rule; retd bounds end on delay slots with exit
  addr in note); all interior F073/F273 targets confirmed interior;
  14 call sites objdump- or byte-verified.
- Open: 7A4B-7AB0 (no entries found), 7ADE-7AE4 (post-exit tail),
  5009/500A delays, table 56BD semantics, S1a loop-guard proof.

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
- Wave-4 landed (37 symbols, 689 total, 79.7% bounded = 44,089/55,296w):
  C7B1-reversal (FRAG_C7B1, single F073@C7E7->C878, noreturn stays disposition-open),
  FRAG_C7E9/2AFC/2B45/7A4B/95A2(4 entries)/AC07/AC22/2ECD/6753(no-exit tail)/49B6-lane(6)/388C/389C,
  ROUTINE_A815/A91C (CC-callers F94D/F944), ABD2/BF21/BF4D (F074/F274), 516A (F074@4D70, contains
  provisional DISPATCH_MASK15 point), 7B72 (F074@4771), 7CB6 (F830@7C8E), 772F/774E, 87C3(6 BC)/87C7/87D3
  (trimmed at retd@87E8)/8813, 5AAC (branch-tailed), 5DF4 (CC F920@5D7F), 29B1 (trimmed 29B1-29B8),
  FRAG_4C41/4CB4 (chained-frag, entries F84C@4C3D/4C43 — broad-scan rescue over zero-ref kill), FILL trim
  4BD7-4C28 (single-exit, parseable), FRAG_49B2 target corrected ->4AD8 (was ->49B6 misread, 4AD8 dark).
  Evidence: op_cc mask FF80 (F9 = cond call, ti-c54x op_cc.c), F980-F9FF = FCALL (plan p3-s118),
  cascade [4C29-4C40] decoded (F110 + F84C-skip + F073-exit per cell), 7CD8/F062 ghost, 5E4E negative.
  Pre-existing overlap noted (RUN_FF40 x SUB_FF61, untouched, for wave-5). make test 6 pass.
- Wave-5 landed (110 new + 30 bound upgrades, 799 total, 91.0% = 50,333/55,296w): 4 survey teams
  (W/C/E/H) + parent byte-validation of every exit/entry/interior. Convention: retd/bd bounds INCLUDE
  delay words (wave-1 precedent); chained inter-sibling lane edges are joins, not early-outs (4C41/4CB4);
  F072/F071 = rptb/rptz, F272 = rptbd, FBFF 1-word (objdump). Closed: 942E/9459 double-claim (COBBA trims to
  942E-9452, old RET@94EF model superseded by SUB_9459); C7F6-split rejected; B0E6 = F073 upheld; 9700/6657
  withholds honored; 2E2F dispatcher fan-in 53 callers counted. Data-kills honored (AED9/B948/BFB7/E855/E9D6-
  zeros/82D9/8329/8956/909F/95AA/9B6F-head/7EC5-head/9A50-weak/4B67-thin/4C29-cascade). Evidence-only, no
  draft: 9146-tail (BUTTERFLY), 9C99-lanes (MSG_STAGE_9F35). make test 6 pass.

## Goal mapping

Active goal "Static ROM6 completion" maps to tracker rows. Vector and
handler inventory maps to ROM6 upper plus blocks understanding. RF and
audio edges map to MCU driver plus §7a. Block↔ROM xrefs map to blocks
understanding. DROM shapes map to `drom.txt`. Homology ports map to the
ROM4 row.
