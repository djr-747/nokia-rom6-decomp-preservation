/* ROM6 0x9315 9315_SPAN_TAIL_9315 -- 28w (Pool).
 * Verified encoding: src/rom6/kernel/9315_span_tail_9315.asm (recombine MATCH).
 * ORIGIN 0x9315
 * EXPECT: F074 0594 7714 B405 E800 7710 0000 7711 001F 7213 0060 6D8E F072 932F 30B4 348E F492 F130 000F 8910 6C89 932F 828B 808B 7711 001F 6DAC FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS leaf.
 * (see src/rom6/kernel/9315_span_tail_9315.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
