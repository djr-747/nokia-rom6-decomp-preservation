/* ROM6 0xE532 E532_SUB25_E532 -- 25w (Pool).
 * Verified encoding: src/rom6/kernel/e532_sub25_e532.asm (recombine MATCH).
 * ORIGIN 0xE532
 * EXPECT: ED00 7715 0000 A409 F463 8294 A485 B081 F272 E549 F463 8294 A449 4715 B049 B009 F463 C8BA A485 4715 B085 B081 F463 C8BA FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/e532_sub25_e532.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
