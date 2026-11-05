# Worklog + ROM image understanding / coverage

This log is a running record. Entries run newest first. Dates are UTC.

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
