/* ROM6 0x90B9 90B9_WRAP_90B9 -- 29w (Pool).
 * Verified encoding: src/rom6/kernel/90b9_wrap_90b9.asm (recombine MATCH).
 * ORIGIN 0x90B9
 * EXPECT: F074 0676 F7B7 F074 9118 4A17 7717 3120 7712 0003 771A 0007 F072 90CB 3097 5A85 5FD5 8ED4 8FD3 8D96 6C8A 90C3 6DDC 6DDB 8A17 6C89 90BC F6B7 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: ssbx/rsbx st1,c16 have no C form
 * (see src/rom6/kernel/90b9_wrap_90b9.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
