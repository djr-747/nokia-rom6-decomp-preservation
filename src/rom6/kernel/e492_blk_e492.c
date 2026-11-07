/* ROM6 0xE492 E492_BLK_E492 -- 57w (Pool).
 * Verified encoding: src/rom6/kernel/e492_blk_e492.asm (recombine MATCH).
 * ORIGIN 0xE492
 * EXPECT: 8062 4A14 4A15 4A13 4A11 E754 771A 0009 F272 E4A0 770E FFFF 1492 0493 8094 F274 E4DD E713 E752 8A13 8A12 1062 4A12 4A13 FB44 E4DD 6DEB 000B 771A 0009 8A13 8A11 8A12 8A14 770E FFFF F272 E4BC 4A14 4A12 1491 0494 8092 8A12 4A13 F274 E4DD 6DEB 0016 8A13 8A12 1062 FB44 E4DD 6DEB 0021 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/e492_blk_e492.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
