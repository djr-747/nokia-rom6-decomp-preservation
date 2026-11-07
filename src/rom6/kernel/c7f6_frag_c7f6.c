/* ROM6 0xC7F6 C7F6_FRAG_C7F6 -- 16w (Pool).
 * Verified encoding: src/rom6/kernel/c7f6_frag_c7f6.asm (recombine MATCH).
 * ORIGIN 0xC7F6
 * EXPECT: F495 80D4 1085 F030 00FF 0887 6B87 0001 FA46 283D 7314 054A 7687 0000 F073 283D
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: bit-reversed AR4-advance store (*ar4+%, advance ungrounded)
 * (see src/rom6/kernel/c7f6_frag_c7f6.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
