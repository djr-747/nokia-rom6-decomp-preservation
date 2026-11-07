/* ROM6 0x90D6 90D6_WRAP_90D6 -- 17w (Pool).
 * Verified encoding: src/rom6/kernel/90d6_wrap_90d6.asm (recombine MATCH).
 * ORIGIN 0x90D6
 * EXPECT: F074 0676 F6BE EA00 F7B7 F074 9118 F074 90F8 1061 FA46 90DB 6B61 FFFF F6B7 F7BE FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: ssbx/rsbx st1,c16/cpl have no C form
 * (see src/rom6/kernel/90d6_wrap_90d6.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
