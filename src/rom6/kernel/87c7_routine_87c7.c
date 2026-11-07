/* ROM6 0x87C7 87C7_ROUTINE_87C7 -- 12w (Pool).
 * Verified encoding: src/rom6/kernel/87c7_routine_87c7.asm (recombine MATCH).
 * ORIGIN 0x87C7
 * EXPECT: E800 F072 87D1 4914 6F81 0F18 8912 3091 F495 3482 F492 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: ROLTC rotate-with-carry + BITT T-test (both oracle-unbound)
 * (see src/rom6/kernel/87c7_routine_87c7.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
