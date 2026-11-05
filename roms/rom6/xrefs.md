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

## Payload identity (build file → manifest block → run range)

| file | manifest | runs at | note |
|---|---|---|---|
| block00.bin | block00 | `0x0D00-0x0F7E` | loader + branch table |
| block01.bin | block01 | `0x0930-0x14DA` | main code / MDI dispatch |
| block04/17.bin | block02/block0B | `0x0930-0x0A7C` | data pages inside block01's range |
| block06.bin | block03 | `0x09C6-0x0E43` | RF page |
| block08.bin | block04 | `0x0926-0x0FEF` | mixed RF page |
| block09.bin | block05 | `0x09C6-0x0EFA` | — |
| block11.bin | block06 | `0x09C6-0x0BF6` | — |
| block13.bin | block08 | `0x09C6-0x0AC1` | audio page |
| block15.bin | block09 | `0x09C6-0x0DE8` | audio page |
| block19.bin | block0C | `0x0B3A-0x0FD6` | — |
| block20.bin | block0D | `0x09C6-0x0BA0` | — |
| block23.bin | block0F | `0x0A00-0x0A68` | IVT image |
| block30.bin | block14 | `0x0A00-0x0C75` | overwrites IVT range (phases) |
| block32/35/38.bin | block15/16/17 | `0x0800-0x08F7` | HPI window (same payload ×3) |
| block41/45.bin | block18/1A | `0x0800-0x0943` | HPI window (same payload ×2) |
| block48.bin | block1B | `0x0F00-0x0FDF` | version publisher, overwrites loader |

Run ranges overlap: upload is phased, later phases overwrite earlier
ones (`0x0A00`: IVT image then block14; `0x0F00`: loader then
publisher; `0x0930`: code then data pages). Phase order = walk order.
A static call graph across phases is unsound without the order;
that order plus the overwrite map is the next static step.
