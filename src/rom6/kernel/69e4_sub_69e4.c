/* ROM6 0x69E4 69E4_SUB_69E4 -- 58w (Pool).
 * Verified encoding: src/rom6/kernel/69e4_sub_69e4.asm (recombine MATCH).
 * ORIGIN 0x69E4
 * EXPECT: F074 0598 7712 250F E8F0 1882 F010 0010 FC44 6082 001A FC30 60F8 2614 0000 FC20 60F8 053C 0000 FC20 44F8 050F F161 0002 FC4B 76F8 053C 0002 41F8 0510 7713 2615 7714 0511 FD4D E512 E521 F061 0001 82F8 050F 6FF8 0510 0C2F 11F8 053D FF45 F300 0001 F210 0029 F300 000A FD43 F640 FE00 80F8 053D
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/69e4_sub_69e4.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
