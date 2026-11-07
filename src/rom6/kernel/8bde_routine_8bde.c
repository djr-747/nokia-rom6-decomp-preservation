/* ROM6 0x8BDE 8BDE_ROUTINE_8BDE -- 44w (Pool).
 * Verified encoding: src/rom6/kernel/8bde_routine_8bde.asm (recombine MATCH).
 * ORIGIN 0x8BDE
 * EXPECT: F074 0612 4A07 F6BE F7B9 F7B6 EA5E 7713 2F7D E732 771A 009F F272 8BEF 770E FFFD 1494 9892 7713 1000 7714 1001 7622 4000 ED1F 771A 009F F272 8C07 770E 7FDF A201 E501 2394 F611 2884 F57F 8284 408C 8484 0122 9B81 8A07 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/8bde_routine_8bde.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
