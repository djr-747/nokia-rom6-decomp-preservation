/* ROM6 0xDA48 DA48_SUB_DA48 -- 54w (Pool).
 * Verified encoding: src/rom6/kernel/da48_sub_da48.asm (recombine MATCH).
 * ORIGIN 0xDA48
 * EXPECT: 7714 007A 10F8 0B68 F030 0004 F47E 6FF8 0079 0C01 F000 D9D3 F030 FFFF 7E84 E801 1860 FA45 DA65 6B5F 0001 F020 D9D8 0084 F030 FFFF 7E60 F073 DA75 F4BC 1084 F110 0003 FA4C DA6F F000 D9DC 6160 0080 F030 FFFF 7E60 FF30 6960 0100 6160 0001 F820 DA80 7662 0000 7661 0017 FE00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/da48_sub_da48.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
