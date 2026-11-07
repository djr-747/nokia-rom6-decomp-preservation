/* ROM6 0xDAFD DAFD_SUB_DAFD -- 28w (Pool).
 * Verified encoding: src/rom6/kernel/dafd_sub_dafd.asm (recombine MATCH).
 * ORIGIN 0xDAFD
 * EXPECT: 4A07 F7B8 767A 000F 7711 EB3F 771A 005E 4912 6F81 0F18 F272 DB16 767B 0001 1091 8913 187A 1C7A 880E 4912 6F81 0F18 147B 1A83 8083 8A07 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/dafd_sub_dafd.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
