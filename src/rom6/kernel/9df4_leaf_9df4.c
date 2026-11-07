/* ROM6 0x9DF4 9DF4_LEAF_9DF4 -- 59w (Pool).
 * Verified encoding: src/rom6/kernel/9df4_leaf_9df4.asm (recombine MATCH).
 * ORIGIN 0x9DF4
 * EXPECT: F074 06C2 4A07 4A06 F7B6 F7B8 F7B9 60F8 0573 AF57 F820 9E0E F274 9D9A 7713 3196 10F8 085D F030 0002 F845 9E2C 7713 3196 F073 9E1C F074 06C2 F274 9D9A 7713 3236 10F8 085D F030 0001 F845 9E2C 7713 3236 E901 7212 057D F074 9D2D 7312 057D 10F8 057C F030 0FFF F847 9E2C 6BF8 057C FFFF 8A06 8A07 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/9df4_leaf_9df4.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
