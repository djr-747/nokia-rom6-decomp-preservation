/* ROM6 0xBCBA BCBA_FRAG_BCBA -- 14w (Pool).
 * Verified encoding: src/rom6/kernel/bcba_frag_bcba.asm (recombine MATCH).
 * ORIGIN 0xBCBA
 * EXPECT: 770E 3433 F272 BCC6 4483 2E84 C822 2A84 950F F53F F600 C8FC DE2D FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/bcba_frag_bcba.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
