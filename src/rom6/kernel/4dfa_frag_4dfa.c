/* ROM6 0x4DFA 4DFA_FRAG_4DFA -- 105w (Pool).
 * Verified encoding: src/rom6/kernel/4dfa_frag_4dfa.asm (recombine MATCH).
 * ORIGIN 0x4DFA
 * EXPECT: 7719 0004 7213 264B 7711 0004 4811 F010 0001 881A E900 61F8 3EB5 0200 F820 4E17 61F8 0586 0002 F820 4E17 7210 261F F495 6DCB 6C80 4E17 6DE8 0004 F272 4E2C 7712 2F00 10D3 61F8 3EB5 0200 F820 4E2B 61F8 0586 0002 F820 4E2B 6C88 4E2B E800 7710 0000 8092 F586 4811 F010 0001 881A 7714 2F21 8184 F272 4E3B 7712 2F00 4482 F074 4348 8092 E800 8A08 F110 0004 F84C 4E63 7714 2F00 7713 2F80 32F8 0016 7717 0003 7715 0005 771A 0012 F072 4E59 4583 F76C F768 F778 F775 F062 0001 F600 3194 8793 6DEC FFED 6C8D 4E4C 6D94 6C8F 4E4A F073 4E8D
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: 40-bit sfta chain (sfta b,12 on 32-bit B overflows 40-bit
 * (see src/rom6/kernel/4dfa_frag_4dfa.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
