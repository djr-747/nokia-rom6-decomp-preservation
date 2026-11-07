/* ROM6 0xE855 E855_FRAME_DIV_E855 -- 24w (Pool).
 * Verified encoding: src/rom6/kernel/e855_frame_div_e855.asm (recombine MATCH).
 * ORIGIN 0xE855
 * EXPECT: EEFF 10F8 3E21 7000 2D31 EC0F 1E00 F030 FFFF 11F8 3E23 F520 890E F166 4CCD F610 80F8 3E24 80F8 3E24 EE01 8A09 8A08 F4E6
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * gap pool).
 * (see src/rom6/kernel/e855_frame_div_e855.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
