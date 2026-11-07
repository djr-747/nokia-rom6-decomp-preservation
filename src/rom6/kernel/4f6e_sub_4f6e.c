/* ROM6 0x4F6E 4F6E_SUB_4F6E -- 84w (Pool).
 * Verified encoding: src/rom6/kernel/4f6e_sub_4f6e.asm (recombine MATCH).
 * ORIGIN 0x4F6E
 * EXPECT: F074 059C 7712 0457 7714 2F1F 7717 0000 E900 68F8 0473 00FF 7711 001C 7710 01C8 6084 00C0 F820 4F8B 7711 000D 7710 00D3 68F8 0464 0007 F073 4F96 6084 00C1 F820 4F96 7711 0017 7710 017A 68F8 046E 03FF 1292 1C93 F845 4FA1 771A 000F F072 4FA0 F490 07F8 0017 6C89 4F96 8917 6084 0070 7712 0000 FF30 7712 0001 11F8 2628 F330 0010 6084 00B1 7714 247C FF4C 7712 0001 FF30 7712 0000 4817 0084 8094 4810 6E8A 4FB9 0084 8094 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/4f6e_sub_4f6e.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
