/* ROM6 0x436C 436C_ROUTINE_436C -- 24w (Pool).
 * Verified encoding: src/rom6/kernel/436c_routine_436c.asm (recombine MATCH).
 * ORIGIN 0x436C
 * EXPECT: 771A 000F 1282 F072 437E 60F8 0010 03FF F490 6D90 F820 437A 7710 0000 FF0C 7093 0010 07F8 000E 6E8F 436C 6D8A F495 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: ROR rotate + ADDC carry + BANZD loop (rotate/carry oracle-unbound)
 * (see src/rom6/kernel/436c_routine_436c.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
