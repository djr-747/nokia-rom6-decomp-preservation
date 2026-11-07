/* ROM6 0xDB5D DB5D_SUB_DB5D -- 25w (Pool).
 * Verified encoding: src/rom6/kernel/db5d_sub_db5d.asm (recombine MATCH).
 * ORIGIN 0xDB5D
 * EXPECT: 767A 0FFF 771A 0009 F272 DB74 7710 000A 6291 3FFF 6492 3FFF 307A F58C 29B3 29B3 29B3 29B3 29B3 29B3 29B3 6DEB FFBB 8394 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/db5d_sub_db5d.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
