/* ROM6 0xDFA4 DFA4_SUB_DFA4 -- 43w (Pool).
 * Verified encoding: src/rom6/kernel/dfa4_sub_dfa4.asm (recombine MATCH).
 * ORIGIN 0xDFA4
 * EXPECT: E724 771A 0007 F272 DFAC 6D92 E589 A28A 8293 F120 4000 0984 8183 6DEB FFF7 7715 0068 E754 771A 0009 7712 000C 7695 0733 7695 1862 7695 6E00 F272 DFCD 768D 0D63 A21A FA42 DFCB 318C 4484 A51B 448D 4082 F463 8293 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/dfa4_sub_dfa4.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
