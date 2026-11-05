# ROM4 paged-block tables per phone build

Same dual-table caveat as [ROM6](../rom6/blocks/README.md): verdicts are
per build. All 5110 builds fingerprinted so far carry a **single**
ROM4-range table.

| phone | firmware | table @flash | F073 range | verdict |
|-------|----------|--------------|------------|---------|
| 5110 | NSE-1 v5.04 | `0x292804` | `0926–F870` | ROM4 |
| 5110 | NSE-1 v5.27 | `0x2941EC` | `0926–F470` | ROM4 (smaller max; genuinely smaller table or walk variance — open) |
| 5110 | NSE-1 v5.28 | `0x294760` | `0926–F870` | ROM4 |
| 5110 | NSE-1 v5.29 | `0x2947BC` | `0926–F870` | ROM4 |
| 5110 | NSE-1 v5.30 | `0x2948EC` | `0926–F870` | ROM4 |
| 5110i | NSE-2 v5.51 | `0x29C034` | `0926–F870` | ROM4 |
| 5110i | NSE-2 v5.53 | `0x29C160` | `0926–F870` | ROM4 |

Notes:

- No ROM3-range table observed locally. The 5110 is mostly ROM4 (v5.04/v5.28/v5.29/v5.30 + all 5110i — clean
  16–18-payload ROM4 tables), with one R3-witness build: v5.27 (single
  18-payload table, standard link slots, R4-band, 2/84 R4-API, 11% ROM4
  miss rate). Singles per build, not dual images — Nokia shipped
  per-silicon firmware here, both tables never in one image.
- 6110: v5.40/v5.48 (dir copy) = ROM4 singles; v4.06/v5.47 + the
  archive-labelled "v5.48 A" copy = R3-witness singles (17 payloads,
  standard slots, F470-capped). The archive "v5.48" md5-differs from
  the v5.48/ copy — treat its label as suspect (likely an older build).
- 6130: v5.00 = R3-witness single; v5.30/v5.51/v5.61 = ROM4 singles.
  No phone is currently attached to ROM3 as a dual partner — R3 shows
  up in single-table builds and as first tables of duals.
- 3210 (NSE-8 v5.36 @`0x2B60D8`, v6.00 @`0x2B73D4`): ROM4 half of a
  dual; the ROM6 half is inventoried in rom6/blocks.
- 5190 (NSB-1 v6.11 @`0x2B2C54` + `0x2B8B94`, v6.71 @`0x2B35A4` +
  `0x2B94E4`): dual. First table = **R3 witness** (17 payloads; 99 PROM
  targets, 2 R4-API, 0 R6-API, 11% operand-miss in ROM4 incl. sampled
  STM-immediate landings); second table = ROM4. Same signature v6.11
  and v6.71 — stable across builds. Adjacent tables; walk splits on the
  second loader.
- 6190 (NSB-3 v6.13 @`0x2B7168` + `0x2BD0A8`): dual, same split as
  5190 (first table 99/2/0/11% — identical signature; shared US code
  base). First table = R3 witness, second = ROM4.
- 6150 (NSM-1 v5.17–v5.23): single table per build, all ROM4-range
  (`0926–F870`). Not a dualie in these builds.
- 6110 / 3210 / 7110: survey addresses (6110 v5.48 @`0x2A7CE4`, 3210
  v6.00 @`0x2B73D4`, 7110 v5.01 @`0x2284EC`) — re-fingerprint on hand,
  do not copy blind.
