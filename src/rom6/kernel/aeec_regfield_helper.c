/* ROM6 0xAEEC AEEC_REGFIELD_HELPER -- 40w (Pool).
 * Verified encoding: src/rom6/kernel/aeec_regfield_helper.asm (recombine MATCH).
 * ORIGIN 0xAEEC
 * EXPECT: 11F8 3490 F330 0007 81F8 0013 00F8 0013 80F8 0013 1195 F310 0002 81F8 001A 7183 0012 F072 AF12 7195 0014 1086 F010 0001 F843 AF13 F845 AF0F 80F8 0011 47F8 0011 E58A F073 AF10 E582 6D96 F495 F495 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS regfie
 * (see src/rom6/kernel/aeec_regfield_helper.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
