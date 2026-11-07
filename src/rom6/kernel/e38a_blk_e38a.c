/* ROM6 0xE38A E38A_BLK_E38A -- 11w (Pool).
 * Verified encoding: src/rom6/kernel/e38a_blk_e38a.asm (recombine MATCH).
 * ORIGIN 0xE38A
 * EXPECT: 771A 0008 F272 E391 E58A 3093 2292 E49A FE00 2292 8294
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/e38a_blk_e38a.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
