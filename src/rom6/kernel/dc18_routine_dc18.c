/* ROM6 0xDC18 DC18_ROUTINE_DC18 -- 22w (Pool).
 * Verified encoding: src/rom6/kernel/dc18_routine_dc18.asm (recombine MATCH).
 * ORIGIN 0xDC18
 * EXPECT: 7713 0B44 F020 FC91 0061 8812 771A 0009 F121 4000 0982 890E E900 F272 DC2C 7714 0B3A E109 2B94 8395 E900 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: LMS adaptive filter + MACR rounded (both oracle-unbound)
 * (see src/rom6/kernel/dc18_routine_dc18.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
