/* ROM6 0x965F 965F_FRAG_965F -- 8w (Pool).
 * Verified encoding: src/rom6/kernel/965f_frag_965f.asm (recombine MATCH).
 * ORIGIN 0x965F
 * EXPECT: F0F8 1A84 80D4 E806 F273 9667 7314 21FA
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: bit-reversed AR4-advance store (*ar4+%, advance ungrounded) + delayed branch
 * (see src/rom6/kernel/965f_frag_965f.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
