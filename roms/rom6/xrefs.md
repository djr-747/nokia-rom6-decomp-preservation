# 3310 setB block → mask-ROM cross-references (static)

Method: objdump each payload (`build/3310-v579/blockNN.bin`), collect
`B/BC/CALL/FB` targets. Full map: `/tmp/xref/3310-setB-xrefs.json`
(staged; regenerate with the objdump loop). Counts below.

| block | ROM | DROMband | DARAM | note |
|---|---|---|---|---|
| block00 | 13 | 0 | 46 | branch table + loader1 |
| block01 | 47 | 12 | 120 | main code / MDI dispatch |
| block04 | 0 | 0 | 0 | data page (params) |
| block06 | 12 | 0 | 33 | — |
| block08 | 12 | 0 | 63 | — |
| block09 | 7 | 0 | 31 | — |
| block11 | 0 | 0 | 35 | code, no ROM calls |
| block13 | 4 | 0 | 7 | — |
| block15 | 8 | 0 | 46 | — |
| block17 | 0 | 0 | 0 | data page (params) |
| block19 | 17 | 0 | 63 | — |
| block20 | 3 | 0 | 29 | — |
| block23 | 2 | 3 | 2 | runtime IVT image |
| block30 | 11 | 2 | 13 | — |
| block32/35/38 | 0 | 0 | 0 | data or undecoded |
| block41/45 | 1 | 0 | 0 | single ROM call each |
| block48 | 0 | 0 | 14 | code, no ROM calls |

Shared core (called by 3+ blocks): `0x2E2F` (dispatcher = ROM4
`3900`; also the resident-ISR callee), `0x3986`, `0x3EE1`, `0x4007`
(port txn A = ROM4 `45c2`), `0x4055` (port txn B = ROM4 `4610`).
The shared core is the dedicated-mode spine: dispatch plus port
transactions.
