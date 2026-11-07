/* ROM6 0x7142 7142_SEL_3490_3WAY -- 37w (Pool).
 * Verified encoding: src/rom6/kernel/7142_sel_3490_3way.asm (recombine MATCH).
 * ORIGIN 0x7142
 * EXPECT: F074 05B4 61F8 3490 0001 F830 7155 61F8 3490 0002 F830 715E FF45 7712 34D6 76F8 0533 0000 FC00 76F8 37F6 0000 7712 34E2 FF44 7712 347E FC00 76F8 37F7 0000 7712 34EE FF44 7712 3486 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/7142_sel_3490_3way.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
