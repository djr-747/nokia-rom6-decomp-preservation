/* ROM6 0x5825 5825_SUB_5825 -- 97w (Pool).
 * Verified encoding: src/rom6/kernel/5825_sub_5825.asm (recombine MATCH).
 * ORIGIN 0x5825
 * EXPECT: F074 059C 4A10 76F8 2EF5 0000 80F8 0060 F845 5875 60F8 2510 00C0 F820 5852 80F8 2620 E900 7712 261F 8192 819A 819A 7712 264D 10F8 0914 08F8 2EF8 8182 F110 0008 FF45 7682 0002 F010 0011 FF4D 7682 0002 FF45 7682 0002 F073 5875 60F8 2510 00B1 F830 5834 80F8 2620 E900 7712 261E 8192 8192 819A 819A 60F8 250F 0022 F820 586F 11F8 352C 81F8 264C F300 0072 81F8 264D F073 5875 76F8 264C 2B1C 76F8 264D 2B8E 10F8 2F02 7714 DD33 6D94 6084 FFFF 6F94 0D20 F830 5884 F84C 5879 1184 F5E3 8A10 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: cala b@5883 with computed target B = *(AR4-walk) over a runtime-populated key/vector table at 0xDD34+ (even words keys vs A with -1 terminator, odd words vectors
 * (see src/rom6/kernel/5825_sub_5825.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
