/* ROM6 0x7FDC 7FDC_ROUTINE_7FDC -- 24w (Pool).
 * Verified encoding: src/rom6/kernel/7fdc_routine_7fdc.asm (recombine MATCH).
 * ORIGIN 0x7FDC
 * EXPECT: F074 059E 7719 0002 7714 0060 7715 0061 F274 7EA7 771A 001F F072 7FED 4485 F491 82D5 F591 6E89 7FE4 838B 818B 6D93 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: ROL rotates + BANZD loop (rotate family oracle-unbound)
 * (see src/rom6/kernel/7fdc_routine_7fdc.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
