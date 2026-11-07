/* ROM6 0xDC43 DC43_SUB_DC43 -- 52w (Pool).
 * Verified encoding: src/rom6/kernel/dc43_sub_dc43.asm (recombine MATCH).
 * ORIGIN 0xDC43
 * EXPECT: 7711 0C48 F071 0003 8091 7711 0C57 7691 1000 EC09 8091 7712 0C62 EC09 7092 FB9C 7712 0C6C EC09 7092 FB9C 7712 0C76 EC1D 8092 7712 0C94 EC09 8092 7712 0D42 EC51 8092 7712 0CA2 EC9F 8092 7712 0E34 EC8E 8092 F020 F6B3 7712 0C9E EC03 8092 F074 E5BA F074 D9E1 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/dc43_sub_dc43.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
