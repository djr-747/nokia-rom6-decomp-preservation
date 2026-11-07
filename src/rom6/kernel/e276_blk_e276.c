/* ROM6 0xE276 E276_BLK_E276 -- 77w (Pool).
 * Verified encoding: src/rom6/kernel/e276_blk_e276.asm (recombine MATCH).
 * ORIGIN 0xE276
 * EXPECT: EA00 E8EF 881A 8217 7716 2F00 ED00 F272 E282 E762 3093 2291 E498 F4BA E762 2692 ECEE 3892 FA60 E294 E762 E763 ED1E 4492 ECEF C889 F273 E283 6DEF 0004 F000 0001 F48E ED0F F48F 490E 8294 4808 C88A 771A 0009 7715 00EC F272 E2AF 7710 FF13 A498 4715 B098 B09C 890E E763 F48F 8294 4808 C87A 6D90 ED00 FE00 6F17 0E20 771A 0009 F272 E2C1 7662 0001 A598 208A 3562 A458 3562 E689 490B 9B9F FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/e276_blk_e276.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
