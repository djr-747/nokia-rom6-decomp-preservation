/* ROM6 0xE46B E46B_SUB39_E46B -- 39w (Pool).
 * Verified encoding: src/rom6/kernel/e46b_sub39_e46b.asm (recombine MATCH).
 * ORIGIN 0xE46B
 * EXPECT: E800 7710 FFFC 7711 0003 8815 7664 0001 7693 0100 8093 E737 928A E489 8093 E734 4815 881A 6DDC F272 E48A E5A9 E5A9 A50A 1294 F46F F48C 3564 56DC 50CC F621 4EDC 5687 928A 6E89 E47A 4E87 A0B8 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: rptbd/banzd delayed forms + stlm have no direct C form (deferred execution, flagged)
 * (see src/rom6/kernel/e46b_sub39_e46b.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
