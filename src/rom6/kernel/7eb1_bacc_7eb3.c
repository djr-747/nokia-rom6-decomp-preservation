/* ROM6 0x7EB1 7EB1_BACC_7EB3 -- 11w (Pool).
 * Verified encoding: src/rom6/kernel/7eb1_bacc_7eb3.asm (recombine MATCH).
 * ORIGIN 0x7EB1
 * EXPECT: F2C0 828C F074 059E F000 B153 8813 F495 F495 1083 F4E2
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS: no in-span caller
 * (see src/rom6/kernel/7eb1_bacc_7eb3.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
