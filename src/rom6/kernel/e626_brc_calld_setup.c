/* ROM6 0xE626 E626_BRC_CALLD_SETUP -- 38w (Pool).
 * Verified encoding: src/rom6/kernel/e626_brc_calld_setup.asm (recombine MATCH).
 * ORIGIN 0xE626
 * EXPECT: 7713 0A4A 771A 0001 A210 F272 E63A 7711 0000 E724 E735 FF47 E725 E734 A332 F361 0002 E581 A210 FD4B 6D91 10F8 0A43 80F8 0A44 4911 81F8 0A43 F600 F010 0004 7713 0A4B E901 8183 FD43 8383 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/e626_brc_calld_setup.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
