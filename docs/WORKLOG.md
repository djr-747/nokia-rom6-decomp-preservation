# Worklog + ROM image understanding / coverage

This log is a running record. Entries run newest first. Dates are UTC.

## 2026-11-07 — F2 supervisor loop + low-band ISR triple closed (1446w new)

- F2 `2088` supervisor loop (474w): full C body (port strobes,
  cmpm/cc lanes, bcd tails, calld-2D5E / calld-2C88 / 9E85 / E64C joins).
  Corrected portr model: PORTR is memory-only (A untouched); fixed two
  A-clobber stretches in the F2 C (no downstream effect, A reloaded).
- Low band `0x0000` + `0x22DA-0x27FF`: 8 nonzero clusters (1440w) owned
  as 8 spans (1446w with STM operands) + full C, entry-evidenced via
  vectors (FFC0->22DA SAMPLE, FFD2->25DF STATE, FFC4/C8/E0->27CD FRAME)
  and abuts (27FF->2800_stretch per its header). Contents: 0000 fill
  table (128w, uniform 0x7C2A); 22DA SAMPLE prologue (23w); 22F1/25F0/27E9
  STM-REA slots (2w each); 22F3 SAMPLE body (765w: pa33 handshake, kind
  dispatch, dual-MAC FIR BRC=7, SQDST metrics, epilogue FRETE, dead lane
  25D9-25DE, sub-entry 25DF); 25F2 STATE body (503w: mailbox copy, bound
  C851, DRR0/DXR0 echo per emu MMR 0x20/0x21 mapping, pa54 poll, coeff
  MAC chain, DXR0 write, FRETE 27CC, bc-296A exit, sub-entry 27CD);
  27EB FRAME head (21w: sample combine, bc-296A, abuts 2800).
- Correction: STM #lk,MMR is a 2-word instruction (oracle catalog row
  0x7700/0xFF00, 2 words; gas confirms `stm #5,rea` -> 771C 0005). The six
  `stm #0,rsa/rea` sites take operand 0x0000 as the immediate,
  not a dumped zero: spans extended (22da 22->23, singles 1->2, 22f3
  764->765, 25f2 502->503), headers/comments/symbols fixed. Nonzero words
  below 0x2800: 2158/2158 owned (2176 span words incl. 18 zero immediates);
  every nonzero word < 0x2800 is now owned.
- Gates: check_c 618 OK / 0 FAIL; recombine 1011/1011 MATCH (57,472w);
  link_audit 1011 spans, 0 overlaps, gap_runs 0 (outside=17, all pre-existing
  low-region + new low spans: informational, no region covers <0x2800);
  make test green (exit 0). symbols.yaml: +7 (LOW_FILL_0000 data_word;
  SAMPLE/STATE/FRAME slots+bodies program_word).

## 2026-11-07 — dark-gap Tier-3: gap_runs 0, gap_words 0 (was 15/1124)

- 15 remaining PROMLOW/PROMHIGH gap runs owned as spans (asm +
  C intent or pool/dead note, entry-evidenced via xrefs).
  Gates: check_c 604 OK / 0 FAIL; recombine 997/997 MATCH
  (55,296w); link_audit 997 spans, 0 overlaps, 0 gap runs;
  make test green (exit 0).
- C intents (13): 28D6 cmpm fork (frag_291C/291E forward joins);
  2B54 ISR context-save (isr_2B54; pshm balanced, frete comment);
  2C8A ring arith (dual sub/add per 2D8F/71A3); 2ED6 sample copy
  (frag_2F41 second entry, uploaded 9F5D/9F7E callers); 33E8 bit
  ladder (TC held to bc; mvmm/mar dance; routine_434F dark);
  3475 dispatch fan (entries 3475/3480/3491/3497 + frag_34B4
  subroutine; 3500 idle/checksum hangs; callee AR steps applied);
  355C store lanes; 4009/4057 port0 phases (port45_poll_40A1
  C-bound; TC/B dark-unbound flagged); 54BD msg stage (calld 2262
  delay-first; C-bound 54F8/5503 joins); 7EC6 delay-abut (first 4w
  run as 7EBE bd delays per D581, tail-joins 7F95); 8956 max-fold
  (RPTBD RSA=PC+4 flagged; max b per 66C5/68A2; bare-word mvdk
  per 64A0); 9613 counter lane (xorm per 4CB4; mvmd delay abut).
- Pool/dead notes (2): E855 frame-divide (frame/fbacc, no C form);
  7F1C 57w all-dead (post-bd, no entries); dead tails noted in
  7EC6 (7ECA+), 8956 (8990+), 9613 (9629+), all xref NONE.
- Fixes: 8643 trimmed to 11w call lane (prior +7w overlapped owned
  864E/8653); 294D/35BB duplicates removed (boot/35bb owners kept);
  3538 aligned to verified 351D (+0% AR0 param, bitf #512); pa44-45
  as numeric ports (40A1 precedent); DP-relative as bare direct
  (8F1C precedent); 4057 join label to l4095 (and, not end).

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
- Wave-6 landed (29 new + 3 upgrades, 828 total, 92.6% = 51,208/55,296w): tails, micros, withholds.
  OVERTURNS with falsified premises: FRAG_9700 (9700-9707, kill premise "inside ROUTINE_9682" falsified —
  parsed [9682-96B5]/[96BD-96FF] end before 9700) and FRAG_6657 (6657-6665 no-exit abut, kill premise
  "overlaps-6666" falsified — [6666-6678] abuts). Parent-claimed notes upgraded with verified bounds:
  STATE_WORKER C851-C85C, BUTTERFLY_9146 tail 9146-918A, CHAIN_HEAD_9C99 9C99-9CCE. Post-RET chains:
  A9E9-AA2E + AA2F/AA41/AA56/AA69 (gap fully covered), C576, BCBA, A5D2 (thin-entry flagged). Mid-entries:
  9B72, AF40 split-head (orphan AF3E-3F dark), 7C2C/7C2F, C806, B61F, CF01, DA32, 4AD8 (5 entries).
  Micros promoted: 65A5/6928/6987/9AF4 (+delays)/9BF5/68B7/690E/6940. 7ED4-7F54 stays dark (no head entry).
  make test 6 pass.
- Wave-7 landed (11 new + 4 corroborations, 839 total, 93.5% = 51,706/55,296w): block-xref exterior entries.
  Method: 3310-setB ROM-xref targets filtered to dark zones, sites verified in block binaries (opcode+operand
  alignment), catalog decode for F880 (= FB far branch, op_fb_pmad mask FF80), ROM-side exit/interior scans.
  ROUTINE_2B53 (FB-vector F880@66 block23 IVT image — hardware ISR entry, closes COBBA_CMD_ISR_ENTRY vector);
  FRAG_2A5F (block01 BC, closes DARK_2AFC tail — head 29B9-2A5E stays dark, note updated); ROUTINE_2C75
  (block30 call); FRAG_3691/36B0 (block01 branches, dispatch trampolines; 3683-368E dark, no entry);
  ROUTINE_3FFA (9 block calls, extended to [3FFA-4006] on clean tail); FRAG_43CD (block08 4xB head sled);
  FRAG_9AFC (block01 B, 96w); FRAG_A8B9 (block01 B micro); ROUTINE_ACF4 (block19 call); FRAG_B948 (192w,
  block00 loader branch-table slot — table, not executed branch, flagged; slots corroborate ROM6 table
  C556/C576/C660/C67F/C6B2/C736/BCBA/BCAC/B605/B634/9D16). Corroborations: DISPATCH_MATCH_LOOP
  (2E64 block01+30 refs, no bound — loop), INIT_FILTER_C717 (C736 slot interior), GAP_B634 (B634 slot;
  [B634-B6E5] already parses). 2E64 note YAML fixed (plain->folded scalar). make test 6 pass.
- Wave-8 landed (13 new + 2 upgrades, 852 total, 94.1% = 52,022/55,296w): assessment pass over remainders.
  FRAG_970B (85w no-exit, bcd+branch entries; F4EB-not-TRETE falsifies trete claim); FRAG_9ABF (chained into
  9AD2); FRAG_DA35 (retd, chained); FRAG_38F6/38FB (micro chain, CC/BC entries); FRAG_397B; FRAG_691D
  (chained); FRAG_A8B1/36A1 (no-exit micros); ROUTINE_2C88 (4 calls); FRAG_361C (post-RET thin, 3616
  precedent); FRAG_9CCF (no-exit; east F073@9CDB claim FALSIFIED — w=1092); FRAG_DAC9 (retd micro, chained).
  DISPATCH_MATCH_LOOP upgraded with Bound 2E64-2E83 (no-exit loop head, falls into 2E84). YAML hazard found
  and fixed: plain-style `note:` truncates at ` #` (PORT45_POLL bound was file-visible but parser-dead);
  audit of all 44 plain notes found this the sole casualty (folded `-` notes immune); fixed to folded style.
  Stays dark, ruled: 8329 (rptb non-entry), E795 (entry-less), 361C-remainder, 9708-orphan, DA40-47, 38FB-
  remainder, 3905-06, 4007-zone (checked), sub-word orphans, all zero-entry/data/weak zones per standing
  kills. make test 6 pass.
- Wave-9 landed (3 new, 855 total, 94.3% = 52,139/55,296w): 8210 block sets as ROM discriminator + oracle.
  Method: raw-scanned both sets for ROM targets, scored against validated ROM6 heads — setB 52.3% hit vs
  setA 2.6%: setB = ROM6 blocks, setA = ROM5 blocks (independent discriminator, recorded for census).
  SetB dark-zone targets: ROUTINE_3D3D (2x calld, split-head stub 3D3B-3C dark), ROUTINE_92BB + ROUTINE_92D7
  (calld pair, abutting chain). Rejected with reasons: 2FFF (F071 rptz repeat-count phantom, not a branch —
  repeat-form aliasing class); E795/E8BD (F980 FCALL-only refs, fcall-tension convention holds — entry-weak,
  island kill stands). make test 6 pass.
- Wave-10 landed (13 new, 868 total, 94.7% = 52,341/55,296w): systematic cell scan of all dark gaps
  (post-RET head + single-exit cells). FRAG_3A8E/3AB6 (40w chain, 3A81-linked); FRAG_4557/456A/4578 (cell
  chain, interior call overturns data-kill for 4557-cell only); FRAG_2D8B (ISR-chained micro);
  FRAG_BA08/BA2A (retd chain, delay-spill shared words — 8AA5 precedent); ROUTINE_4007/4055 (150w zone
  closed, 4+1 calls); ROUTINE_DBD4 (calld micro); FRAG_4B67 (thin + texture flag — data-kill overturned on
  bar-consistency, falsifiable); FRAG_A3CE (7w minimal, stub closed). Rule teeth demonstrated: BFD2/DAD0/
  BFB7/E795/8329/45FA stay dark (dark-src entry or entry-less + signature-less). make test 6 pass.
- Wave-11 landed (86 new + 17 spill fixes + 2 upgrades, 954 total, 96.8% = 53,537/55,296w): vestibule-chain
  harvest + BCD/CCD-audit + delay-spill class fix. 8-arm 29B9 chain (bc@29A0 entry overturns entry-less
  verdict, FRAG_2983 interior census corrected); 11-arm 3802 chain (FRAG_37D8 entries); 4-arm 3753 chain +
  FRAG_37C0; 3-arm 36C2 + 5-arm 6693 chains; 95AA 6-arm vestibule (thin dark-src, 9667 census match);
  shared tails FRAG_7F54/9A70/66C5/694D/7ADE/82D9/4C29-lane; dispatcher thin-arms 35A0/333C; routines
  ROUTINE_9A50/BADB/D9E1/99E6/DAD2/DFFE (call/ccd-entered); 10 retd + 7 micro-cells (6867, DA40, 399E, 9B63,
  44AF, 4450, 863A, 3905, 3BFE+5B-upgrade, 4313, 7140, 7DB3, ACF3, 649D, 3266, 8F1C, 4238, 3D3B, 9708, 9B6F,
  9453); 17 spill fixes (14 RETD +2w incl 87D3-trim correction, BD@5007 +2w, orm@8369 +2w, LOOP_628C/
  DIV_STEP_4348/LEAF54 mid-cuts, SUB32_7FB3 opcode word, D9C7-8 delays). BCD-audit (all FAxx = bcd) overturns
  BFB7 kill + finds 8F1C/4238; CCD-audit (FBxx/F9xx cc) finds DAD2 + 3D3B (overturns wave-9 stub kill, 3D3D note
  updated). 37DF corrected to FRAG_37D8 interior. DAD0 reconciled as RETD delays. 3EBD carve-out stands
  (wave-3 FIR/data ambiguity, needs trace). Kills stand with reasons: dispatcher fields 2ED6/28CF/33E8/3273/
  7EC5-thunks/3538/E855/315F (post-BACC/B-or-entryless), kernel-boundary 909F (mid-rptb-block), LOOP_628C
  +1w mid-cut + FRAG_62B4 fall-through, table/data E795/AED9/3EBD, repeat-forms 8329/91EF/2FFF, sub-word/DATA
  slivers, post-exit
  orphans. make test 6 pass.
- Wave-12 opened (oracle mining + BACC-table hunt, both negative for ROM6 entries): all-firmware-set
  scanner (/tmp/oracle_all.py) finds 67 dark-gap targets hit from 5190/6190/3210/5110/8210-setA uploaded
  code (ROM3/4/5 call sites: 2F70 15x, 3175/317F/318E/3195/3198, 37B0 18x, 7F07/7F12/7F22/7F24/7F2D, 90A9,
  3906) — cross-ROM homology corroboration (shared layout hypothesis supported), ZERO new ROM6 entries
  (only ROM6-era sets 8210-setB/3310 count per discriminator; their only dark hits are FCALL-only E795/E8BD
  which confer no entry). BACC@2ED5 pointer trace: AR1 = A-0x4FBF with A<=87 gives ROM[0xB041+A] but 0xB041
  is claimed code (FRAG_B036) not a table; negative-A base 0xAFEA-0xB040 also code — table hunt refuted,
  2ED6 kill stands with mechanism documented. FBD (FAFx) sweep: all targets far-space, irrelevant. 909F
  kernel-boundary question deferred (KERNEL_9042 rptb block overrun needs kernel revalidation, not a
  drive-by edit). F remaining: trace or second-firmware oracle for dispatcher fields.
- Wave-12 overlap audit (real parser, not Bound-only): 98 pairs, nearly all self-pairs (one symbol, several
  patterns) or pre-existing cross-symbol touches. Sole wave-11 overlap was ROUTINE_4007/4055 vs PORT0_TXN
  prose-derived span — resolved by making PORT0_TXN non-bounding (functional parent, halves carry the
  bounds; quoting the old pattern text re-matched RET_AT, fixed by rewording). No new overlaps from
  wave-11/12. Lesson: Bound-only overlap checks under-report; audit with coverage.ranges_in.
- Wave-13 (+30w, 96.9% = 53,567/55,296w): KERNEL_9042 len 47->72 through rptb@9074 block-end 90B6 + rsbx
  (byte-verified; abuts KERNEL_9071; pre-existing 9004-overlap unchanged, no new overlap); FRAG_45FA
  [45FA-45FE] (post-RET + RET, 2 out-calls). 8907 kill confirmed (B-operand orphan). make test 6 pass.
- Wave-14 verification (no new words): independent re-derivation of the six reada-dispatchers
  (8335/A249/AF57/AFAB/B11E/B16C) from the ti-c54x reference core — READA writes Smem (Smem<-PROG[A],
  program address from accumulator A), MMR 0x0B is BL, so B<-PROG[base+index] then BACC B is a ROM
  table jump. All six tables, 41 case bodies, six dispatcher prologues, and 27 shared callees rebounded
  and audited with coverage.ranges_in across all spaces: every span already claimed (JTAB/DISPATCH/SUB
  symbols), zero extensions, zero new overlaps. Lesson: audit all symbols.yaml spaces (data_word holds
  the wave-3..13 claims); program_word alone under-reports. Static surface unchanged at 96.9%.
- Wave-15 (+80w, 97.0% = 53,647/55,296w): exhaustive claimed-to-gap edge scan (41 gap targets, 40
  gap-internal, sole exterior edge F980 fcall E770->E86D from EXT_DISPATCH_BIG) yields SUB_E86D
  E86D-E8BC (far min/max clamp routine, fbacc b exit, interior join E898->E8AC); E8BD-E8C6 post-exit
  orphan stays dark. make test 6 pass, no new overlaps.
- Wave-16 (+14w, 97.0% = 53,661/55,296w): gap-boundary fall-through audit over all 33 gaps — every gap
  follows an exit except nine candidates; delay-slot analysis kills five (8BD3/95BF/95F3/9613/AEA8 sit
  behind retd/bd exits, not fall-through; D9C9 behind RETD@D9C6 delays; AED9 ambiguous data/code,
  AE70 1w post-table ret). Two annexations land: LEAF43_82D4 len 43->54 (fall-through tail 8329-8333,
  banzd-loop interior, abuts ret@8334) and WINDOW_918C len 50->53 (rptb@91EE operand + body 91EF-91F1
  per block-end precedent). WINDOW/BUTTERFLY_9146 overlap pre-exists (91BD-91D0 inside old bound);
  added words clean. make test 6 pass.
- Wave-17 (+555w, 98.0% = 54,216/55,296w): first emulator-trace oracle. 8210 v5.31
  headless boot to REGISTERED (250M steps, co-sim, ~205M DSP insns) with app-edge
  64K PC histogram (`DSP54_PCHISTFILE`; first-install-wins guard + core getter;
  emu diff saved in evidence dir). 262 executed gap words in 12 gaps -> 15 trace-entry
  claims (28CF/2917 COBBA-poll head+body; 2F51 RAM-table target block; 3273 split at
  interior b32B2; 3306; 3779 split; 7EEC lane run; 3179; 3557 frag; 3115; AE70 stub;
  AE71 prologue; AEA8 leaf refuting post-retd kill) + 345B-345F annex into
  DISPATCH_CMP_3460 (trace refutes "345F is data": ADD head via mid-instruction
  computed entry; also fixes its inverted 3460-34FF bound). Duplicate SUB_35A0
  withdrawn (FRAG_35A0 pre-exists, trace-corroborated instead). make test 6 pass,
  no new overlaps.
- Wave-18 (+100w, 98.2% = 54,316/55,296w): 3310 mixed-chain attempt (MT leg fails
  at 0 transitions — the ROM6 wall holds on both phones, but SMS-adapter/3310-MCU
  stimulus executes 4,677 new DSP PCs). Three chain-trace claims: SUB_2FD3A/B
  (2FD3-3021 continuation past 2FD1 dispatch tail, hot 2FFF lane x4) + FRAG_8907
  (full 21w bitf/brc repeat-minmax gap). make test 6 pass, no new overlaps.

- Wave-19 (recompilation seed): DSP-arch source tree (`src/rom6/<boot|kernel|
  modem|audio|rf|msg|tables>/`, `src/common/include/`, `src/rom6/link/rom6.cmd`
  MEMORY/PAGE per docs/01-memory-map.md). Assembler `tic54x-as` built from
  binutils 2.42 (`tools/build_tic54x_as.sh`, installed to ~/.local/bin).
  `tools/recombine.py` + `make recombine`: 6 kernel modules MATCH, 69 words
  (absolute calls, bc, calld, xc, retd+spill all encode exact). C intent layer:
  2 files with ORIGIN/EXPECT, `tools/check_c.py` binds them to ROM bytes.
  `make test` green (table_walk 6, verdict 6, recombine floor 69, c_spec).
  Gap: TI cl500 absent, no FSF/LLVM C54x backend; .asm stays the verified
  encoding until cl500 closes codegen. Doc: `docs/09-recompilation.md`.
- Wave-19b (+573w, 642w recombining): bulk import of 34 anchor
  (`program_word`) spans via listing miner (`/tmp/gen_spans.py`, kept out
  of tree). 40/40 MATCH after two gas rules (`.mmregs`, numeric ports).
  Floor raised 69 to 642. `make test` green.
- Wave-19c (+46,720w, 47,362w recombining = 85.6% of window): `data_word`
  bulk import with keep-or-delete verify + per-line `.word` fallback
  engine. 962/962 MATCH. Gas rule set closed: `-mfar-mode` global,
  MMR(n) raw (`|0x80` when <16), DP-direct rewrite, long RPT/LD forcing,
  XC forcing, leading-bare `.word`, `rsbx` verified. 949 pure mnemonic,
  1 forced module, 12 data tables. ~184 exotic spans dropped for hand
  review (`*+ARx` forms, far-call targets). `make test` green.
- Wave-19d (+7,255 module-words, 54,617w = 96.6% unique): oversize cap to
  4096 (C9E3, SPANHEAD, 2 data tables), listing-tail completion (drom to
  FC77 + zero-fill rule for objdump-elided runs; vectors tail), XC/`rcd`
  condition forcing, `-w` (byte-compare is the gate), whole-span `.word`
  last resort. 968/968 MATCH: 952 pure mnemonic, 1 line-forced, 3
  whole-word, 12 data-majority. Below-floor DARAM claims (~613w) and
  unclaimed dark gaps (~980w) are not statically recombinable. Floor
  54617. `make test` green.
- Wave-19e (C intent 2 to 5 files, 39 words): `daram_save_restore`,
  `div_step` (extern helper + subc_step pattern for opaque callees),
  `6f79_fill` (memset shape). Vacuous-match guard in recombine
  (0-word modules FAIL); hollow `e59d` refilled (29w). Floor 54646,
  unique 53,466w = 96.7%. `make test` green.
- Wave-19f (C intent 5 to 9 files, 54 words): constant fill/zero/copy
  leaves (`3616`, `4313`, `a8b9`, `aea8`). Straight-line stm/rpt/stl
  shapes transliterate directly; calls stay extern. `make test` green.
- Wave-19g (C intent 9 to 12 files, 92 words): cross-subsystem pattern
  proof. `a255` is a const pointer table (all 5 entries are fragment
  symbols), `9b5c` a null-check gate with chained continuation,
  `9414` a COBBA-status bit-test dispatch with extern callees
  (`99A4` header builder, `96BD` RSSI poster). `make test` green.
- Wave-19h (C intent 12 to 14 files, 139 words): `a109` audio path
  select (bit-test cascade, 32-bit dld/dst swap either direction,
  in-span A120/A126 arms mapped), `bfaa` modem normalize gate
  (fract-mode setup, delayed-branch chaining to `BFB7`).
  `make test` green.
- Wave-19i (C intent 14 to 16 files, 156 words): boot coverage.
  `2e2f` dispatcher head (flag-gated mvdk), `28cf` COBBA bring-up
  head (hottest boot entry, 10,681 trace hits, chains to `2917`).
  All six subsystems now have C presence. `make test` green.
- Wave-19j (C intent 16 to 19 files, 210 words): tables as const
  arrays (`ae6c` 4-way jump table with AD0D-driver consumer,
  `af64` 6-way handler table, `aead` 44-word coefficient table).
  Pattern: code tables become `static const` data, not functions.
  All seven source dirs now carry C. `make test` green.
- Wave-19k (C intent 19 to 20 files, 240 words): `698b` scaled
  divide (50-gate to `69A6`, DIV_CORE with fixed 9484/12049 cells,
  negate + conditional 0x250C offset, spill to 0x563).
  Delay-slot setup modeled as pre-call state. `make test` green.
- Wave-19l (C intent 20 to 21 files, 307 words): `96bd` RSSI poster
  (67w: status-gated port reads, INTM-locked COBBA program path,
  delay slots modeled as pre-branch state, rete context noted).
  `make test` green.
- Wave-19m (C intent 21 to 22 files, 448 words): `7ae5` COBBA port
  programmer (141w: conditional init, ports 5/7/8 program, 7B0A
  setup vs 7B1B compare/copy lanes, PORT0 transaction, range-picked
  burst base 4816/4944, INTM-locked burst). In-span arms mapped
  from the listing address map. `make test` green.
- Wave-19n (C intent 22 to 23 files, 514 words): `99a4` message
  builder (66w: length-delta header, flag select, AR0/saved-B
  stores, rptb XOR checksum, odd tail, end-pointer writeback
  to 0x21FC). Address-mapped L_99C4/99D8/99E2 arms. `make test`
  green.
- Wave-19o (C intent 23 to 24 files, 523 words): `a4d5` setup gate
  (helper, zero-test cell 9771, conditional call 0x4944). Rule set:
  40-bit accumulator fold chains (e.g. `85ad` XOR chain) stay
  asm-only -- 16/32-bit C cannot express SFTL/SUBC wrap exactly,
  extern-per-op is noise; they wait for `cl500` intrinsics.
  `make test` green.
- Wave-19p (C intent 24 to 26 files, 600 words): `a2b9` computed-call
  table walker (cala with 255 terminator -- the identity dispatch
  mechanism) and `a269` identity dispatcher (extern worker stages,
  A281/A28F/A291/A2A9 arms, AR5 presets). `make test` green.
- Wave-19s (C intent 29 to 31 files, 750 words): `84af`
  clock-gated idle/wake (CLKMD is data cell 0x58, spin loops,
  IDLE 3) and `84cf` measurement init (flag-gated andm, calld
  delay slots as pre-call state, fixed-point mpy/sfta scale).
  `make test` green.
- Wave-19t (C intent 31 to 34 files, 802 words): fanout trio.
  `853b` driver (BANZ grounded in ti-c54x core: tests the AR
  register with post-decrement, `while (ar0-- != 0)` exact),
  `8555` orchestrator, `8577` 32-bit OR-combine (AR3 lane stores
  swapped). check_c caught two EXPECT transcription slips in the
  new files -- the gate works as designed. `make test` green.
- Wave-19u (C intent 34 to 36 files, 816 words): `85f6` bitwise
  combine leaf (cmpl/or/xor, exact 16-bit) and `8501` fanout
  launcher (high-buffer setup, 853B call). Skip rule extended:
  ROR/ROL rotate chains (e.g. `85fd`) stay asm-only like folds.
  `make test` green.
- Wave-19v (C intent 36 to 38 files, 853 words): `56de`
  accumulate-and-post port transaction (INTM lock, conditional
  port-16 sample, timed port-14 write; ports as extern ops) and
  `8507` second fanout launcher (leading ret belongs to `8501`
  fall-through). `make test` green.
- Wave-19r (toolchain hunt): TI CGT needs myTI registration, no
  anonymous URL (TI site + archive.org checked). Handoff recorded in
  `docs/09-recompilation.md`: user installs C5000 CGT (`cl500`),
  session then compiles each `.c` and diffs EXPECT. C5500 (`cl55`)
  explicitly excluded (wrong ISA).
- Wave-19q (C intent 26 to 29 files, 668 words): SIMLOCK feeders.
  `8588` rolling crypto-block schedule (register stream, side
  spill, three folds), `85e4` 12-cell build plus 6 sub-rounds,
  `8611` 32-bit XOR combine (unsigned-long model, bit-exact low
  32 bits). `make test` green.
- Wave-19w (C intent 38 to 42 files, 899 words): RC-family gate
  leaves. `a3be` flag-gated calld (delay slots always execute),
  `a3d5` OR-combine with zero-reload plus retd-slot mask,
  `a3e1` single-instruction rc skip (tail always runs),
  `b110` rcd-delayed return plus rc bneq second gate.
  RC settled as conditional-skip per symbols.yaml B115/B118
  (objdump-verified conditional returns); emulator-core RC
  handler location still open. `make test` green.
- Wave-19x (C intent 42 to 54 files, 926 words): micro-leaf
  sweep. Four 1w RET pads (`3266` `4adf` `7f54` `ae70`), TC
  set/clear presets (`3bfe` `5823` set, `7140` clear, hardware
  state as comment-only), cell presets (`6928` `87c3`),
  `3905` reserved-word tail, `4450` mvdp overlay-patch point,
  `2d8b` ISR-tail call wrapper (B = 17 to `4590`).
  `make test` green.
- Wave-19y (C intent 54 to 67 files, 989 words): wrapper-family
  sweep. Ten `calld A2B9` primitive wrappers (`a25a` `a25f`
  `a264` `af74` `af79` `af7e` `af83` `b04b` `b0bd` `b141`,
  AR5 presets -8676 to -8869, same family as `a269` call
  sites), `45fa` dispatcher-entry wrapper, `38f6` status-OR
  plus B-to-A move, `9b6f` post-increment load (retd delay
  slots fall through out of span, documented). `make test`
  green.
- Wave-19z (C intent 67 to 80 files, 1076 words): mixed-leaf
  sweep. Two more `calld A2B9` wrappers (`b146` `b157`),
  `9dd7` rc-beq double call, `a3ce` ccd-delayed call on the
  `a3d5` measure (delay slot always runs), `56b7` producer
  converge step into `56de`, `454f` computed-call dispatch
  loop (banz as `while (ar6-- != 0)` per ti-c54x op_banz),
  `4578` helper-call store, `45a0`/`45a9` dispatcher plus
  flag set/clear call pair, `43cd` dispatcher call wrapper,
  `b5ff` cell preset call, `399e` INTM-unlock mask clear.
  `make test` green.
- Wave-19aa (C intent 80 to 92 files, 1192 words). Twelve
  more: `8529` copy-plus-fanout launcher (callee register
  mapping flagged unverified), `a3c5` ccd-delayed call on
  the `a3d5` measure, `af88` rc-gated primitive, `af6a`
  producer step, `a89b`/`a8a5` compare-and-fanout pair
  (CMPM TC-on-equal grounded in ti-c54x op_cmpm; tail-call
  model), `643e` measure gate plus save, `44b2`
  dispatcher plus byte extract, `446d` helper-call clear,
  `7c9e` mod-4 counter, `82cb` twin delayed-call launcher,
  `db76` indexed store plus tick (retd slots out of span).
  One EXPECT overrun into the next module caught by
  check_c, fixed. `51d0`/`da18` deferred (out-of-span
  branch targets). `make test` green.
- Wave-19ab (C intent 92 to 107 files, 1369 words).
  Deferred pair resolved: `51d0` inlines its 51CC target
  bytes (B = 0 plus delayed return, byte-cited), `da18`
  tail-enters DA21 mid-span via forward extern (DA21 has
  no C binding yet, per convention). Thirteen more:
  `b14b` twin primitive, `3609` flag preset plus tail-call
  into `3616`, `44a6` accumulator-restore nibble store,
  `9d0b` scaled-index call, `a2ac` gated producer step,
  `a5c6` cell test call, `b0e8` far-call pair plus
  primitive, `80fc` helper pair with zero-fill trap edge
  (0x6F8 reads all-zero, modeled non-returning), `9c8f`
  XOR-fold, `a5d2` measure-delta flag, `a806` delta plus
  bit move, `ff69` triple-call driver, `4439` two-lane
  dispatch gate. `3a81` deferred (branch past span to
  unbound 3A8E). `make test` green.
- Wave-19ac (C intent 107 to 119 files, 1557 words).
  Twelve more: `2e52` bit-test chain (BITF any-bit TC
  grounded in ti-c54x op_bitf), `712d` flag gate with
  tail-call into `7140`, `b12f` worker chain with dead
  gate (cc beq never fires, B = 1 per A4DE tail bytes),
  `b15c` worker chain with live gate (cc aneq always
  fires, same citation), `456a` two-lane gate with
  reversed move, `6973` modulo-by-subtraction self-loop,
  `6871`/`687f` range-flag pair, `44d7` shifted-OR store,
  `4590` shifted-store pair, `9f0a` sign-bit OR, `a5e1`
  measure setup. `3a81` still deferred (needs `3a8e`
  loop-capable modeling: portr/rptb/xc). `make test`
  green.
- Wave-19ad (C intent 119 to 121 files, 1610 words).
  Deferred `3a81`/`3a8e` pair closed. `3a8e` port-driven
  gain-ramp plus table tap modeled as C loop (BRC = 14,
  rptb block mapped word-exact from ROM; xc as if;
  PORTR Smem-only per ti-c54x op_portr so B is live-in;
  STH high word src(31:16) per ti-c54x op_sth).
  `3a81` measure router tail-enters it with B = 0.
  `make test` green.
- Wave-19ae (C intent 121 to 131 files, 1789 words).
  Small-leaf pool exhausted. Ten more: `838c`/`83a0`/
  `83ff` triple-calld launcher family, `afbf`/`b050`
  worker chains with dead/live A4DE-tail gates (same
  B = 1 citation as `b12f`/`b15c`), `b346` straight
  worker chain into audio workers, `aa2f` bit-test call
  chain, `71d8` scaled product (MPYA Smem = Smem x
  A-high overwriting B per ti-c54x op_mpya_smem),
  `7ea7` XOR-fold bit merge (XOR_ACC_SHIFT = dst ^
  shifted-src per ti-c54x op_logical; retd slots out of
  span), `b39e` preset call sandwich. One EXPECT
  transcription slip (dropped calld pair) caught by
  check_c, fixed. `make test` green.
- Wave-19af (C intent 131 to 150 files, 2006 words).
  Widened sweep: rpt/rptz/xc loop-capable routines.
  MMR-alias correction: DATA 0x8/0xB alias AL/BL, so
  `portr 56,*(0x8)` writes A-low (the 3ADE poll loop
  only terminates under this reading; fixed `3a8e` to
  take B from the port, A-low from the port). New:
  `3ade` PA56 poll, `2c75` port-2 handshake, `3ffa`
  port snapshot plus DST LONG32 store, `6867` port-bit
  gate, `44af` port write, `3cc9` port write plus
  delay, `dbd4` MAC dot-product (MPYA dst overwrites),
  `57fe` block copy plus call, `e380`/`c7a4` fill and
  table-copy pair, `4444` program-table broadcast
  (MVPD absolute = same word x3, flagged), `397b`
  split store plus conditional move, `ff61` audio
  copy plus ABDST distance-sum (B += |A-high| per
  ti-c54x op_distance_dual), `45b2`/`45ba`/`3115`/
  `33ce`/`da40` xc-gated presets with fall-through
  tail-calls into abutting spans. DST = 32-bit store
  per ti-c54x op_dst. `make test` green.
- Wave-19ag (C intent 150 to 164 files, 2264 words).
  Fourteen more: `83e8` fourth launcher, `3be4`
  compare/bit-test chain with shared FRAG_3BFE tail,
  `33bc` two-bit flag pack (nested xc gates), `a8bf`
  cell test with shared A8CD tail (TC/B live-in
  params, CMPM TC-only grounded in ti-c54x op_cmpm),
  `b036` far-call chain with byte-identical B046 tail
  branch, `aa56`/`aa69` bit-test chains plus far
  store (calld delay slot executes first), `a99a`
  table copy plus conditional clear, `4b9a`
  field-merge loop (SXM-on-entry flagged unknown),
  `7bf8` clamp plus zero-fill (MAX/MIN per
  ti-c54x op_compare), `8813`/`9ddd` table fills,
  `457f` shifted test plus copy-call, `cfae`
  triple fill plus ST1 restore. `make test` green.
- Wave-19ah (C intent 164 to 177 files, 2559 words).
  Thirteen more: `b41c` preset sandwich, `44e7`
  dispatcher plus shifted-OR store, `4557` program
  broadcast with dead loads noted, `855f` XOR-fold
  fanout into the C `block_copy_8588`, `86cf`
  zero-fill plus AR0-stepped store (`*ar2+0` by AR0
  convention, flagged), `d8f6` ST1/BK mode-switch
  call pair, `e7ef` zero-block plus call pair,
  `a7eb` audio worker B (A803 stub inlined from ROM
  bytes; no standalone .asm so no C file for it),
  `2e39` flag setup plus tail chain (2E4A/2E52),
  `580b` sieve with FRAG_5821/5823 tails plus new
  `5821` TC-clear stub, `a639` preset swap with
  in-span A64B skip, `3662` flag-cell copy with
  in-span 3671 gate. One EXPECT slip (3B88/3B89)
  caught by check_c, fixed. `make test` green.
- Wave-19ai (C intent 176 to 185 files, 2753w).
  Tooling: check_c now fails on missing stated .asm
  spans and on EXPECT-range overlaps of 2+ words
  (single shared boundary ret allowed, per the
  8501/8507 pattern). The audit caught a misplaced
  file (`a7eb` written to `rf/`, moved to `audio/`)
  and a double-bind (`5821` was `580b`'s own tail;
  file dropped, `580b` fixed to join its own tail).
  Nine more: `af40` flag copy with in-span gate,
  `56a2` producer gate (sftl logical-shift grounded
  by barrel semantics; bc into xc block modeled),
  `44bd` overlay patch plus readback (prom_write
  extern added), `4ebc` shift-chain math loop
  (40-bit long long flagged, ASM/AR0 live-ins),
  `573b` delayed-branch cell test (bcd slots always
  run), `68b7` range flag, `6961` modulo plus
  accumulate (MPYA dst, B out-param), `7d60`
  chained conditional stores, `5755` masked
  compare with out-of-span gates. SUB dst = src
  minus operand grounded in ti-c54x op_sub. Six
  EXPECT transcription slips on `5755` caught one
  by one by check_c (transcribe from ROM slices,
  not mnemonics), fixed. `make test` green.
- Wave-19aj (C intent 185 to 197 files, 3068w).
  Twelve more: `9f19` push-preserved block copy
  (rptb block with parallel st||ld sequentialized;
  BRC live-in, ASM dead, popm hardware state),
  `a4ba` cell test plus flag merge (A4CB fragment
  away via forward extern), `a87f` worker plus
  triple fanout (forward extern to FRAG_A8B1, which
  has no exit and falls into A8B9, so its C waits),
  `aff9`/`b062` gated lanes with byte-identical
  shared B012/B07B tails, `b0a1` far-call chain
  into audio workers `a7b7`/`a7eb`, `83b4`/`83ce`
  preset call sandwiches with in-span skips (popped
  AL = saved AR7 modeled live-in), `9233` block
  preset plus fills (BK circular size noted),
  `9268` constant spread plus triple call (BRC
  presets feed callees, values cited not bound),
  `acf4` three-way store select (STH high word
  per ti-c54x op_sth), `a8fe` long call chain with
  early return. One EXPECT slip (phantom mvdk from
  a misattributed grep line) caught by check_c,
  fixed from the verified .asm. `make test` green.
- Wave-19ak (C intent 197 to 205 files, 3168w).
  Eight more: `a8b1` twin test with fall-through
  into A8B9 (second rc skips the stm, AR2 stays
  live-in; 9-fill inlined, cites `frag_a8b9_zero`),
  `40a1` port 45 poll plus port 44 strobe (AH/AL
  aliases, two self-loops, bit-12 tests), `36f0`/
  `36e1`/`375e` dispatcher-clause arms (AL compare,
  forward externs to unbound `36fb`/`3775`/`2c88`/
  `2e64`; far call modeled extern per b036),
  `3802` vestibule arm, `4a12`/`4a46` B-lane chain
  link plus tail (AR2-relative clear, tail into C
  `frag_4ADF`). Deferred pool reconfirmed asm-only:
  `85fd`/`8627`/`4f5f`/`8775` (rotates), `436c`
  (ror plus addc carry), `99ff`/`43d3`/`8433`/
  `3623`/`32ee`/`333c`/`3862` (bit-reversed `%`),
  `5b18` (RPTB plus BANZ nesting), `c5c3`/`c5ea`/
  `bcac` (MASR/MACR/parallel), `4883` (retd),
  `9e2f`/`3199` (held for size). Symbols cleanup
  flagged: 4A12/4A46 notes claim self-loop and
  back-edge targets but ROM bytes verify 4A4B/4ADF
  and the .asm files agree; ROM wins. `make test`
  green.
- Wave-19al (C intent 205 to 208 files, 3236w).
  Three more: `3775` dispatcher tail (call plus
  b into unbound `2e64`), `2e64` match-loop filter
  (dark callees `05a0`/`942e`/`2e8f` as forward
  externs, `942e` A live-out as int return; AR4
  in-out; `xor #0,b` no-op pad kept; `sftl -8`
  logical), `8413` index-halve gate (BRC write
  cited not bound; `rc blt` signed; away tails to
  dark `8436`/`843a` and asm-only `8433`). Held:
  `2c88` (span review: .asm covers only the call
  head, ROM runs on through `11F8 08E5`), `4a4b`
  (bd delay slots run past the .asm end), `36fb`
  (bitrev plus dynamic rpt), `9e2f`/`3199` (size).
  `make test` green.
- Wave-19am (C intent 208 to 213 files, 3336w).
  Five more: `6666` threshold gate with save plus
  retest (AGT/AGEQ per 6871; calls C
  `daram_save_restore`), `9708` delayed-return bit
  set (orm in retd delay slot), `8f1c` direct-store
  pair with fall-through, `89f4` scaled round-trip
  (MPY Smem,#lk per ti-c54x op_mpy_smem_lk; ADD
  #lk,16 per op_add_lk_16; bcd/retd delays always
  run; STH high word per op_sth; AR1 in-out),
  `5e7d` masked merge plus ring stage (ALT per
  6871; andm masks exact; mvdd AR2-fixed). `make
  test` green.
- Wave-19an (C intent 213 to 215 files, 3375w).
  Two more: `7fc6` neighbor-merge filter (rptb
  plus retd delays; AR2 threaded from both `83b4`/
  `83ce` callers, signatures updated), `9591`
  two-bit select with delayed away-branch (bd
  delay orm always runs). Held: `2e84` (bitrev),
  `9e85` (cc form plus size), `8b03`/`8ddb`/`9004`
  (rptbd/parallel/double-precision). `make test`
  green.
- Wave-19ao (C intent 215 to 225 files, 3494w).
  Ten more, all boot-chain strobes and gates:
  `2867` port 2 set-bit strobe, `29b1`/`29d3`/
  `2a02` preset gates (forward externs to unbound
  `29e1`/`2a73`), `2a0e`/`2a5f` port 4 strobes
  (idle loops exact counts), `2a57` clear gate
  (tail calls C `frag_2A5F`), `2b45` port 1 strobe
  plus flag, `95e2` shift store plus join,
  `96b6` delayed-return preset (retd delay always
  runs). `make test` green.
- Wave-19ap (C intent 225 to 237 files, 3627w).
  Twelve more: `3557`/`361c` flag tests,
  `36a1` three-way fanout, `36b0` cell pair plus
  report, `3753` arm 3 (36f0 shape with #10),
  `37c0` dual-port relay with unlock (BL-only
  observation, INTM hardware state), `381b`
  byte-class dispatch (range tests proven exact
  under both SXM states), `3827` masked store,
  `382e` small-value dispatch (ldu exact),
  `383f`/`3844`/`3849` cell presets (plus state
  step). Held: `3691` (cc needs the 580b TC-out
  contract). `make test` green.
- Wave-19aq (C intent 237 to 245 files, 3701w).
  Eight more: `2ec6` constant-B call chain (B
  threaded into C `routine_4590`), `388c` flag
  pair with B handoff (B live-out threaded),
  `38fb` shift-merge with live-out A (long, int
  return), `4238` delayed-return double move
  (retd delays always run, pointers in-out),
  `452c` shift-mode store (ASM hardware state),
  `49b2` B store plus join, `49f7` clear-or-join
  gate, `4a01` B-lane chain head (all tails
  wired: C `frag_4A12`, unbound `4a1e`/`4a4b`).
  Held: `2ecd` (bacc computed branch, no
  convention), `4ad8` (calad delayed computed
  call). `make test` green.
- Wave-19ar (C intent 245 to 251 files, 3763w).
  Six more: `4ae0` B-lane join (B threaded into
  C `routine_4590`), `4af3` port 56 idle-poll
  loop (INTM lock hardware state, `idle 1` extern
  op, self-edge loop), `4c29`/`4c2f`/`4c35`/`4c3b`
  compare-rung chain (SUB dst = src minus operand
  per op_sub; dark equal-tails). check_c caught a
  dropped rsbx/idle pair in the `4af3` EXPECT,
  fixed from ROM. `make test` green.
- Wave-19as (C intent 251 to 255 files, 3810w).
  Four more: `4df0`/`4df6` delayed-branch BK
  presets (bd delay always runs), `4ece`
  conditional one-store (xc pair, retd delay),
  `4ee0` counter-gated delayed branch (BANZ
  post-decrement per branch_sind; bd delay B
  dead). Held: `4dda`/`4de2`/`4dea` (mar-% is
  reverse-carry update, consumer dark, needs
  oracle), `4c41` (size plus rptbd), `4d9d`
  (rptbd plus exotic store), `4e63` (rptbd plus
  mpya). `make test` green.
- Wave-19at (C intent 255 to 262 files, 3877w).
  Seven more: `614f` flag-gated delayed store
  (retd 2nd slot spills past span, flagged),
  `4ff6` triple-flag chain (bd delay A dead),
  `63d8` double store (no yaml bound, header
  plus MATCH), `649d` B store plus join (shared
  operand word per 8AA5), `6596` range gate,
  `65a5` conditional cell add (xc 2nd slot
  spills, flagged), `6657` conditional rebias
  (MIN signed per op_compare, A/B out-params).
  Held: `54bb`/`629f`/`644a` (decomp boundary
  review). `make test` green.
- Wave-19au (C intent 262 to 271 files, 3947w).
  Nine more: `66a7` sum handoff, `690e` T-bit
  test (BITT via T = A - 17, in-range noted;
  calls C `frag_6928`), four message-converge
  fragments (`569a` live-out A return, `569e`,
  `5676`, `54f8` with live-A tail), three code-
  address tables (`4433`, `b129`, `b177`, static
  const arrays per aead precedent). Held: `a249`
  (READA program-read direction plus bacc-to-zero
  need oracle). `make test` green.
- Wave-19av (C intent 271 to 275 files, 3972w).
  Four more: `d5c8` tail store, `345b` compare-
  operand setup (A/B out-params), `538d` branch
  sled (four entries, one EXPECT, entry-function
  convention), `52f7` decrement-or-join gate.
  Deferred as a class: `afab`/`b16c`/`af57`
  (READA plus bacc-to-zero, with `a249`),
  `5355` (cc, with `3691`), `dbc1` (norm needs
  40-bit plus TC). `make test` green.
- Wave-19aw (C intent 275 to 277 files, 4011w).
  Two more: `3460` masked compare fanout (TC
  live-out noted as lane-consumer feed; SUB per
  op_sub), `53d9` far-call chain with fetch
  (extended fcalls extern per b036; A threaded
  into unbound `54a4`). Held: `5362` (bacc with
  computed A into uploaded-code region). `make
  test` green.
- Wave-19ax (C intent 277 to 282 files, 4085w).
  Five more, the 66xx cluster: `6693` entry gate
  (cmpm equality, AR1 preset, A/AR6 plus B/AR5
  passthroughs), `66ac` min gate, `66b8` absorb
  gate, `66c5` max join (fall-through abut as
  tail call), `66cb` save-conditional (xc pair,
  calld delay first, C `daram_save_restore`).
  MAX/MIN signed per op_compare. `make test`
  green.
- Wave-19ay (C intent 282 to 286 files, 4129w).
  Four more, the 69xx T-bit family: `691d`
  (retd delay orm), `6940` difference gate (rc
  bail plus tail to C `frag_6954`), `694d`
  fall-through bail, `6954` cell bump (rc ageq
  early return). BITT via T, in-range noted per
  690e. Held: `687e`/`688c` (post-ret heads,
  with 629f/644a). `make test` green.
- Wave-19az (C intent 286 to 289 files, 4214w).
  Three more, the message swap-store chain:
  `5683` masked merge (A threaded to C `569a`/
  `569e` and dark `569c`), `55d7`/`55b1`
  T-scaled swap stores (MPYA register-only dst
  per ti-c54x op_mpya_dst: A = T x A-high, T
  known in-span; `and #-2,16,a` high-word math
  exact). Held: `d5ca` (rptbd plus T-from-ST1).
  `make test` green.
- Wave-19ba (C intent 289 to 290 files, 4266w).
  One more, 52w: `a7b7` audio path A. Absolute
  offset mapping proved all six branch targets
  in-span (A7E5 = st-7 word, A7E8 = call site,
  A7D8 = st-8 word, A7C9/A7D2/A7DD interior
  joins); single function with gotos, bcd
  convergence modeled straight, no dark
  externs. `make test` green.
- Wave-19bb (C intent 290 to 293 files, 4292w).
  Three more: `7a4b` cell-equality pair,
  `7ade` step-plus-gate (tails into C
  `port_programmer_7AE5` with AR1 in-out plus
  AR3/AR4/AR5 passthrough; A live-out int
  return), `7c2c` constant-A tail (A threaded
  into dark `7bee`). `make test` green.
- Wave-19bc (C intent 293 to 294 files, 4310w).
  One more: `3850` register zigzag (ldm values
  as int params, B lane-id threaded into unbound
  `93ce`, sftl logical). Held: `3787` (4-operand
  AND needs oracle grounding). `make test`
  green.
- Wave-19bd (C intent 294 to 298 files, 4406w).
  Four more, all boot: `2bed` port 56/2 relay
  segment (second segment of the split span),
  `3028` post-return setup (SP hardware state,
  far join to dark `2000`), `296a` port 1 strobe
  with flag joins, `29b9` conditional stage (xc
  pair, path-dependent store address noted,
  tail calls C `frag_29D3`). `make test` green.
- Wave-19be (C intent 298 to 301 files, 4508w).
  Three more: `29e1` masked select (bcd delays
  always run, plain sub form per .asm), `2a73`
  port 49/50/4 sequence (bd delay mvmd always
  runs), `2983` flag chain with arithmetic tails
  (entry AR2 as param, not scaffolding; tails
  call C `frag_2A73`/`frag_29B9`/`frag_29B1`).
  `make test` green.
- Wave-19bf (C intent 301 to 303 files, 4604w).
  Two boot leaves in house style
  (`<addr>_frag_<addr>.c`, ORIGIN/EXPECT header,
  volatile cells, port externs): `2875` strobe-then-clock
  gate (in-span rejoins at 0x2890/0x2899 via goto;
  dark tails `frag_283D`/`frag_28A5`, dark call
  `sub_05F6`) and `2ACC` masked RF-port program
  (BC targets 0x2AE2/0x2AE6 proven in-span nops from
  the recombined listing, not dark tails; full-flow
  goto over the TC skip; CMPL grounded as full-40-bit
  NOT per ti-c54x `op_cmpl.c:44-45`, C/TC preserved,
  low16 exact). `2983` caller updated to pass A into
  C `frag_2ACC(a)`. Misnamed `c_boot_*` drafts removed.
  `make test` green (exit 0).
- Wave-19bg (C intent 303 to 304 files, 4649w).
  `2D5E` message-block post plus status-latch epilogue
  (bitf-gated 0x2F00 block build around dark `sub_0626`
  and unbound `frag_93CE`; in-span rejoin at 0x2D7F via
  goto; C tail `frag_2D8B`; orm/andm bit3 stroke pair;
  entry AR2/AR3 threaded as params; existing `56a2`
  caller updated to pass `G_AR2/G_AR3`). `make test`
  green (exit 0).
- Wave-19bh (C intent 304 to 305 files, 4716w).
  `2BAA` RF gate plus mode-lane select head (67w;
  in-span joins at 0x2BCD/0x2BE4; provably-dead
  `(x<<4)-1==0` re-tests folded with proof; C tail
  `frag_2BAA_seg2`; dark subs `sub_39F0`/`sub_39A4`
  per kernel precedent; transposition slip in EXPECT
  caught by check_c, fixed from listing). `make test`
  green (exit 0).
- Wave-19bi (C intent 305 to 306 files, 4791w).
  `2DE4` HPI word-drain plus classify-post worker
  (all four BC targets proven in-span rejoins from the
  listing, including `ret` at 0x2E2E; dark calls
  `sub_0628`/`sub_2289`/`sub_B4F8`; `ldu` as unsigned
  load and `stlm` per `2e64` precedent; `sfta -8` exact
  on non-negative `ldu` value; 1024-header variant of
  the `2D5E` 0x2F00 block). `make test` green (exit 0).
- Wave-19bj (C intent 306 to 315 files, 10711w).
  All 9 remaining unbound tables bound as read-only
  C arrays via `/tmp/gen_tables.py` (pure `.word`
  verified by grep; EXPECT transcribed from the
  `.asm` words, not mnemonics): 56bd/33w, 8821/51w,
  ad0d/316w, afb5/10w, bcc8/52w, e9ee/432w,
  eb9e/1122w, f000/3072w, fc00/832w. `make test`
  green (exit 0).
- Wave-19bk (C intent 315 to 316 files, 10885w).
  `5503` RF-tune converge chain (174w, first-try
  EXPECT from the listing): rpt/mvdd loops,
  single `xc 2,tc` with plain delay slots (4EBC
  exact-skip precedent), mvdk idiom, SUB #lk SHFT-0
  per ti-c54x `op_sub_lk`, `cmpm *(0x8)` on the
  port-56 AL residue; tails into C `frag_55B1`
  (AR1) / `frag_5683`, dark `sub_56FC`/`sub_06E6`,
  unbound `frag_55EF` declared with B-live param
  (its entry SUB reads B). `make test` green (exit 0).
- Wave-19bl (C intent 316 to 317 files, 10941w).
  `A482` tune-select setup (56w): SUB #lk lanes
  (SHFT-0 per `op_sub_lk`, alt narrowing per 6871),
  INTM-free; pshm/popm BL round-trip net preserve;
  calld into void `sub_AB82` per A3E1 precedent
  (delay presets dead in C); int status return
  (0 early, 1 done). `make test` green (exit 0).
- Wave-19bm (C intent 317 to 325 files, 11112w).
  Six RF binds, all first-try EXPECT: `938C`
  COBBA audio preamble (rc early-out per 2E64,
  PORTR-to-plain-cell leaves A untouched per
  `op_portr` Smem-only); `4474` port 4/49/50
  strobe (pshd/andm/popd net preserve modeled
  exactly; bc-to-self busy-wait as while loop;
  AR4 param); `4453` guarded broadcast (mvpd via
  `prom_read_word` per 4444; family par3/par4
  signature); `5395` lane head plus `53BA/5420/546B/
  5489` lane chain (AR2 params; interior join
  `frag_546B` into `frag_5489`; A-threading into
  `frag_54A4`/`frag_53CD` per 53D9). `make test`
  green (exit 0).
- Wave-19bn (C intent 325 to 328 files, 11255w).
  `5301` copy sled, dual-entry `53EB` (53w: 53EB
  lane plus 0x5409 lane, one file per 538D
  convention) and `544A`: xc-gated slots with
  TC-liveness analysis per lane (53EB threads
  entry TC as param since its cmpm sits in the
  skipped slots; 544A void since its cmpm runs
  unconditionally; 5301 void, TC dead after);
  `538D` slot1 updated to thread TC while slot2
  stays a void forward extern (sled ROM bytes
  target 0x5434, a separate span from the 0x5409
  entry — listing-resolved, no conflation).
  `make test` green (exit 0).
- Wave-19bo (C intent 328 to 333 files, 11338w).
  `A679` dual-entry measurement setup (53w, one
  file per 53EB convention; retd delay slot
  always runs; SUB #lk single-acc form; mvdk
  dmad-destination); `4A4B` dual-subtract select
  (bd delay slot stored before the C tail call
  per 2A73; B threaded as param; 4A63 void extern
  proven airtight from its entry path); three
  entry-call stubs `3986`/`3EE1`/`54BB` defining
  `sub_3986`/`port13_stable_read`/`frag_54BB` for
  existing callers; `4007` stub withdrawn (446D
  already contracts it with A/B params — a void
  definer would conflict). `make test` green
  (exit 0).
- Wave-19bp (C intent 333 to 342 files, 11676w).
  `44FD` triple-entry fanout (A-restore honesty
  via saved local; calld dead presets; two
  functions one EXPECT per 53EB); `3D1B` port
  program (mvdk store-content fix: `*ar2++`, not
  the pointer); `66E2` rebias pair (beq-skips-st
  shape shared with 4474); `4A19` 4-param
  threading into `frag_4A4B`/`frag_4A46`;
  `6679`/`6753` save tails (calld delay-slot stm
  IS the `daram_cell_store` src arg);
  `692C`/`68F7` BITT gates (TC formula grounded
  in `op_bitt_smem`, plain-offset reads);
  `6693` caller updated to pass AR5 into C
  `frag_66E2`. `make test` green (exit 0).
- Wave-19br (C intent 352 to 358 files, 11780w).
  Six more, all first-try: `9700` bit-test fork
  (AR2 passthrough into unbound `frag_970B`);
  `9AF4`/`9B63` retd leaves with int A-out
  (delay slots always run; A482 precedent);
  `BA2A` cell-bump return; `DAC9` zero gate into
  C `frag_DACF`; `B942` delayed-call tail.
  `make test` green (exit 0).
- Wave-19bs (C intent 358 to 362 files, 11813w).
  `8675` store return; `89EB` register gate
  (ldm address-value test per 4444); `95B8`
  negate tail into C `frag_9667`; `AEA0` cursor
  rewind (plain mar offset, linear). Skipped as
  dangling/mid-span: `C851`, sth/stl pairs,
  rpt+sth fills, lone pshm/ld/add heads, `DB7F`
  (dangling xc), `3EBD` (table length open).
  `make test` green (exit 0).
- Wave-19bt (C intent 362 to 365 files, 11855w).
  `836D` AR7 dispatch (calld delay-slot presets
  callee-visible, second AR6 preset rides tail);
  `952E` init pair + port 1 kick (A = 256 dead at
  tail, void precedent for dark `283D` tail);
  `C7E9` masked compare (DROM lane, masks
  `0xC600`/`0xF9FF`, void tails). New check_c
  gate caught: `Verified encoding:` line required
  in every C header. `make test` green (exit 0).
- Wave-19bu (C intent 365 to 371 files, 12183w).
  `32B4` nibble steering into `ROUTINE_423B`
  (TC chain grounded: AND/OR preserve TC per
  `op_logical.c`, `xc` reads the earlier `bitf`;
  all three bc targets rejoin in-span). `3640`
  AR0 class select (`3664/3667` dark voids,
  `3652` a separate span inside the bound).
  `3938` scaled port kick (literal double-`sub`
  keeps a dead 20200 arm; AR2 bump rides out).
  `38C9` scaled add/or (stale-Z gate: entry Z as
  `z_live`, LDM/SFTA/BITF write no Z per oracle
  deltas with PRESERVE = 0; TC4 chain grounded
  through sub/sfta/stl/sftl/subs/ld/or/add;
  bound `FRAG_38F6` returns A). `3FC4` RF prologue
  (three dead `sub_4007` calls). `670D` quad
  MIN-select (AR0 pinned 12253 after pass 1;
  `alt` = A < 0, `min` signed 40-bit; `676A`
  void per 6666). `make test` green (exit 0).
- Wave-19bv (C intent 371 to 377 files, 12496w).
  `C7B1` init gate (56w DROM; `C7E9` arm as
  terminal call, spans abut with zero overlap;
  `C7F6` escape as dark void; BK/AR4 dead noted).
  `4B67` dual accumulate-store (Smem
  zero-extension for OR grounded in
  `op_or_smem.c`; audit flag: older `or/and`
  Smem files modelled signed -- review queue).
  `B605` cell-sum gate (arithmetic Smem
  sign-extends under SXM = 1 per
  `op_sub_smem.c`; `FRAG_B61F` takes live B).
  `500B` mode-word build (NEG preserves TC per
  `op_neg_acc.c`; dead `5052-5055` block noted;
  goto-free via build-select + shared tail;
  EXPECT slip caught by check_c -- transcribed
  from ROM slice verbatim after). `4BA8` A-gated
  fill chain (`9268` par3 = delay-slot AR3 =
  12162; ASM = -9 unmodeled; B rides 0 per
  callee-preservation convention, second bneq
  dead in model). `978F` port strobe + poll
  (entry-A gate; `9682` opaque void; 40-bit B
  entry-live; poll hang risk noted). `make test`
  green (exit 0).
- Wave-19bw (C intent 377 to 380 files, 12612w
  measured). `7FF4` copy-plus-select (RPTZ
  zeroes B per `op_rptz.c`, 7 zero stores;
  `802D`/`802F` B-live dark voids). `4986`
  cell-gated store pair (stale defer note was
  wrong -- no bcd in span; `49B2` in-span join;
  `4AD8` calad opaque void). `687F` range flag
  (6871 twin, cell `0x2FD9`/159, B-out int).
  `688D` polled negate (rc-tc chain: bitf TC
  survives xc/neg/add per oracle deltas; retd
  single delay slot; authored exact 20w .asm --
  sibling `688d_sub21` overclaims through
  post-retd `max`; recombine 969/969 MATCH).
  Tallies now measured from tree, not running
  sums. `make test` green (exit 0).
- Wave-19bx (codegen loop live; 383 C files).
  `cl500` C5400 CGT 4.2.0 installed to
  `~/ti/c5400_4.2.0` (`-v548` accepted; needs
  CGT `bin/` on `PATH` for sub-tools; `-o`
  unsupported, use bare `-c`; no TI disassembler
  ships -- `.text` via `ofd500
  --obj_display=rawdata`, reading via our
  `disasm_c54x.py`). New `tools/codegen_diff.py`
  (compile `-O2`, extract `.text`, diff vs
  EXPECT) writes `build/codegen.json`. First
  full sweep: 4 MATCH / 383 -- all four 1-word
  `ret` pads (`3266/4ADF/7F54/AE70`), `.asm`
  retired, `check_c` taught the codegen path
  (MATCH record in `codegen.json` replaces the
  `Verified encoding` line). 16 data-scope
  (tables + `A255` jump table, no `.text`).
  362 code mismatch: 361 diverge at word 0
  (compiler prologue `PSHM` vs frameless hand
  code), nearest `691D` (2 words match).
  Median codegen 1.67x hand size. Dialect fixes
  from compiler errors: 12 files `&G_AR5` to
  local `int **pp5` + writeback (C89: decls at
  block top); `44FD/53EB` implicit-decl
  conflicts fixed with prototypes. `4EBc`
  `long long` left failing (40-bit intent,
  narrowing would falsify; recorded as cl500
  gap). `make test` green (exit 0).
- Wave-19by (prologue lever verdict). `cl500
  -n` codegen read directly (`687F`: `STM
  #12249,AR2` = absolute-cell access,
  `PSHM AR1` frame, `SSBX SXM`, stack-passed
  args, A-return, inverted branches). ROM ABI
  is register-passed, B-returning, frameless.
  Verdict: stock `cl500` cannot reach
  byte-identity for most functions (no
  naked/no-frame flag; `-r` only reserves
  globals). `.asm` stays the byte-identical
  source of truth (969/969 MATCH); C stays
  intent plus tightening guide; codegen diff
  guides opcode/order convergence only.
- Wave-19bq (C intent 342 to 352 files, 11740w).
  `423B` T-scale accumulate (MPY #lk.dst per
  84CF); ten-file micro batch, all first-try:
  entry-call stubs `8641`/`864E`/`8653`/`3D3B`
  (define the 5420-lane callees), branch tails
  `7FB3`/`965C` (into C `frag_7F54`/`frag_9667`),
  step tail `9BF5` (plain mar), delayed-return
  stores `DA32`/`DACF` (ROM-slice EXPECT, no
  listing rows), guarded tail `9453` (calld dead
  preset, agt on live-in A). Fragments skipped:
  lone pshm/ld/sth/mvdk/add heads with no
  control unit or unknown table length. `make
  test` green (exit 0).

## Goal mapping

Active goal "Static ROM6 completion" maps to tracker rows. Vector and
handler inventory maps to ROM6 upper plus blocks understanding. RF and
audio edges map to MCU driver plus §7a. Block↔ROM xrefs map to blocks
understanding. DROM shapes map to `drom.txt`. Homology ports map to the
ROM4 row.

- Wave-19br (C intent 385 to 404 files; check_c
  404 OK 0 FAIL; recombine MATCH, make test exit
  0). Kernel remainder: `57A3` head (41w) abuts
  existing `57CC` tail; new `57cc.c` holds six
  entry functions sharing the rcd commit tail.
  `5AAC/5AC8/5AFB` filter kernel (.c over existing
  .asm): RPTB deinterleave scatter (stride 64 mod
  BK = 456, 57 slots), mod-627 fold, re-bias, BANZ
  test-then-dec (3-2-1 taken + fall = 4 passes).
  `5B18` nibble unpacker. `5B26/5B5C/5B9E/5BD9`
  region: computed baccd dispatch head, pshm/calld
  twin tails, mod-4 dispatch `5BC6`, table scatter
  `5BD9` (ASM-shift + DLD-step HYPOTHESIS). `5A68`
  banzd triple nest (4 x 6 x 19). `5BF1` 8-call
  hub + `5C34` neg-shift scatter. Deferred group
  `3267/3691/3674/3779/33D8`: trampolines with
  bitrev-advance noted unmodelable (AR live-out
  unknown), RPT Smem = RC (op_rpt_smem) + 1 iters,
  bare-extern tails per 361C. Msg: `A4DE` setup
  chain, `93CE` TC-result classifier (dead-A fossil
  noted: `ld/and` masked A never read after AR3 =
  8 reassign), `A2C3` port worker. KEY FINDING:
  `A2C3` bleq chain is dead under callee-preserved
  A, fully live under 3EE1-A-out: `port13_reading`
  HYPOTHESIS recorded; CONFLICTS with 2983.c which
  assumes 3EE1 preserves A. Trace (or a 3EE3-3FC3
  dark-body decomp) must decide; if A-out, 2983.c
  needs rework. T-as-negative-shift HYPOTHESIS
  (`5BD9/5C34/5A68`): effective barrel count for
  wrapped T trace-confirmable. `and #-1,a` = A &=
  0xFFFF (immediate zero-extended, op_logical).
- Wave-19bs (encoding-pool disposition). Spans
  that stay asm-only, reason recorded in each
  .asm header + recombine MATCH (byte truth kept):
  READA (`55EF`, `A249`, `AFAx/B16x` family);
  bit-reversed addressing (`9A11`, `3623/32EE/
  333C/3862/36FB/43D3/8433` family, `3779/3674`
  loads noted); far returns (`9A11` retd/reted);
  NORM/EXP single-steps (`71A3`, modem exp_norm);
  dual-destination arithmetic (`71A3`, `C2D5`
  sub-pair); SAT (`C2D5`); parallel MAC/MAS/MACD
  (`9F42`, modem mac/rptbd/dual); DLD/DST 32-bit
  (`9F42`, `5282/528F`); ROR/ROL rotate (`4F5F`,
  `80F3`); BACC computed (`95A2`, `5362`, `2ECD`);
  CALA/CALAD (`4AD8`); BRC-carry (`8775/87C7`);
  BCD (`4986`); 233w monster (`4CB4`, staged).
  Rule applied: a span gets C intent iff every op
  has an oracle-grounded C form; otherwise .asm
  stays the deliverable with the blocking op cited.
- Wave-19bt (link audit). New `tools/link_audit.py`
  checks all 965 recombine spans against
  `src/rom6/link/rom6.cmd` regions; writes
  `build/link_audit.json`. Result: 54662 span-words
  (53462 unique), 0 spans fully outside the map (3
  boundary-crossers: `AFF9` PROMLOW->PROMHIGH,
  `FF78` BRANCH->VECS, `FC00`-table PROMHIGH->
  BRANCH -- map-description notes, bytes verified),
  87 overlap pairs (26 substantive: dual analyses
  sub13/sub14/sub21/sub32/sub84/sub85 families +
  abut variants; rest 1-word shared exits), 1834
  gap words in 50 runs (dark gaps, expected).
  Verdict (wave-12): per-span origins individually consistent;
  overlap pairs zero (959 spans, 53682w, all unique);
  a naive single-image link still needs generated
  SECTIONS (959 sections); no link claimed.
- Wave-19bu (3EE3-3FC3 dark body + A-out verdict).
  New `3EE3` (16w stability loop: double-read port
  13 masked to 14 bits, loop to agreement; exits A
  = reading, B = 0) and `3EF3` (209w port-config
  ladder: INTM-gated pa2 RMW, timed writes, mode
  lane 680/640/1696, 4x SUB_4007 + ROUTINE_3FFA,
  exterior exit to FRAG_3FC4 on bit 5 of 0x3EC8).
  Both .asm + .c, recombine MATCH, check_c 406 OK.
  CONFLICT SETTLED: A-OUT wins -- the loop rewrites
  A and B unconditionally, so callee-preservation is
  impossible for any caller of 0x3EE1. Fixed the
  three wrong callers (C semantics otherwise
  unchanged): 2983.c, 4474.c, a7b7.c now assign
  `a = port13_stable_read()` (stub now int with
  abut tail into STABLE_READ_3EE3); a2c3.c already
  modeled A-out, updated to the shared int name.
  check_c 406 OK, recombine 967/967, make test exit
  0. Asm-only 3EE1 callers (aa7c/aac7/a361)
  unaffected (byte truth). No new test file: change
  is intent-documentation; existing gates
  (EXPECT-vs-ROM, recombine, make test) verify byte
  truth.
- Wave-12 overlap ownership pass (one owner per word).
  link_audit overlaps 57 -> 0 (959 spans, 53682w, all
  unique). recombine 959/959 MATCH. check_c 579 OK,
  0 FAIL. make test exit 0. coverage symbols 981
  (897 bounded), merged 54172/55296 = 98.0%. gaps 53
  runs / 1614w (dark, unchanged); outside 3
  (pre-existing). test_recombine floor 54646 ->
  53682 (dedup: same bytes, each counted once).
  Method per site: objdump ground truth of the ROM
  bytes; exit word belongs to the exiting span;
  ret-first twins deleted; mis-origin drafts re-homed
  to their true function bounds; giants split.
  Sites: 7f74/821f/83b3/83cd/83e7/83fe/8412/
  84ce/8500/8507/9041?/e54a/90d5?/90e6?/90f7? deleted
  or re-homed (ret-abut dups); 81f1 232w split to
  81f2 (46w C) + 82b7 (20w C) + 82d4-head (5w pool,
  rsbx); 643e/644a ret@644A to 643e (644b file);
  649d/649f operand@649F to 649d (64a0 file; bare
  xc-blt word restored); 7fb4 trimmed to own lanes;
  80fb trimmed to ret; 836c deleted, 836d extended
  15w -> 31w (C, 837C lane + 8384 join in-span);
  83xx chain ret-twins removed (83a0/83b4/83ce/
  83e8/83ff own exits); 8449 cluster: 84ae giant +
  84ce/8500/8507 twins deleted, lanes 8508 (asm +
  8507 C head) + 8513/851E (11w C each) owned;
  853B fanout re-homed (26w C) + 861F stub (8w C);
  90xx: 9042 (47w pool) + 90b9 (29w) + 90d6/90e7
  (17w pools) + 9071 (71w); a679 trimmed to 14w
  (sled C keeps intent; retd unconditional, no
  fall-through -- early C draft with tail-call
  deleted); ff40 trimmed to 33w head; E-tile:
  e42d-head 21w + e442 41w (delays restored) +
  e46b 39w + e492, exact tiling, zero gaps added.
  Corrections: OR Smem zero-extends per op_or_smem
  (81f2 C; 82a5 sign-extended lane flagged for
  review); 9042 dadst/dsadt order x2 (recombine
  DIFF); e42d DP-dma bare-hex form (0x6c).
  symbols.yaml: stale SUB85_644B entry rewritten
  (split reality); added 64A0/8508/8513/851E/861F
  entries; refreshed A679/E42D/FF40/853B/90xx.

## Wave-13: oracle-grounded C corrections + live-C continuation
- Oracle leaves consulted directly: op_sub_src_asm
  (dst = dst - src<<SHIFT), op_sub_smem_shift (dst = src -
  Smem<<SHIFT), op_add_smem (dst = src + Smem<<16),
  op_dual_arithmetic (dual X/Y SXM-widened <<16, X-first),
  op_poly_smem (A = rnd(T*AH + B_old), B = Smem<<16),
  MIN_ACC (A = min(A,B)), DADD/DSADT semantics.
- Fixed across live C: SUB/ADD Smem <<16 scale (e583,
  b61f, 87d3, ac07, e50b, e59d, bfb7, e837, 8f7a);
  accumulator-first shift forms as dst_old +/- src<<SHFT
  (e0a2, e8c7 x5, 8f7a x3, 7f75); dual mem-mem results <<16
  with X-first order (e0a2 x2, e8c7 x7, e50b, e837);
  MPYA/MAC/MACSU/MAS T-vs-dual forms (b61f, bfb7, 772f);
  4-operand SUB/ADD/MAS = (Xmem<<SHFT or X*Y) -/+ src
  (e583, e50b, 8f7a x2, 772f, c556); POLY dual-channel
  (bfb7); ADDS same Smem<<16 addend + saturate (bfb7);
  ASM threaded as dark shifter (e8c7); DLD lane order +
  DST two-store (ac07); MVPD template via prom_read_word
  with ROM-ramp Pmad proof (d9e1); subc_step32 (e59d);
  bit_merge_7EA7/late_leaf_9217 call arg forms.
- XC direction corrected tree-wide: XC executes when its
  condition holds (e0a2 x2, b61f, 9d16 x3, e583).
- Delay-slot rule settled from the silicon pattern:
  BD/BCD/BANZD/CALLD/RETD take 2 delay WORDS; BANZ/BCC/B
  are immediate (no slots). CALLD order fixed: delays,
  call, return-address load (ac07, 7e88). RPTBD blocks end
  at REA with delays outside: re-mapped 7f95 (block =
  7 words, or/stl are BANZD delays), 7e88 (block =
  4 words; banz-taken preempted by delay-slot ret --
  7E92 target dead, flagged), 7f75 (same shape),
  c556/90f8 single-representative passes.
- d95f dual-SUB order corrected (was Y-X, now X-Y per its
  own header rule). 2d8f already correct (wave-12).
- Provisional extern convention for asm-owned in-image
  spans and mid-span joins (frag_88AD, frag_B0A1_tail,
  sub_86FB/89C4/7067/9042/9071/9315/C53D, helper_0594,
  sub_059E/067A/0696/06DA); far_1A839/1A425 (XPC pages).
- 90F8 outer-BANZ re-arm documented OPEN (caller-evidenced
  return vs no in-span exit path; asm header updated).
- New rule: EXPECT always embedded from program.be16,
  never hand-composed (90f8/c556/88b9 caught by check_c).
- Gates: check_c 852 OK / 0 FAIL, recombine 1011/1011
  MATCH, make test exit 0.

## Wave-13 continued: live-C ascending (859 OK)
- c556 (MAC lattice), 88b9 (init/block-copy, tail to 8854
  zone), b080 (port gate chain with far_1A839/1A425 XPC
  calls + B0A9/B09D/B0A1/A87F legs), ff40 (LMS lane;
  LMS grounded via op_lms_dual -- dc18 note stale),
  9ad2 (INTM mailbox lane), ab56 (predicate; XC BOV
  qualifier oracle-unbound, flagged), ba08 (threshold;
  BA07 = predecessor RETD with shared-word delays),
  ceb4 (masked merge; AND/OR Smem zero-extend), dd77
  (abs-accum; SRCCD/SACCD are conditional STORES per
  oracle -- store-BRC / store-shifted-acc -- with
  delayed-commit order modeled), 953c (port sweep).
- Smem-logical zero-extension applied tree-wide (AND/OR/
  XOR Smem clear upper; acc-acc and imm forms unaffected).
- Provisional join-extern convention extended
  (frag_88AD, frag_B0A1_tail, frag_95A2/956E, sub_2C88).
- EXPECT-from-image rule held (c556/88b9/ff40 hand drafts
  caught by check_c before commit).

## Wave-14: live-C ascending 31-40w (check_c 875 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
Hand-wrote C intent for 9ce7 (XC-2-over-orm resync + DP:2 ADD), ba32 (dual RPTBD shuffle, MIN oracle), cf01 (CALLD pre-call delays), 82d9 (ROR/ROL/SFTA/SFTL oracle, RPTB in BANZD), 8894 (BK=0 frozen splat per oracle indirect_circular), 7937 (RPTBD quad-call), afd3/b0c2 (guard lanes), 7c2f (DADD + flagged 1-word DST/DLD), 89c4 (AND-immediate = A&(lk<<SHFT) per oracle, MPYA = T x A-high), 9fa8 (absolute DST/DLD oracle rows), e9a1 (BANZ shoot-first do-while). a687 dropped as dup (owned by a679_meas_setup_b Entry 1; direction *(0x337B) = *(0x54A) confirmed same). 2c8a `sftl b,-1` <<1 modeling contradicts oracle (SFTL -1 = logical right); flagged for a later correction pass, not silently fixed mid-wave.

## Wave-14b: live-C 40-42w (check_c 882 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
87eb (FRCT=1 MAC/min/max lane), af16 (MVDK-to-AR scatter, RPTZ N+1 confirmed), e442 (quad MAC lane; caught + fixed zeroed-mpya bug, T threaded via maca read-phase load), 8ddb (MACR/MACAR exact rounding from oracle op_multiply; exact BRC+1 incl. wrap retrofitted to 7937/af16), ab2c (BCD-delay + all-paths-bitf retrace), ac22 (AR-select branches), e000 (dual-MAC FIR). New oracle-grounded rules: MVKD dmad = source; MVDK dmad = dest; MPYA-Smem = Smem x A-high into B (T untouched); MACA/MACAR loads T from Smem; MACR rounding = (sum+0x8000)&~0xFFFF; AND-imm = A&(lk<<SHFT); 1-word DST/DLD = MSW@AR LSW@(AR+1) step 2 (flagged gap, structural corroboration); BK=0 freezes % sources (oracle indirect_circular); `st||ld` parallel reads pre-store.

## Wave-14c: correction debt logged (do not silently fix mid-wave)
- 2c8a `sftl b,-1` modeled <<1 contradicts oracle (SFTL negative = logical right). Flagged for a dedicated correction pass with its siblings.
- 2d8f/4b81 ADDS modeled as sign-extended plain add; oracle op_adds_smem says zero-extended + OVM-gated saturation. New files use oracle form; old files queued for the same correction pass.

## Wave-14d: live-C 43-45w (check_c 887 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
ced6 (EXP/NORM/SUBC/SQUR/SQUARA all oracle-grounded; exact rounding + TS conventions), dad2 (bcd-lane joins, retd-delay repeat-abandoned), 72e3 (bubble compare-swap, nested BANZD/RPTB count caveat flagged), bf21 (ADDS zero-extend per oracle; butterfly), 7ab1 (guard cascade, no-op self-join branch noted).

## Wave-14e: live-C 45-46w (check_c 890 OK / 0 FAIL, recombine 1011 MATCH)
88da (dual-copy lanes), 8b03 (single-word RPTBD block -- dual runs once after; mutually-exclusive xc proof), 9c61 (xor-fold; call-redefined A/B convention). BCD delay = 2 WORDS re-verified (orm only); every-path-runs-bitf retrace pattern (ac22) -- stale-TC modeling corrected before commit.

## Wave-14f: live-C 45-46w (check_c 891 OK / 0 FAIL, recombine 1011 MATCH)
88da (BK=0 frozen sources), 8b03 (single-word RPTBD block; mutually-exclusive xc proof), 9c61 (xor-fold; call-redefined A/B), 7ab1 (guard cascade, no-op self-join), a815 (fcalld pre-call delays, bit-merge tail). New rule: `st||ld` parallel reads pre-store memory (8ddb C891); RPT N+1 incl. RPT-Smem (af16).

## Wave-14g: live-C 46w e4dd (check_c 892 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
e4dd (PSHM_POPM_GATE): lattice post-filter gate, RPTBD x4 + once-tail. Oracle-settled rules: 1-word DLD/DADD/DRSUB indirect *ARx+/- steps AR by 2 (oracle indirect_single LONG32 MOD1/2; DADD/DRSUB Lmem legs route LONG32_SINGLE kind-21); `sub a,1,b` = B -= A<<1 (oracle SUB_ACC_SHIFT, bit9 = src, bit8 = dst, shift[4:0]); `ld #-13,asm` single-word ED13 (ASM = -13); `stl b,asm,*ar` = low16(B>>13). Tail-overlap (drsub pair = next dld pair) modeled faithfully, noted.

## Wave-14g (cont): live-C 47w 7d31 (check_c 893 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
7d31 (SUB_7D31): mode-gated zero-init lane; cmpm TC = (Smem == lk) per oracle op_cmpm_smem_lk; B = *AR2 & 240 flag-dead; skip/tail joins via goto/early-return.

## Wave-14g (cont): 3623 kept stage-owned, brev primitive derived (check_c 893 OK / 0 FAIL)
3623 (FRAG_3623): a new frag_3623.c was written then REMOVED -- wave-12 3623_frag_3623_stage.c already owns the span (overlap guard tripped, correctly). Stage keeps the 351d linear convention (ar2 += ar0_live, wrap flagged) and local frag_93CE/frag_2E64 extern names. New ground for a future tree-wide `%` pass, derived from oracle foundation/reverse_carry.h + indirect_reverse_carry.c: reverse-carry carry/borrow propagates bit 15 -> bit 0, old AR addresses, post-access update; `+%` = add (MOD7), `-%` = subtract (MOD4) by TI suffix-sign convention (MOD-number assignment flagged oracle-unbound); oracle reverse-carry is WORD16-only, matching that no `%` appears on long-word forms. Exact C helpers drafted (rcarry_add/rcarry_sub) but NOT committed, pending a consistent `%`-span convention decision with 351d.

## Wave-14h: live-C 47w ae71 + 9760 (check_c 895 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
ae71 (SUB_AE71): six entry lanes (71/75/79 stubs, 7B bitf-pair, 87, 8E) per 389c per-lane pattern; TRACE heads + unconditional-b shadowing cited. xc 2,alt execute-when-true; sub_0596 low-zone binding (72e3 precedent).
9760 (SUB_9760): port-strobe gate. New grounded rules: PORTR numeric-port form carries a port-address extension word (0036 = port 54; 978f EXPECT corroborates 7482 0036); AND_IMMEDIATE_SHIFT decode (F130: src A dst B shift 0, B = A & 4096; oracle layout bits 9/8/[3:0]); COND_BEQ = B zero (oracle branch cond); frag_978F (A-low,B,AR2) + sub_2D5E(AR2,AR3) passthroughs; port extern-op decls (portr_port54_cell08, portw_par2_port1, portr_port2_par2, portw_par2_port2); sub_05C2 mini-kernel extern (pchist-evidenced).

## Wave-14i: live-C 48w b431 + 7eec + 86fb (check_c 898 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
b431 (ROUTINE_B431): mode-cell switch; sub_05A8 dark (b358 binding), routine_B39E passthrough, rpt/mvdd x8, set-bit lane join.
7eec (SUB_7EEC): four-phase stm/calld/bd lanes; family bindings sub_7F55 + frag_7F95 (7ebe/7ec6), delay-first ordering, TRACE-range lane entries flagged; no overlap with 7EC6 (starts exactly at 7EEC).
86fb (SHARED_SUB_86FB): keyed-mix loop. New grounded rules: ADD Smem,SHIFT SXM = 0 gives logical right shift (oracle op_add_smem_shift: signed -16..15, SXM-ruled right); LD with SXM = 0 zero-extends; T-shift count = T & 0x3F (oracle ld leaves); ROL carry thread (82d9); BANZ test-then-decrement while-idiom; LD-TS plain `<< t` (82d9); `bc nc` repeat-abandon to the mar end word (dad2 precedent).

## Wave-14j: live-C 49w b3b1 + d3be (check_c 900 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
b3b1 (ROUTINE_B431): helper-call fork; MVKD/MVDK both copy first->second (2000/2088/22f3 precedents); LD_LK shift-0 (oracle layout); BNEQ/BEQ (oracle cond); AF40 AR1-dark intake; A654 pooled comment-only; pshm/popm comments.
d3be (CLAMP_STORE_SUB head): min/max clamp-store lane. New grounded rules: MIN_ACC dst = bit 8 (F587 dst B, F487 dst A; ba32 convention oracle-confirmed); MPYA_SMEM (0x3100 row + extension) does T <- Smem then B = Smem x A-high REPLACE (oracle leaf; 87eb/e442 form; 71a3 `+=` and 89c4 `T untouched` readings now correction-debt, logged not fixed); AND-Smem zero-ext (2acc); MVDM cell->AR idiom; retd delays owned by D3EF span (no overlap; function renamed clamp_store_sub_D3BE to avoid the delay-pair file's name).

## Wave-14k: live-C 50w 9bc3 + 51w d499 (check_c 902 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
9bc3 (FRAG_9BC3): banz sieve; wrap_9C4D(AR2,AR4,AR6) + frag_9BF5/frag_9BF8 passthroughs; 9BBE epilogue inlined (verified 9B72 tail words); frag_9C15 shared-join void+dark (361c precedent); banz test-then-dec gotos; 351d linear `%` steps; ld-shift SXM? (4b9a); ldm (long)ar.
d499 (D499_SHARED_TAIL): min/max filter pump. New grounded rules: DELAY Smem does *(Smem+1) = *(Smem) write-back + AR step (oracle op_delay_smem; 25f2 no-C-form note now correction-debt); MAX_ACC dst = bit 8 (F586 dst B: B = max); MPYA long-offset = MPYA_SMEM (0x3100 row + ext); MVDM cell->AR; DP = 0 assumed (da40); DP switches as hardware comments; routine_DB81(A) under DP = 20; delay-pump AR threading gives exact tap shifts.

## Wave-14l: live-C 52w 9682 + a6ae (check_c 904 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
9682 (ROUTINE_9682): table-fill with port-bit exits; sub_05C4 mini-kernel extern (pchist-evidenced); B entry-dark read by and #128,b (decoded src/dst B via oracle layout bits -- same-word check applied tree-wide); portr_port54_cell0B extern (existing name); frag_96B6 tails; xc beq/tc lanes; retd delays in next span.
a6ae (SUB_A6AE): measurement-gate fanout; sub_065E RAM-resident (a679), sub_BA56/sub_B750 A-live dark takes (a679), sub_9FCF asm-only (a8d4), C5F9/BCFC pooled comment-only; ccd always-delay shape (a7eb: delay duplicated both arms); SUB_LK shift-0; bitf -32768 = bit 15.

## Wave-14m: live-C 53w abd2 (check_c 905 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
abd2 (ROUTINE_ABD2): select-and-scan loop; frag_71A3/scale_3EB8_leaf_71D8/frag_AC22/frag_AC07 passthroughs with entry AR2/AR3 params and dark-A intake; pshm/popm comments; SUB 2-op dst -= src vs 4-op dst = Smem<<SHIFT - src (dd77); AC00 decoded as sub *ar2+,0,a,b (4-op shift 0: probe proved 6F92 0D20, killing a phantom -32 shift -- binutils range-errors out-of-range shifts); banz test-then-dec loop; plain ADD Smem (long)+SXM flag.

## Wave-14n: live-C 54w 82fe + 8b9d + 9c99 (check_c 908 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
82fe (LEAF43_82D4): abuts 82d9 (post-RET head not modeled, DP = 0 in-span grounds absolute cells); full 82d9-dance mirror incl ror/rol/sfta + or/stl + banzd-do/while.
8b9d (ROUTINE_8B9D): rounded-MAC viper with per-lane entries (389c pattern, dark BRC/AR4/A/AR0 params); MPYR rounded (22f3), MACAR oracle pair (8ddb), parallel st||ld pre-store tmp (8ddb), +0% linear + AR0 (351d); sth tail; retd delays in-span.
9c99 (CHAIN_HEAD_9C99): gain-apply + dispatch; sub_06D4/06BE mini-kernel externs (06BE pchist-evidenced); 9F35/8BDE/86E3 pooled; superblock_8C0A asm-only extern; frag_9CCF/frag_9CE7 tails; RPTBD delay-once + 160x; andm TC-neutral (required for xc-after-cmpm); xc+3-word-orm overlap: taken runs orm, skip executes 0x4000 as unidentified 1-worder (byte-probe verified, flagged).

## Wave-14o: live-C 56w 8334 + a91c + e0b5 (check_c 911 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
8334 (SUB_8335): ret@8334 LEAF54 abut (not modeled); call 0686 dark; A from RAM cells; and #-1 = &0xFFFF; reada = program[A]->cell (oracle op_reada.h direction); bacc b dark exit via dark_8335_target (28a5 precedent); tail 8346-836B unreachable-in-model (whole-image xref scan: zero external targets in-range), documented not executed.
a91c (ROUTINE_A91C): rc tc / rc aneq (RC cond8 catalog row 694, carry 0-modeled, unread in-span); bitf TC=(Smem&lk)!=0; orm TC-neutral (catalog neutral rows); xc-andm lane; rpt-mvkd x57 broadcast fill; d29e pooled; D0BE/872B asm-only externs; 0686 dark extern.
e0b5 (ROUTINE_E0B5): neg/xc-alt MAC filter lane; A/AR2/AR0 dark params; stm#-9 AR0 rides all % steps (351d convention); rptbd 40x mpy+18mac+macr (795d plain + 8b9d round shape, FRCT flagged); first draft wrote 19 alternating macs, check_c word-compare caught E0E8 mismatch -- fixed to image 17+1 (EXPECT embedded-from-image rule vindicated again).
Correction debt: 454F reada direction (454f_sub_454f.c models A = prom[cellB]; oracle op_reada.h says cellB = prom[A]; 8335 follows the oracle; 8335's compute-then-mask-to-16-bit A supports address-use). 454F left untouched (green); revisit with a reada probe.

## Wave-14p: live-C 58w b3e2 + 9c13 (check_c 913 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
b3e2 (ROUTINE_B3E2): 3-phase straight-line setup; 05A8 dark extern (no symbol); frag_B41C extern; mvdk direction flip phase1 vs 2/3; cmpm+rc ntc / rc aeq; carry 0-modeled unread.
9c13 (FRAG_9C13): dual entry (9C13 xor + 9C15 4x joins) via frag+lane pair (8b9d pattern); cc passes AR5/AR3/A/AR1 per 9B5C contract; bc-9bdc = interior join frag_9BDC into 9bc3 @+0x19 (28d6 precedent); banz AR-test-dec (4ee0); or a,-16 = OR_ACC_SHIFT dst=A logical (op_logical ground); 9C61 redefines A dark (2e84 clobber convention); ccd delay-always (a7eb/351d); mvmm address-as-value cast.

## Wave-14q: live-C 59w 7e4d + badb (check_c 915 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
7e4d (SUB90_7E4D): 059E dark extern; rptb offset-load lane + rptbd delay-once + retd exit; OR_ACC_SHIFT S=bit9/D=bit8 layout ground (operand_layout_sets.c) fixes or b,8,a as A |= B<<8 and vindicates 9c13 or a,-16 as A |= A>>16.
badb (ROUTINE_BADB): 06AA dark extern; AR2 dark param; ST1 save/restore with ssbx OVM/FRCT -- FRCT=1 KNOWN in-span so all mpy/mpya double (<<1 modeled, first known-FRct span; OVM small-values per 3d3d); bcd delay-always diamond; max signed idiom (22f3); ADD_SMEM_SH16 as A += (22f3); MPYA replace+load-T (wave-14/e442); sub a,-3,b arithmetic (SXM flagged); st||mpy parallel pre-write store.

## Wave-14r: live-C 60w a843 (check_c 916 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
a843 (FRAG_A843): post-A815 head; cmpm+3x bitf/rc status web; cc-ntc fanout; rpt-mvkd broadcast; ccd-anex into AB7E = ab78 rptz lane interior (new INTERIOR triage section; frag_AB7E forward extern); cc-aeq pooled 9E2F; A8FE dispatch; BKMAX asm-only; BAC2(AR2) via calld delay.

## Wave-14s: live-C 61w 6ae9 + 9a82 (check_c 918 OK / 0 FAIL, recombine 1011 MATCH, test exit 0)
6ae9 (FRAG_6AE9): no own exit (falls into SPANHEAD_6B26); NORM = shift-by-signed6(T) per op_norm_acc (no T write; OVM/SXM flagged); MIN dst-bit rule (bit8: 0=A like 22f3 max, 1=B); full 32-bit DLD/DST pair (22f3 single-word dld noted partial, not followed); bc-6B26 + bc-6B3F(interior @+0x19, new INTERIOR triage line) tails; B-sign xc fill lanes; TC1 (bitf) survives mvdk/call to final bc.
9a82 (FRAG_9A82): single head entry (6x pre-span bc verified in listing; interior joins all in-span); 3-word stack-carry to 9AD2 (push ar2/al/al vs its pops al/bl/ar2 per its C; pooled-9ABF exit leaves them, flagged); sfta shift-out carry (59dc) clobbers sub borrow (not modeled, noted); OR-Smem zero-extends (2289) vs AND-Smem sign-extends (59dc) kept per-op; +% linear (25f2); bc-ntc to pooled 9ABF (return, no extern).
