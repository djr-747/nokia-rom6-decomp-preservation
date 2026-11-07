/* ROM6 0x4E63 4E63_FRAG_4E63 -- 51w (Pool).
 * Verified encoding: src/rom6/kernel/4e63_frag_4e63.asm (recombine MATCH).
 * ORIGIN 0x4E63
 * EXPECT: F110 0006 F84C 4E69 7719 0008 F110 0008 F84D 4E96 F110 000A F84B 4E79 7719 0008 7714 2F02 7713 2F06 E5A9 E521 7714 2F00 32F8 0016 771A 01C7 F272 4E8C 7713 2F80 4583 F76C F768 F778 F775 F062 0001 F600 31D4 8793 7712 2F80 7713 0457 F274 4F5F 7711 001C FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: 40-bit sfta chain (sfta b,12 on 32-bit B
 * (see src/rom6/kernel/4e63_frag_4e63.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
