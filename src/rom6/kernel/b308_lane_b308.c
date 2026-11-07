/* ROM6 0xB308 B308_LANE_B308 -- 62w (Pool).
 * Verified encoding: src/rom6/kernel/b308_lane_b308.asm (recombine MATCH).
 * ORIGIN 0xB308
 * EXPECT: F074 A2C3 F074 B358 F074 A3E1 F074 B431 F074 A4D5 F074 B3E2 60F8 34BF 0004 F820 B330 10F8 34C7 F845 B330 71F8 34C6 34C8 80F8 34C6 7712 3490 6882 FFF0 6982 0002 F074 B3B1 71F8 34C8 34C6 76F8 34C7 0000 68F8 3490 FFF0 F074 B3B1 10F8 34BF F845 B341 71F8 34C5 34C7 E800 80F8 34C5 80F8 34C6 F074 A7B7 F074 A7EB FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/b308_lane_b308.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
