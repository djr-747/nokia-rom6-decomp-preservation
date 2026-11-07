/* ROM6 0x8A08 8A08_HELPER_8A08 -- 50w (Pool).
 * Verified encoding: src/rom6/kernel/8a08_helper_8a08.asm (recombine MATCH).
 * ORIGIN 0x8A08
 * EXPECT: F074 0592 7714 0008 7713 000E E900 7712 09CA 4492 F063 FF00 F274 8A3A 8183 1A92 4492 F063 FFC3 1A92 F274 8A3A 6884 C7FF 4492 1A92 F274 8A3A 6884 FF0F 4492 1A92 F274 8A3A 6884 0003 F310 0010 E800 F495 FD4B E801 F300 000E 7712 3083 FD4B E802 8082 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/8a08_helper_8a08.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
