/* ROM6 0x43BA 43BA_ROUTINE_43BA -- 19w (Pool).
 * Verified encoding: src/rom6/kernel/43ba_routine_43ba.asm (recombine MATCH).
 * ORIGIN 0x43BA
 * EXPECT: F074 0594 6F82 0C58 F030 00FF 71D2 2F00 F110 001D F84E 43CD F000 B0DE 8811 F495 F495 1081 F4E2
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: BACC computed jump exit (oracle-unbound dispatch) + circular MVKD
 * (see src/rom6/kernel/43ba_routine_43ba.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
