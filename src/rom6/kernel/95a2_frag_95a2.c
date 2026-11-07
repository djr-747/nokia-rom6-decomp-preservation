/* ROM6 0x95A2 95A2_FRAG_95A2 -- 8w (Pool).
 * Verified encoding: src/rom6/kernel/95a2_frag_95a2.asm (recombine MATCH).
 * ORIGIN 0x95A2
 * EXPECT: F000 B406 8811 7214 21FA 1181 4813 F5E2
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: BACC computed jump (target = B, oracle-unbound dispatch)
 * (see src/rom6/kernel/95a2_frag_95a2.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
