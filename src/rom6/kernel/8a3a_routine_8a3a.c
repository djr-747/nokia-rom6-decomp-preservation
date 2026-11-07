/* ROM6 0x8A3A 8A3A_ROUTINE_8A3A -- 11w (Pool).
 * Verified encoding: src/rom6/kernel/8a3a_routine_8a3a.asm (recombine MATCH).
 * ORIGIN 0x8A3A
 * EXPECT: 771A 001D F272 8A41 F0FF 0783 F0FF 0783 FE00 F0FF 0783
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: interior ADDC-with-carry + RPTBD (both oracle-unbound)
 * (see src/rom6/kernel/8a3a_routine_8a3a.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
