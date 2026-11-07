/* ROM6 0x87E9 87E9_ROUTINE_87D3 -- 2w (Pool).
 * Verified encoding: src/rom6/kernel/87e9_routine_87d3.asm (recombine MATCH).
 * ORIGIN 0x87E9
 * EXPECT: F48F F623
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: NORM exponent op + 3-operand SUB (oracle-unbound)
 * (see src/rom6/kernel/87e9_routine_87d3.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
