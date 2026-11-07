/* ROM6 0x9E85 9E85_WRAP_9E85 -- 75w (Pool).
 * Verified encoding: src/rom6/kernel/9e85_wrap_9e85.asm (recombine MATCH).
 * ORIGIN 0x9E85
 * EXPECT: F074 06C6 61F8 085D 003F FC20 61F8 04C2 0004 FC30 4A07 4A06 F7B6 F7B8 F7B9 61F8 085D 0002 F820 9EBD 61F8 057C 4000 F820 9EA3 F074 9ED0 68F8 057C BFFF 61F8 057C 1000 F830 9EBD 10F8 057C F030 0FFF F847 9EBD E900 7212 057D F274 9D2D 7713 32D6 7312 057D 6BF8 057C FFFF 69F8 057C 1000 F074 06C6 61F8 085D 0004 F820 9ECD 10F8 057C F030 2000 F944 9C99 68F8 057C DFFF 8A06 8A07 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/9e85_wrap_9e85.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
