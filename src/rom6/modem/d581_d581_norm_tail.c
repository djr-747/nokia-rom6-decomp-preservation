/* ROM6 0xD581 D581_D581_NORM_TAIL -- 71w (Pool).
 * Verified encoding: src/rom6/modem/d581_d581_norm_tail.asm (recombine MATCH).
 * ORIGIN 0xD581
 * EXPECT: F58E 7609 8000 8C08 6B08 FFFF 3008 F78F 0309 771A 0026 8306 F272 D592 948E F58D 948E E200 F84C D599 6C86 D5CA F073 D5B5 F58E 4406 F78F 0309 8305 EC0E 1E05 8004 6F04 0C47 490E 0908 8104 3204 F274 E54B F482 EA00 EA60 6E86 D5CA F469 0209 770E 0CCC F58C F363 FFFF 771A 0027 7713 3007 7712 3004 ED00 7082 0B58 F272 D5C6 7683 7333 B201 E420 F48C F463 8294 FE00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: sqdst *ar2,*ar2 (E200, wave-12). Dual-memory X/Y step modes plus the SXM/FRCT/OVM status tuple are all dark in-span (no ST1 setup anywhere in D581-D5C7
 * (see src/rom6/modem/d581_d581_norm_tail.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
