/* ROM6 0x877D 877D_SUB_877D -- 70w (Pool).
 * Verified encoding: src/rom6/kernel/877d_sub_877d.asm (recombine MATCH).
 * ORIGIN 0x877D
 * EXPECT: F074 0590 7714 051D 962D F820 87C3 6884 FFFB 60F8 09C7 0000 F820 87C3 F274 872B 7714 09C8 11F8 09CD F33B 0007 F520 F84C 87C3 60F8 0573 B11C F830 87BF 10F8 051C F030 1003 00F8 3083 F844 87BF 7711 B351 7714 09C8 F274 87C7 771A 0005 08F8 0575 F843 87C3 7716 0003 F274 87C7 771A 0006 F110 0078 F84E 87C3 F010 0028 F843 87C3 6C8E 87B1 76F8 3082 0000 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/877d_sub_877d.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
