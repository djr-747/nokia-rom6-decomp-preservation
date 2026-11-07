/* ROM6 0x9609 9609_FRAG_9609 -- 10w (Pool).
 * Verified encoding: src/rom6/kernel/9609_frag_9609.asm (recombine MATCH).
 * ORIGIN 0x9609
 * EXPECT: 80D4 F000 0002 80F8 20FD E805 F273 9667 7314 21FA
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: bit-reversed AR4-advance store (*ar4+%, advance ungrounded) + delayed branch
 * (see src/rom6/kernel/9609_frag_9609.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
