/* ROM6 0xAF92 AF92_HELPER_AF92 -- 25w (Pool).
 * Verified encoding: src/rom6/kernel/af92_helper_af92.asm (recombine MATCH).
 * ORIGIN 0xAF92
 * EXPECT: 10F8 0914 F110 000D F495 F495 FD4B F540 8912 F310 000C 68F8 0012 0003 F84C AFAA 6FF8 2652 0D20 7712 0004 FF4D 7712 0005 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/af92_helper_af92.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
