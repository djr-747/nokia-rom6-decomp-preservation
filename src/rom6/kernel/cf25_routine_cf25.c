/* ROM6 0xCF25 CF25_ROUTINE_CF25 -- 38w (Pool).
 * Verified encoding: src/rom6/kernel/cf25_routine_cf25.asm (recombine MATCH).
 * ORIGIN 0xCF25
 * EXPECT: EA00 7719 0000 4A07 7707 0740 F074 0680 7711 0D42 7713 FCA9 F274 E276 7714 110A 80F8 0ED0 7712 FE89 F274 E2B4 7713 110C F274 E2C3 7711 0F31 7663 0F92 7662 0F7E F274 E395 7611 0F31 8A07 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS ea00-family leaf.
 * (see src/rom6/kernel/cf25_routine_cf25.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
