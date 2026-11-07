/* ROM6 0xB1ED B1ED_FRAG_B1ED -- 50w (Pool).
 * Verified encoding: src/rom6/kernel/b1ed_frag_b1ed.asm (recombine MATCH).
 * ORIGIN 0xB1ED
 * EXPECT: F074 B358 F074 A3E1 F074 A2C3 F074 B431 F074 A4D5 F074 B3E2 68F8 3490 FFF0 F074 B3B1 10F8 34BF F845 B21A F010 0004 F845 B210 7712 3490 6882 FFF0 6982 0001 F074 B3B1 F073 B21A 7712 34C5 7182 37DD 7692 0000 7182 34C7 7682 0000 F074 A7B7 F074 A7EB FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/b1ed_frag_b1ed.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
