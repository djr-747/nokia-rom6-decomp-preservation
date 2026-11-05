# ROM6 paged-block tables per phone build

One MCU firmware image can carry **two** DSP block tables; the MCU
picks one by silicon ID (see `docs/02-boot-and-upload.md`). The verdict
is therefore per **build**, never per model. Fingerprinted with
`tools/fingerprint.py` (F073 call-target range over the fully walked
table; walker validated 20/20 payload blocks against the committed
3310 manifest).

Payload-block inventory is exact. Zero-slot (placeholder) counts are
"as found" — zero padding between blocks is indistinguishable from
empty slots, so counts may exceed the factory slot numbering. Only
payload blocks feed the ROM verdict.

## Fingerprinted builds (all ROM6 in local images)

| phone | firmware | tables @flash | payload blocks | F073 range | verdict |
|-------|----------|---------------|----------------|------------|---------|
| 3310 | NHM-5 v5.79 | `0x300CD8` (single) | 20 | `0940–FF85` | ROM6 |
| 8210 | NSM-3 v5.11 | `0x313D8C` (single) | — | `0940–FF85` | ROM6 |
| 8210 | NSM-3 v5.29 | `0x30DD68`(A) + `0x314E98`(B) | 19 + 19 payloads | both `0940–FF85` | **B=R6 (validated), A=R5 (leaning) — see note** |
| 8210 | NSM-3 v5.31 | `0x30DFEC` + `0x31511C` (dual) | 254 + 224t | both `0940–FF85` | same pattern as v5.29, not yet discriminated |
| 8850 | NSM-2 v5.11 | `0x3140FC` (single) | — | `0940–FF85` | ROM6 |
| 8210 | NSM-3 v5.27 | `0x30DEA0` + `0x314FD0` (dual) | 444 + 224t | both `0940–FF85` | open: same pattern as v5.29 |
| 3210 | NSE-8 v5.36 | `0x2B60D8` + `0x2BB648` (dual) | 311 + 199t | `0926–F870` + `0940–FF85` | **ROM4 + ROM6, one image** |
| 3210 | NSE-8 v6.00 | `0x2B73D4` + `0x2BC994` (dual) | 315 + 202t | `0926–F870` + `0940–FF85` | **ROM4 + ROM6, one image** |
| 8290 | NSB-7 v5.22 | `0x3115B8` + `0x3183A4` (dual) | 444 + 223t | `0732–FF85` + `0940–FF85` | ROM6 + ROM6 (first table low-min suspect) |
| 8850 | NSM-2 v5.31 | `0x30E22C` + `0x31535C` (dual) | 444 + 224t | both `0940–FF85` | ROM6 + ROM6 (v5.11 was single) |
| 8890 | NSB-6 v12.16 | `0x30BA98` + `0x312C1C` (dual) | 439 + 222t | `0732–FF85` + `0940–FF85` | ROM6 + ROM6 (first table low-min suspect) |

Notes:

- The 3210 dual is the cross-generation proof: one image, one ROM4
  table and one ROM6 table, silicon-ID selected.
- 8210 v5.29 discriminator (tools/compare_sets.py on clean 19+19
  sets; 18/19 blocks pair as same-logic, one (block01) diverges):
  PROM targets disjoint (37 vs 28, overlap 0), DROM disjoint (14 vs 12,
  overlap 0), DARAM shared (77 overlap). B-side = ROM6 API (27/28 PROM
  + 12/12 DROM match the 3310-validated set); A-side matches neither
  reference anywhere. Paired call sites show systematic re-target
  deltas (F074 +0x33 ×99, −0x1E clusters; DROM +0x18 parallel runs —
  same tables relocated). A-side operand-landing rate in the ROM6 image
  is 17% vs 2% for validated entries (one example: A-side `0x2A6C` is a
  `portw` operand word in ROM6 — unexecutable as an entry). Verdict:
  B=R6, A=R5 — by elimination over the closed DCT3 set {R3,R4,R5,R6}:
  A matches neither the validated ROM4 API (0/37 PROM, 0/14 DROM) nor
  the validated ROM6 API (0/37, 0/14; 17% operand-landing in the ROM6
  image vs 2% baseline), and R3 is excluded by era (early-5110
  generation; never shipped in an 8210). A is a well-formed 19-block
  sibling set pairing 1:1 with B's, so it targets a real sibling PROM —
  the only remaining slot is R5. Positive confirmation still wants an
  R5 image or the MCU selector/version-byte read (expected 5 vs 6).
- No ROM5-range (or ROM3-range) table has been observed in any local
  image. No phone is currently attached to either slot.
- Recurring 64-descriptor / ~444-target first tables (8210, 8290,
  8850 v5.31, 8890): uniform signature, low-min on 8290/8890 — walk
  over-run suspected. Payload-block inventory exact; band verdicts
  unaffected; descriptor counts on those four are not trusted.
- 3410 / 6210 / 8250 / 8290 / 8850-later: table addresses from the
  emulator's ROM-revision survey (3410 v5.46 @`0x46FBFC`, 6210 v5.56
  @`0x21EAB8`, 8850 v5.31 @`0x30E22C`) — re-fingerprint when those
  images are on hand; do not copy the survey's verdict blind.

## Committed manifests

- `3310-v5.79-manifest.json` — payload descriptors from the
  emulator's `re/dsp/` extraction, cross-checked 20/20 against the
  walker. New builds: `tools/extract_blocks.py --fls … --table …`
  and commit the manifest (payload `.bin` files stay in `build/`).
