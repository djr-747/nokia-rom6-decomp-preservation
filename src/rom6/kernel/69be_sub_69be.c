/* ROM6 0x69BE 69BE_SUB_69BE -- 38w (Pool).
 * Verified encoding: src/rom6/kernel/69be_sub_69be.asm (recombine MATCH).
 * ORIGIN 0x69BE
 * EXPECT: F074 0598 7711 051D 6181 0200 FC20 61F8 058F 000F FC30 60F8 2614 0000 FC20 7712 053C 6082 0000 FC20 7214 2A84 7713 2618 E5A1 6BF8 2A84 0001 6084 FFFF FE20 7682 0004 6881 FDFF FE00 6981 0400
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * gap end)
 * (see src/rom6/kernel/69be_sub_69be.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
