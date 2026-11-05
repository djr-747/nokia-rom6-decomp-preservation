# Firmware DSP-table classification (generated)

Regenerate: `python3 tools/classify.py` (see tool header for rules).
Refs: 5110 v5.30 (ROM4) + 3310 v5.79 (ROM6). Only F073 PROM-code-zone (0x2800–0xAFFF) targets count; DROM/DARAM/VEC excluded.

| image | table | band | verdict | evidence |
|---|---|---|---|---|
| 2100/NAM-2/archive/2100_download_calib-restored_003F0000.fls | — | no table | **** |  |
| 2100/NAM-2/archive/2100_knowngood_v5.21_003F0000.fls | — | no table | **** |  |
| 2100/NAM-2/archive/2100_knowngood_v5.84_003F0000.fls | — | no table | **** |  |
| 2100/NAM-2/archive/Nokia 2100 NAM-2 v5.21 A (Sharp full).fls | 0x314E2C | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 2100/NAM-2/v5.03/Nokia 2100 NAM-2 v5.03 A.fls | 0x313E28 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 2100/NAM-2/v5.05/Nokia 2100 NAM-2 v5.05 A.fls | 0x314AAC | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 2100/NAM-2/v5.11/Nokia 2100 NAM-2 v5.11 A.fls | 0x314870 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 2100/NAM-2/v5.21/Nokia 2100 NAM-2 v5.21 A.fls | 0x314E2C | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 2100/NAM-2/v5.49/Nokia 2100 NAM-2 v5.49 A.fls | 0x314BC0 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 2100/NAM-2/v5.56/Nokia 2100 NAM-2 v5.56 A.fls | 0x314D28 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 2100/NAM-2/v5.64/Nokia 2100 NAM-2 v5.64 A.fls | 0x315044 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 2100/NAM-2/v5.78/Nokia 2100 NAM-2 v5.78 A.fls | 0x3150A8 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 2100/NAM-2/v5.84/Nokia 2100 NAM-2 v5.84 A.fls | 0x315104 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 2100/NAM-2/v5.84/Nokia 2100 NAM-2 v5.84.fls | 0x315104 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 3210/NSE-8/archive/Nokia 3210 NSE-8 v6.00 A.fls | 0x2B73D4 | R4 | **ROM4** | pay=17 range=0926-F870 R4ref=23 R6ref=0 miss@R4=0/48 |
| 3210/NSE-8/archive/Nokia 3210 NSE-8 v6.00 A.fls | 0x2BC994 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=20 miss@R6=1/24 |
| 3210/NSE-8/v5.01/Nokia 3210 NSE-8 v5.01 A.fls | 0x2BB064 | R4 | **ROM4** | pay=17 range=0926-F870 R4ref=25 R6ref=0 miss@R4=0/46 |
| 3210/NSE-8/v5.26/Nokia 3210 NSE-8 v5.26 A.fls | 0x2BC7B4 | R4 | **ROM4** | pay=17 range=0926-F870 R4ref=25 R6ref=0 miss@R4=0/46 |
| 3210/NSE-8/v5.36/Nokia 3210 NSE-8 v5.36 A.fls | 0x2B60D8 | R4 | **ROM4** | pay=17 range=0926-F870 R4ref=25 R6ref=0 miss@R4=0/46 |
| 3210/NSE-8/v5.36/Nokia 3210 NSE-8 v5.36 A.fls | 0x2BB648 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=19 miss@R6=1/23 |
| 3210/NSE-8/v6.00/Nokia 3210 NSE-8 v6.00 A.fls | 0x2B73D4 | R4 | **ROM4** | pay=17 range=0926-F870 R4ref=23 R6ref=0 miss@R4=0/48 |
| 3210/NSE-8/v6.00/Nokia 3210 NSE-8 v6.00 A.fls | 0x2BC994 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=20 miss@R6=1/24 |
| 3310/NHM-5/archive/3310_knowngood_v5.79_003D0000.fls | — | no table | **** |  |
| 3310/NHM-5/archive/3310_knowngood_v6.39_003D0000.fls | — | no table | **** |  |
| 3310/NHM-5/v5.79/Factory Reset 3310 NR1 v5.79.fls | 0x300CD8 | R6 | **ROM6** | pay=20 range=0940-FF85 R4ref=0 R6ref=30 miss@R6=1/30 |
| 3310/NHM-5/v6.39/Nokia 3310 NHM-5 v6.39 A.fls | 0x3020B4 | R6 | **ROM6** | pay=20 range=0940-FF85 R4ref=0 R6ref=30 miss@R6=1/30 |
| 3330/NHM-6/archive/3330_knowngood_v4.16_00550000.fls | — | no table | **** |  |
| 3330/NHM-6/archive/3330_knowngood_v4.50_00550000.fls | — | no table | **** |  |
| 3330/NHM-6/v4.16/Nokia 3330 NHM-6 v4.16 A.fls | 0x3D673C | R6 | **ROM6** | pay=21 range=0940-FF85 R4ref=0 R6ref=30 miss@R6=1/30 |
| 3330/NHM-6/v4.50/Nokia 3330 NHM-6 v4.50 A.fls | 0x3D6804 | R6 | **ROM6** | pay=22 range=0940-FF85 R4ref=0 R6ref=30 miss@R6=1/30 |
| 3350/NHM-9/v5.11/Nokia 3350 NHM-9 v5.11 A.fls | 0x3E5600 | R6 | **ROM6** | pay=22 range=0940-FF85 R4ref=0 R6ref=30 miss@R6=1/30 |
| 3350/NHM-9/v5.15/Nokia 3350 NHM-9 v5.15 A.fls | 0x3E9EF8 | R6 | **ROM6** | pay=22 range=0940-FF85 R4ref=0 R6ref=30 miss@R6=1/30 |
| 3350/NHM-9/v5.22/Nokia 3350 NHM-9 v5.22 A.fls | 0x3EACF4 | R6 | **ROM6** | pay=22 range=0940-FF85 R4ref=0 R6ref=30 miss@R6=1/30 |
| 3350/NHM-9/v5.25/Nokia 3350 NHM-9 v5.25 A.fls | 0x3EACF4 | R6 | **ROM6** | pay=22 range=0940-FF85 R4ref=0 R6ref=30 miss@R6=1/30 |
| 3350/NHM-9/v5.30/Nokia 3350 NHM-9 v5.30 A.fls | 0x3EAD0C | R6 | **ROM6** | pay=22 range=0940-FF85 R4ref=0 R6ref=30 miss@R6=1/30 |
| 3410/NHM-2/archive/3410_knowngood_v5.46_00570000.fls | — | no table | **** |  |
| 3410/NHM-2/archive/Nokia 3410 NHM-2 v5.46 (FAID off, cksum fixed).fls | 0x46FBFC | R6 | **ROM6** | pay=20 range=0940-FF85 R4ref=0 R6ref=30 miss@R6=1/30 |
| 3410/NHM-2/archive/Nokia 3410 NHM-2 v5.46 (chksums).fls | 0x46FBFC | R6 | **ROM6** | pay=20 range=0940-FF85 R4ref=0 R6ref=30 miss@R6=1/30 |
| 3410/NHM-2/v5.46/Nokia 3410 NHM-2 v5.46 (assembled).fls | 0x46FBFC | R6 | **ROM6** | pay=20 range=0940-FF85 R4ref=0 R6ref=30 miss@R6=1/30 |
| 3410/NHM-2/v5.46/Nokia 3410 NHM-2 v5.46 A.fls | 0x46FBFC | R6 | **ROM6** | pay=20 range=0940-FF85 R4ref=0 R6ref=30 miss@R6=1/30 |
| 3610/NAM-1/v5.11/Nokia 3610 NAM-1 v5.11 A (provisioned identity, TEXT fixed).fls | 0x41E390 | R6 | **ROM6** | pay=21 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 3610/NAM-1/v5.11/Nokia 3610 NAM-1 v5.11 A.fls | 0x41E390 | R6 | **ROM6** | pay=21 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 5110/NSE-1/archive/Nokia 5110 NSE-1 v5.30 A (FAID off).fls | 0x2948EC | R4 | **ROM4** | pay=18 range=0926-F870 R4ref=29 R6ref=0 miss@R4=0/29 |
| 5110/NSE-1/archive/Nokia 5110 NSE-1 v5.30 A (FAID off, cksum fixed).fls | 0x2948EC | R4 | **ROM4** | pay=18 range=0926-F870 R4ref=29 R6ref=0 miss@R4=0/29 |
| 5110/NSE-1/archive/Nokia 5110 NSE-1 v5.30 A.fls | 0x2948EC | R4 | **ROM4** | pay=18 range=0926-F870 R4ref=29 R6ref=0 miss@R4=0/29 |
| 5110/NSE-1/v5.04/Nokia 5110 NSE-1 v5.04 A.fls | 0x292804 | R4 | **ROM4** | pay=18 range=0926-F870 R4ref=23 R6ref=0 miss@R4=1/25 |
| 5110/NSE-1/v5.27/Nokia 5110 NSE-1 v5.27 A.fls | 0x2941EC | R4 | **R3-witness** | pay=18 range=0926-F470 R4ref=2 R6ref=0 miss@R4=10/84 |
| 5110/NSE-1/v5.28/Nokia 5110 NSE-1 v5.28 A.fls | 0x294760 | R4 | **ROM4** | pay=18 range=0926-F870 R4ref=29 R6ref=0 miss@R4=0/29 |
| 5110/NSE-1/v5.29/Nokia 5110 NSE-1 v5.29 A.fls | 0x2947BC | R4 | **ROM4** | pay=18 range=0926-F870 R4ref=29 R6ref=0 miss@R4=0/29 |
| 5110/NSE-1/v5.30/Nokia 5110 NSE-1 v5.30 A.fls | 0x2948EC | R4 | **ROM4** | pay=18 range=0926-F870 R4ref=29 R6ref=0 miss@R4=0/29 |
| 5110i/NSE-2/v5.51/Nokia 5110i NSE-2 v5.51 A.fls | 0x29C034 | R4 | **ROM4** | pay=18 range=0926-F870 R4ref=29 R6ref=0 miss@R4=0/29 |
| 5110i/NSE-2/v5.53/Nokia 5110i NSE-2 v5.53 A.fls | 0x29C160 | R4 | **ROM4** | pay=18 range=0926-F870 R4ref=29 R6ref=0 miss@R4=0/29 |
| 5130/NSK-1/archive/Nokia 5130 NSK-1 v5.30 A.fls | 0x296410 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=22 R6ref=0 miss@R4=0/41 |
| 5130/NSK-1/v5.01/Nokia 5130 NSK-1 v5.01 D.fls | 0x296410 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=22 R6ref=0 miss@R4=0/41 |
| 5130/NSK-1/v5.30/Nokia 5130 NSK-1 v5.30 A.fls | 0x296DA4 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=23 R6ref=0 miss@R4=1/44 |
| 5130/NSK-1/v5.61/Nokia 5130 NSK-1 v5.61 A.fls | 0x29727C | R4 | **R3-witness** | pay=17 range=0926-F470 R4ref=2 R6ref=0 miss@R4=10/89 |
| 5130/NSK-1/v5.71/Nokia 5130 NSK-1 v5.71 A.fls | — | no table | **** |  |
| 5190/NSB-1/v6.11/Nokia 5190 NSB-1 v6.11 A.fls | 0x2B2C54 | R4 | **R3-witness** | pay=17 range=0926-F470 R4ref=2 R6ref=0 miss@R4=10/89 |
| 5190/NSB-1/v6.11/Nokia 5190 NSB-1 v6.11 A.fls | 0x2B8B94 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=23 R6ref=0 miss@R4=1/44 |
| 5190/NSB-1/v6.71/Nokia 5190 NSB-1 v6.71 A.fls | 0x2B35A4 | R4 | **R3-witness** | pay=17 range=0926-F470 R4ref=2 R6ref=0 miss@R4=10/89 |
| 5190/NSB-1/v6.71/Nokia 5190 NSB-1 v6.71 A.fls | 0x2B94E4 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=23 R6ref=0 miss@R4=0/46 |
| 5210/NSM-5/archive/5210_knowngood_v5.40_00580000.fls | — | no table | **** |  |
| 5210/NSM-5/v5.13/Nokia 5210 NSM-5 v5.13 A.fls | 0x409EC4 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 5210/NSM-5/v5.16/Nokia 5210 NSM-5 v5.16 A.fls | 0x40B10C | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 5210/NSM-5/v5.18/Nokia 5210 NSM-5 v5.18 A.fls | 0x40B52C | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 5210/NSM-5/v5.20/Nokia 5210 NSM-5 v5.20 A.fls | 0x40BA08 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 5210/NSM-5/v5.22/Nokia 5210 NSM-5 v5.22 A.fls | 0x40BA40 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 5210/NSM-5/v5.25/Nokia 5210 NSM-5 v5.25 A.fls | 0x40BAEC | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 5210/NSM-5/v5.40/Nokia 5210 NSM-5 v5.40 A.fls | 0x40BAEC | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 5510/NPM-5/archive/5510_knowngood_v3.50_00550000.fls | — | no table | **** |  |
| 5510/NPM-5/archive/5510_knowngood_v3.53_00550000.fls | — | no table | **** |  |
| 5510/NPM-5/v3.50/Nokia 5510 NPM-5 v3.50 A.fls | 0x3E13F4 | R6 | **ROM6** | pay=22 range=0940-FF85 R4ref=0 R6ref=30 miss@R6=1/30 |
| 5510/NPM-5/v3.53/Nokia 5510 NPM-5 v3.53 A.fls | 0x3E3304 | R6 | **ROM6** | pay=22 range=0940-FF85 R4ref=0 R6ref=30 miss@R6=1/30 |
| 6110/NSE-3/archive/Nokia 6110 NSE-3 v5.48 A.fls | 0x2A5FE4 | R4 | **R3-witness** | pay=17 range=0926-F470 R4ref=2 R6ref=0 miss@R4=10/84 |
| 6110/NSE-3/v4.06/Nokia 6110 NSE-3 v4.06 A.fls | 0x2A5870 | R4 | **R3-witness** | pay=17 range=0926-F470 R4ref=2 R6ref=0 miss@R4=8/79 |
| 6110/NSE-3/v5.40/Nokia 6110 NSE-3 v5.40 A.fls | 0x2A77E4 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=29 R6ref=0 miss@R4=0/29 |
| 6110/NSE-3/v5.47/Nokia 6110 NSE-3 v5.47 A.fls | 0x2A6EEC | R4 | **R3-witness** | pay=17 range=0926-F470 R4ref=2 R6ref=0 miss@R4=10/84 |
| 6110/NSE-3/v5.48/Nokia 6110 NSE-3 v5.48 A.fls | 0x2A7CE4 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=29 R6ref=0 miss@R4=0/29 |
| 6130/NSK-3/archive/Nokia 6130 NSK-3 v5.61 A.fls | 0x2AE9B4 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=23 R6ref=0 miss@R4=1/44 |
| 6130/NSK-3/v5.00/Nokia 6130 NSK-3 v5.00 A.fls | 0x2AD824 | R4 | **R3-witness** | pay=17 range=0926-F470 R4ref=2 R6ref=0 miss@R4=10/85 |
| 6130/NSK-3/v5.30/Nokia 6130 NSK-3 v5.30 A.fls | 0x2AE328 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=23 R6ref=0 miss@R4=1/44 |
| 6130/NSK-3/v5.51/Nokia 6130 NSK-3 v5.51 A.fls | 0x2AE838 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=23 R6ref=0 miss@R4=1/44 |
| 6130/NSK-3/v5.61/Nokia 6130 NSK-3 v5.61 A.fls | 0x2AE9B4 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=23 R6ref=0 miss@R4=1/44 |
| 6150/NSM-1/v5.17/Nokia 6150 NSM-1 v5.17 A.fls | 0x2C1054 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=25 R6ref=0 miss@R4=1/39 |
| 6150/NSM-1/v5.20/Nokia 6150 NSM-1 v5.20 A.fls | 0x2C47E4 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=25 R6ref=0 miss@R4=1/39 |
| 6150/NSM-1/v5.22/Nokia 6150 NSM-1 v5.22 A.fls | 0x2C47E4 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=25 R6ref=0 miss@R4=1/39 |
| 6150/NSM-1/v5.23/Nokia 6150 NSM-1 v5.23 A.fls | 0x2C4FEC | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=25 R6ref=0 miss@R4=1/39 |
| 6190/NSB-3/archive/Nokia 6190 NSB-3 v6.13 A.fls | 0x2B7168 | R4 | **R3-witness** | pay=17 range=0926-F470 R4ref=2 R6ref=0 miss@R4=10/89 |
| 6190/NSB-3/archive/Nokia 6190 NSB-3 v6.13 A.fls | 0x2BD0A8 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=23 R6ref=0 miss@R4=1/44 |
| 6190/NSB-3/v6.13/Nokia 6190 NSB-3 v6.13 A.fls | 0x2B7168 | R4 | **R3-witness** | pay=17 range=0926-F470 R4ref=2 R6ref=0 miss@R4=10/89 |
| 6190/NSB-3/v6.13/Nokia 6190 NSB-3 v6.13 A.fls | 0x2BD0A8 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=23 R6ref=0 miss@R4=1/44 |
| 6210/NPE-3/v5.56/Nokia 6210 NPE-3 v5.56 A.fls | 0x21EAB8 | R6 | **ROM6** | pay=21 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/42 |
| 6250/NHM-3/v5.00/Nokia 6250 NHM-3 v5.00 A.fls | 0x2178F8 | R6 | **ROM6** | pay=20 range=0940-FF85 R4ref=0 R6ref=20 miss@R6=1/25 |
| 6250/NHM-3/v5.03/Nokia 6250 NHM-3 v5.03 C.fls | 0x2178F8 | R6 | **ROM6** | pay=20 range=0940-FF85 R4ref=0 R6ref=22 miss@R6=1/27 |
| 7110/NSE-5/archive/7110_knowngood_v5.00_00590000.fls | — | no table | **** |  |
| 7110/NSE-5/v5.00/My 7110 v5.00.fls | 0x2284EC | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=24 R6ref=0 miss@R4=1/51 |
| 7110/NSE-5/v5.01/Nokia 7110 NSE-5 v5.01 A.fls | 0x2284EC | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=24 R6ref=0 miss@R4=1/51 |
| 8210/NSM-3/archive/8210_knowngood_v5.11_003D0000.fls | — | no table | **** |  |
| 8210/NSM-3/archive/8210_knowngood_v5.16_003D0000.fls | — | no table | **** |  |
| 8210/NSM-3/archive/8210_knowngood_v5.20_003D0000.fls | — | no table | **** |  |
| 8210/NSM-3/archive/8210_knowngood_v5.21_003D0000.fls | — | no table | **** |  |
| 8210/NSM-3/archive/8210_knowngood_v5.25_003D0000.fls | — | no table | **** |  |
| 8210/NSM-3/archive/8210_knowngood_v5.26_003D0000.fls | — | no table | **** |  |
| 8210/NSM-3/archive/8210_knowngood_v5.27_003D0000.fls | — | no table | **** |  |
| 8210/NSM-3/archive/8210_knowngood_v5.28_003D0000.fls | — | no table | **** |  |
| 8210/NSM-3/archive/8210_knowngood_v5.29_003D0000.fls | — | no table | **** |  |
| 8210/NSM-3/archive/8210_knowngood_v5.30_003D0000.fls | — | no table | **** |  |
| 8210/NSM-3/archive/8210_knowngood_v5.31_003D0000.fls | — | no table | **** |  |
| 8210/NSM-3/v5.11/Nokia 8210 NSM-3 v5.11 A.fls | 0x313D8C | R6 | **R5-witness** | pay=19 range=0940-FF85 R4ref=0 R6ref=0 miss@R6=8/31 |
| 8210/NSM-3/v5.16/Nokia 8210 NSM-3 v5.16 A.fls | 0x3141CC | R6 | **R5-witness** | pay=19 range=0940-FF85 R4ref=0 R6ref=0 miss@R6=8/31 |
| 8210/NSM-3/v5.20/Nokia 8210 NSM-3 v5.20 A.fls | 0x314660 | R6 | **R5-witness** | pay=19 range=0940-FF85 R4ref=0 R6ref=0 miss@R6=8/34 |
| 8210/NSM-3/v5.21/Nokia 8210 NSM-3 v5.21 A.fls | 0x314A90 | R6 | **R5-witness** | pay=19 range=0940-FF85 R4ref=0 R6ref=0 miss@R6=8/34 |
| 8210/NSM-3/v5.25/Nokia 8210 NSM-3 v5.25 A.fls | 0x314AEC | R6 | **R5-witness** | pay=19 range=0940-FF85 R4ref=0 R6ref=0 miss@R6=9/37 |
| 8210/NSM-3/v5.26/Nokia 8210 NSM-3 v5.26 A.fls | 0x3158C8 | R6 | **R5-witness** | pay=19 range=0940-FF85 R4ref=0 R6ref=0 miss@R6=9/37 |
| 8210/NSM-3/v5.27/Nokia 8210 NSM-3 v5.27 A.fls | 0x30DEA0 | R6 | **R5-witness** | pay=19 range=0940-FF85 R4ref=0 R6ref=0 miss@R6=9/37 |
| 8210/NSM-3/v5.27/Nokia 8210 NSM-3 v5.27 A.fls | 0x314FD0 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 8210/NSM-3/v5.28/Nokia 8210 NSM-3 v5.28 A.fls | 0x30DC94 | R6 | **R5-witness** | pay=19 range=0940-FF85 R4ref=0 R6ref=0 miss@R6=9/37 |
| 8210/NSM-3/v5.28/Nokia 8210 NSM-3 v5.28 A.fls | 0x314DC4 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 8210/NSM-3/v5.29/Nokia 8210 NSM-3 v5.29 A.fls | 0x30DD68 | R6 | **R5-witness** | pay=19 range=0940-FF85 R4ref=0 R6ref=0 miss@R6=9/37 |
| 8210/NSM-3/v5.29/Nokia 8210 NSM-3 v5.29 A.fls | 0x314E98 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 8210/NSM-3/v5.30/Nokia 8210 NSM-3 v5.30 A.fls | 0x30DD7C | R6 | **R5-witness** | pay=19 range=0940-FF85 R4ref=0 R6ref=0 miss@R6=9/37 |
| 8210/NSM-3/v5.30/Nokia 8210 NSM-3 v5.30 A.fls | 0x314EAC | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 8210/NSM-3/v5.31/Nokia 8210 NSM-3 v5.31 A.fls | 0x30DFEC | R6 | **R5-witness** | pay=19 range=0940-FF85 R4ref=0 R6ref=0 miss@R6=9/37 |
| 8210/NSM-3/v5.31/Nokia 8210 NSM-3 v5.31 A.fls | 0x31511C | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 8250/NSM-3D/archive/8250_knowngood_v6.02_003D0000.fls | — | no table | **** |  |
| 8250/NSM-3D/v6.02/Nokia 8250 NSM-3D v6.02 J.fls | 0x3122CC | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 8290/NSB-7/archive/8290_knowngood_v5.22_003D0000.fls | — | no table | **** |  |
| 8290/NSB-7/v5.22/Nokia 8290 NSB-7 v5.22 A.fls | 0x3115B8 | R6 | **R5-witness** | pay=19 range=0732-FF85 R4ref=0 R6ref=0 miss@R6=10/38 |
| 8290/NSB-7/v5.22/Nokia 8290 NSB-7 v5.22 A.fls | 0x3183A4 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=26 miss@R6=1/29 |
| 8810/NSE-6/archive/Nokia 8810 NSE-6 v6.02 A.fls | 0x2E7D9C | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=24 R6ref=0 miss@R4=0/34 |
| 8810/NSE-6/v5.00/Nokia 8810 NSE-6 v5.00 A.fls | 0x2EAC80 | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=23 R6ref=0 miss@R4=0/33 |
| 8810/NSE-6/v6.02/Nokia 8810 NSE-6 v6.02 A.fls | 0x2E7D9C | R4 | **ROM4** | pay=16 range=0926-F870 R4ref=24 R6ref=0 miss@R4=0/34 |
| 8850/NSM-2/archive/8850_knowngood_v5.11_003D0000.fls | — | no table | **** |  |
| 8850/NSM-2/archive/8850_knowngood_v5.26_003D0000.fls | — | no table | **** |  |
| 8850/NSM-2/archive/8850_knowngood_v5.31_003D0000.fls | — | no table | **** |  |
| 8850/NSM-2/v5.11/Nokia 8850 NSM-2 v5.11 J.fls | 0x3140FC | R6 | **R5-witness** | pay=19 range=0940-FF85 R4ref=0 R6ref=0 miss@R6=8/31 |
| 8850/NSM-2/v5.26/Nokia 8850 NSM-2 v5.26 A.fls | 0x315C2C | R6 | **R5-witness** | pay=19 range=0940-FF85 R4ref=0 R6ref=0 miss@R6=9/37 |
| 8850/NSM-2/v5.31/FuBu8850 v5.31 (PPM C).fls | 0x30E22C | R6 | **R5-witness** | pay=19 range=0940-FF85 R4ref=0 R6ref=0 miss@R6=9/37 |
| 8850/NSM-2/v5.31/FuBu8850 v5.31 (PPM C).fls | 0x31535C | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 8850/NSM-2/v5.31/Nokia 8850 NSM-2 v5.31 A.fls | 0x30E22C | R6 | **R5-witness** | pay=19 range=0940-FF85 R4ref=0 R6ref=0 miss@R6=9/37 |
| 8850/NSM-2/v5.31/Nokia 8850 NSM-2 v5.31 A.fls | 0x31535C | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 8855/NSM-4/archive/8855_knowngood_v5.13_00580000.fls | — | no table | **** |  |
| 8855/NSM-4/v5.13/Nokia 8855 NSM-4 v5.13 A.fls | 0x3F9994 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 8855/NSM-4/v5.13/Nokia 8855 NSM-4 v5.13 P.fls | 0x3F9994 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 8855/NSM-4/v5.16/Nokia 8855 NSM-4 v5.16 A.fls | 0x3FA998 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 8855/NSM-4/v5.18/Nokia 8855 NSM-4 v5.18 A.fls | 0x3FAE04 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 8855/NSM-4/v5.20/Nokia 8855 NSM-4 v5.20 A.fls | 0x3FB2A8 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 8855/NSM-4/v5.22/Nokia 8855 NSM-4 v5.22 A.fls | 0x3FB370 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 8855/NSM-4/v5.23/Nokia 8855 NSM-4 v5.23 A.fls | 0x3FB370 | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=27 miss@R6=1/28 |
| 8890/NSB-6/archive/8890_knowngood_v12.16_003D0000.fls | — | no table | **** |  |
| 8890/NSB-6/v12.16/Nokia 8890 NSB-6 v12.16 A.fls | 0x30BA98 | R6 | **R5-witness** | pay=19 range=0732-FF85 R4ref=0 R6ref=0 miss@R6=9/36 |
| 8890/NSB-6/v12.16/Nokia 8890 NSB-6 v12.16 A.fls | 0x312C1C | R6 | **ROM6** | pay=19 range=0940-FF85 R4ref=0 R6ref=25 miss@R6=1/28 |
