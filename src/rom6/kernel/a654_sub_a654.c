/* ROM6 0xA654 A654_SUB_A654 -- 37w (Pool).
 * Verified encoding: src/rom6/kernel/a654_sub_a654.asm (recombine MATCH).
 * ORIGIN 0xA654
 * EXPECT: F074 065C 60F8 2510 00C1 F820 A65E 76F8 09C6 0000 10F8 262D FC45 F110 00A0 F84C A66C 11F8 036D 09F8 250D F310 0002 FC4A E900 F074 4BA8 F274 2282 7712 0009 F930 070C 76F8 262D 0000 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/a654_sub_a654.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
