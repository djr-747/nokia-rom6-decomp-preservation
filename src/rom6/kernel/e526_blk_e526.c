/* ROM6 0xE526 E526_BLK_E526 -- 12w (Pool).
 * Verified encoding: src/rom6/kernel/e526_blk_e526.asm (recombine MATCH).
 * ORIGIN 0xE526
 * EXPECT: 771A 0008 F272 E52E 8285 4182 9E0E A038 4182 FE00 F495 9E0E
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/e526_blk_e526.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
