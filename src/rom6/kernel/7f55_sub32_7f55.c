/* ROM6 0x7F55 7F55_SUB32_7F55 -- 31w (Pool).
 * Verified encoding: src/rom6/kernel/7f55_sub32_7f55.asm (recombine MATCH).
 * ORIGIN 0x7F55
 * EXPECT: F074 059E 6DEA 0007 E721 7715 0006 E900 7196 0013 6DB3 1483 F490 F591 818A E900 771A 0007 F072 7F6F 7196 0013 6DB3 1483 F490 F591 F761 6E8D 7F64 F3FF 818A
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS. Head Bound 7F5
 * (see src/rom6/kernel/7f55_sub32_7f55.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
