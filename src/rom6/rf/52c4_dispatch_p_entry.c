/* ROM6 0x52C4 52C4_DISPATCH_P_ENTRY -- 51w (Pool).
 * Verified encoding: src/rom6/rf/52c4_dispatch_p_entry.asm (recombine MATCH).
 * ORIGIN 0x52C4
 * EXPECT: F074 059C 61F8 2627 0008 F820 56B9 76F8 263E 0000 68F8 2512 FBFF 61F8 3EC8 0010 F820 52E2 7712 0589 6882 7FFF 11F8 0589 F330 4000 F84D 52E2 6982 8000 61F8 2549 0004 F820 52F7 7711 0924 1089 F030 001F 770E 052E 8809 F48C 0081 0AF8 2479 F844 56B9 F073 5315
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/rf/52c4_dispatch_p_entry.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
