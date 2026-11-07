/* ROM6 0xBFD4 BFD4_FRAG_BFD4 -- 10w (Pool).
 * Verified encoding: src/rom6/kernel/bfd4_frag_bfd4.asm (recombine MATCH).
 * ORIGIN 0xBFD4
 * EXPECT: 3181 0342 8368 2668 920F 2C41 4341 FE00 8382 9C03
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: SQUR square + MAS subtract + STRCD conditional store + ADDS (all oracle-unbound)
 * (see src/rom6/kernel/bfd4_frag_bfd4.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
