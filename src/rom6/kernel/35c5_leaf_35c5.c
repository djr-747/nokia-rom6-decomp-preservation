/* ROM6 0x35C5 35C5_LEAF_35C5 -- 68w (Pool).
 * Verified encoding: src/rom6/kernel/35c5_leaf_35c5.asm (recombine MATCH).
 * ORIGIN 0x35C5
 * EXPECT: 71DA 0578 F074 2E2F F073 2E64 7714 263A 7713 051C 4811 F0E8 F030 1800 F845 35DB 1AF8 051F 80F8 051F F844 35EE 61F8 0011 0004 F820 35E4 6984 0200 F073 35EE 61F8 0011 0002 F820 35EC 6983 0002 FF20 6983 0001 61F8 0011 0001 F830 3608 6883 FFFC 6884 FDFF 68F8 051F E7FF 10F8 2510 F030 00F0 F010 00C0 F844 3608 76F8 2EFE 0001 76F8 0B67 0001 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS leaf.
 * (see src/rom6/kernel/35c5_leaf_35c5.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
