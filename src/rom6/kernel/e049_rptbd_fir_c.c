/* ROM6 0xE049 E049_RPTBD_FIR_C -- 33w (Pool).
 * Verified encoding: src/rom6/kernel/e049_rptbd_fir_c.asm (recombine MATCH).
 * ORIGIN 0xE049
 * EXPECT: E746 E725 F272 E068 1192 6D8C B239 B886 B886 B886 B886 B886 B886 B886 B886 B886 B80A F463 8296 B239 B84A B84A B84A B84A B84A B84A B84A B84A B84A B80A F463 8296 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/e049_rptbd_fir_c.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
