/* ROM6 0x95EA 95EA_FRAG_95EA -- 9w (Pool).
 * Verified encoding: src/rom6/kernel/95ea_frag_95ea.asm (recombine MATCH).
 * ORIGIN 0x95EA
 * EXPECT: 76F8 20FD FFFF 80D4 E803 F273 9667 7314 21FA
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: bit-reversed AR4-advance store (*ar4+%, advance ungrounded) + delayed branch
 * (see src/rom6/kernel/95ea_frag_95ea.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
