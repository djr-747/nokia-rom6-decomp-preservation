# ROM4 — the 1998–99 LEAD (parked)

The DSP reports version 4 at boot. ROM4 serves phones 5110, 6110, 3210,
7110.

Status: images catalogued, no active annotation. The emulator already
carries ROM4 through MO/MT voice and SMS. This slot exists for
backfill and cross-revision comparison (F073 ranges, ISR structure,
mailbox evolution ROM4→ROM6).

## Images (`images/`, gitignored)

- `images/rom4-program.be16` — 65535 words + zero slot, SHA-256
  `4a7a9ba9…9c51504f` (full value in `docs/03-image-catalog.md`).
- `images/rom4-drom.txt` — DROM dump, SHA-256 `998f006d…38f5055`.

## Reference firmware

| firmware | DSP table @flash | notes |
|----------|-----------------|-------|
| 5110 NSE-1 v5.30 A | `0x2948EC` | ROM4 reference build |
| 6110 NSE-3 v5.48 A | `0x2A7CE4` | 100% F073-overlap with 5110 |
| 3210 NSE-8 v6.00 A | `0x2B73D4` | ROM4 |
| 7110 NSE-5 v5.01 A | `0x2284EC` | ROM4 (not ROM6; size misleads) |

Activation takes two steps. Mirror `roms/rom6/` (README, symbols,
vectors, messages, blocks manifest, src). Flip the Makefile default.
