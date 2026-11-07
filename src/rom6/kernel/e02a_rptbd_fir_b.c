/* ROM6 0xE02A E02A_RPTBD_FIR_B -- 31w (Pool).
 * Verified encoding: src/rom6/kernel/e02a_rptbd_fir_b.asm (recombine MATCH).
 * ORIGIN 0xE02A
 * EXPECT: F272 E047 1182 F495 B285 B085 B085 B085 B085 B085 B085 B085 B085 B085 B009 F463 8294 B249 B049 B049 B049 B049 B049 B049 B049 B049 B049 B009 F463 8294 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/e02a_rptbd_fir_b.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
