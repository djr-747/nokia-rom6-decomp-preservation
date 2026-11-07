/* ROM6 0x80F3 80F3_LEAF9_80F3 -- 8w (Pool).
 * Verified encoding: src/rom6/kernel/80f3_leaf9_80f3.asm (recombine MATCH).
 * ORIGIN 0x80F3
 * EXPECT: 1282 771A 000F F072 80F9 F490 F591 8182
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS. Head-fill Bound 80F3-80FA (wave-5: no-exit, falls into 80
 * (see src/rom6/kernel/80f3_leaf9_80f3.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
