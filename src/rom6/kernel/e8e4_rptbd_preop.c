/* ROM6 0xE8E4 E8E4_RPTBD_PREOP -- 43w (Pool).
 * Verified encoding: src/rom6/kernel/e8e4_rptbd_preop.asm (recombine MATCH).
 * ORIGIN 0xE8E4
 * EXPECT: 771A 000F F272 E90D 7710 0009 4482 4183 C391 CA18 3D82 C780 8793 2093 288B 3D82 C780 CE91 2C83 3D82 C709 8792 4492 A349 3C8B 8692 8792 3F83 3F93 4083 408B 8693 CA09 2093 2C8B 3D82 C709 D218 2883 3D82 C70D 87DA FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/e8e4_rptbd_preop.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
