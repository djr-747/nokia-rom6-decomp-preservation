/* ROM6 0x7C03 7C03_SUB84_7C03 -- 41w (Pool).
 * Verified encoding: src/rom6/kernel/7c03_sub84_7c03.asm (recombine MATCH).
 * ORIGIN 0x7C03
 * EXPECT: F074 05A0 60F8 0013 0001 F020 20A5 F487 FD20 F461 8816 1081 F120 05B4 F487 F120 02DC F486 770E 1B58 20F8 0008 F0F3 71F8 0016 000E 20F8 0008 F0F3 6F85 0D20 F84B 7C2C EC0F 1E85 F030 FFFF F000 0001 F073 7BEE
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS. Head-fill Bound 7C03-7C2B (wave-5: exit B@7C2A->7BEE chained i
 * (see src/rom6/kernel/7c03_sub84_7c03.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
