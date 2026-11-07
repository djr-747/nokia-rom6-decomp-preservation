/* ROM6 0x8775 8775_ROUTINE_8775 -- 8w (Pool).
 * Verified encoding: src/rom6/kernel/8775_routine_8775.asm (recombine MATCH).
 * ORIGIN 0x8775
 * EXPECT: F072 877B F490 E906 F495 FD0C F2C0 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: ROR/ROL rotates (oracle-unbound)
 * (see src/rom6/kernel/8775_routine_8775.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
