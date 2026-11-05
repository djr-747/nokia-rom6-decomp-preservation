# ROM6 — the 2000+ LEAD (active target)

The DSP reports version 6 at boot. ROM6 serves phones 3310, 3410, 6210,
8210/8250/8290, 8850/8855/8890.

## Images (`images/`, gitignored — see `docs/03-image-catalog.md`)

- `images/rom6-program.be16` — 65536 words, SHA-256
  `b450413a…c50097c63eee4cf` (full value in doc 03).

## Reference firmware (for the paged blocks; bring your own `.fls`)

| firmware | DSP table @flash | F073 range | notes |
|----------|-----------------|------------|-------|
| 3310 NHM-5 v5.79 | `0x300CD8` | `0940–FF85` | ROM6 reference build |
| 3410 NHM-2 v5.46 A | `0x46FBFC` | `0940–FF85` | 100% F073-overlap with 3310 |
| 8850 NSM-2 v5.31 A | `0x30E22C` | `0940–FF85` | 21% overlap (feature divergence) |
| 6210 NPE-3 v5.56 A | `0x21EAB8` | `0940–FF85` | 37% overlap |

## Contents

- `symbols.yaml` — word-address symbol file (schema v1). Seed entries
  are below. Every entry carries `confidence:` per doc 05.
- `vectors.md` — reset/interrupt vectors plus first verified instructions.
- `messages.md` — MDISND/MDIRCV vocabulary (grows with annotation).
- `blocks/` — committed `manifest.json` per reference firmware. `.bin`
  payloads live in `build/`.
- `src/` — C decomp, mirrored with `asm/` listings.

## Seed symbols (static, confirm before use as ground truth)

| addr | name | basis |
|------|------|-------|
| `0x220B` data | `RSSI_SELECTOR_BIT_TEST` | static branch audit, RF RSSI path |
| `0x022A` data | `RX_INITIAL_RAW_FILL_BLOCK_COUNT` | timed-transfer probe readout |
| `0x022C` data | `RX_REQUEST_KIND_FLAGS` | kind dispatch (`1`/`9` observed) |
| `0x022D` data | `RX_REQUEST_PARAMETER` | kind parameter word |
| `0x2627` data | `RSSI_SELECTOR_FLAGS` | RSSI selector state |
