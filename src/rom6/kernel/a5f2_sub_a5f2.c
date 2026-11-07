/* ROM6 0xA5F2 A5F2_SUB_A5F2 -- 35w (Pool).
 * Verified encoding: src/rom6/kernel/a5f2_sub_a5f2.asm (recombine MATCH).
 * ORIGIN 0xA5F2
 * EXPECT: 61F8 3EB5 0040 F820 A60A 12F8 3EBC F030 7FFF 08F8 2636 74F8 000B 000C F846 A606 10F8 3ECB F493 F180 F495 75F8 000B 000C 61F8 2628 0200 FC20 7712 2613 F274 ABD2 7713 022B FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/a5f2_sub_a5f2.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
