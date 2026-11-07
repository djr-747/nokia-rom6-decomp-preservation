/* ROM6 0xE144 E144_BLK_E144 -- 40w (Pool).
 * Verified encoding: src/rom6/kernel/e144_blk_e144.asm (recombine MATCH).
 * ORIGIN 0xE144
 * EXPECT: FA4D E15A 771A 0025 6D8A A435 F272 E150 7710 FFFE F461 3C92 CC5C F461 3C92 C874 6F82 0C7E 6E8F E120 7710 FFD9 6D8A A435 F272 E162 7710 FFFE F463 3C92 CC5C F463 3C92 C874 8282 6E8F E120 7710 FFD9 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/e144_blk_e144.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
