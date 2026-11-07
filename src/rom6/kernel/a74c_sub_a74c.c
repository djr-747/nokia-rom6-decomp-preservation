/* ROM6 0xA74C A74C_SUB_A74C -- 84w (Pool).
 * Verified encoding: src/rom6/kernel/a74c_sub_a74c.asm (recombine MATCH).
 * ORIGIN 0xA74C
 * EXPECT: F074 065E 60F8 2510 00C1 FC20 F074 8A08 F074 877D 61F8 051C 0003 F830 A7A0 7712 051C 6182 0100 F820 A76B 6882 FCFF F074 864E 7712 051C 6882 FFF3 6982 0008 F074 8821 10F8 051C F030 0C00 F010 0800 F845 A798 F274 8A54 7712 3196 F074 9DF4 F274 BBEF 7712 3196 F274 9FCF 7716 288C F074 A12B F274 9F42 771A 009F F274 06A2 7712 3196 F274 BADB 7712 3196 61F8 051C 0800 FB20 BAC2 7712 3196 7712 051C 6182 0008 FC20 FE00 6882 FFF3
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/a74c_sub_a74c.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
