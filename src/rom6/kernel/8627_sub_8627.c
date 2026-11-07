/* ROM6 0x8627 8627_SUB_8627 -- 19w (Pool).
 * Verified encoding: src/rom6/kernel/8627_sub_8627.asm (recombine MATCH).
 * ORIGIN 0x8627
 * EXPECT: 4593 F793 771A 000F F072 8636 F591 F491 F495 F495 FF0C F065 2049 FF0C F050 7E95 6C8A 8627 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/8627_sub_8627.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
