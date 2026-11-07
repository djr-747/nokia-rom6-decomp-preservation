/* ROM6 0xD667 D667_SUB_D667 -- 55w (Pool).
 * Verified encoding: src/rom6/kernel/d667_sub_d667.asm (recombine MATCH).
 * ORIGIN 0xD667
 * EXPECT: EA14 6160 0002 F820 D674 7712 0ACE 7714 0B30 F274 DB4A 7713 0AD8 1060 F130 0070 F84D D69E F030 0040 F845 D683 F274 DC18 7715 3143 F073 D692 7713 0B3A 7714 0B44 E809 881A 7715 3143 F272 D691 7716 0C20 E529 E5AB 8296 7714 0C34 EC09 7094 3143 7213 300C F274 E4CB 7712 3143 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS. Bound D667-D69D (wave-5: exit FC00@D69D +
 * (see src/rom6/kernel/d667_sub_d667.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
