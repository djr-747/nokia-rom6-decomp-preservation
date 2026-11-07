/* ROM6 0x6FB1 6FB1_RANKSEL_6FB1 -- 41w (Pool).
 * Verified encoding: src/rom6/kernel/6fb1_ranksel_6fb1.asm (recombine MATCH).
 * ORIGIN 0x6FB1
 * EXPECT: F074 05B4 6FE3 0004 0D20 FA4F 6FD7 E903 F495 6FE3 0005 0D20 FA4F 6FD7 E904 F495 6FE3 0006 0D20 FA4F 6FD7 E905 F495 6FE3 0007 0D20 FA4F 6FD7 E906 F495 6FE3 0008 0D20 FA4F 6FD7 E907 F495 E908 F640 8A13 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/6fb1_ranksel_6fb1.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
