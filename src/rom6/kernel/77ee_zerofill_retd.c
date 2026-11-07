/* ROM6 0x77EE 77EE_ZEROFILL_RETD -- 40w (Pool).
 * Verified encoding: src/rom6/kernel/77ee_zerofill_retd.asm (recombine MATCH).
 * ORIGIN 0x77EE
 * EXPECT: F074 059E 60F8 250F 0022 F820 780F 7712 3AD0 F071 0003 8092 7712 3AD8 F071 0003 8092 7712 3AE0 F071 0015 8092 7712 37E0 F071 0015 8092 7712 265D 7182 34BC 7182 34BD 7712 264A 7692 2460 FE00 7682 2458
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/77ee_zerofill_retd.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
