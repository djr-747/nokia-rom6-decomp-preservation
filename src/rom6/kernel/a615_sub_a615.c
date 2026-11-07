/* ROM6 0xA615 A615_SUB_A615 -- 36w (Pool).
 * Verified encoding: src/rom6/kernel/a615_sub_a615.asm (recombine MATCH).
 * ORIGIN 0xA615
 * EXPECT: F074 065A 10F8 0565 08F8 0915 F844 A623 10F8 2629 F030 1000 F844 A627 61F8 2628 0100 FC20 E80C 11F8 260E 7711 0CE8 60F8 250F 0022 F820 A633 7711 0DE2 F074 3D79 76F8 022A 0001 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/a615_sub_a615.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
