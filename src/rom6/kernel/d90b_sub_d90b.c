/* ROM6 0xD90B D90B_SUB_D90B -- 84w (Pool).
 * Verified encoding: src/rom6/kernel/d90b_sub_d90b.asm (recombine MATCH).
 * ORIGIN 0xD90B
 * EXPECT: 7719 0000 F074 0684 4A07 7707 0740 EA16 FA44 D91F 6868 FFFD 6168 0001 F820 D91F F274 D95F 771A 0011 EA16 E803 1868 F010 0003 F844 D92E EA60 7212 300A E808 F273 D949 EC9F 8092 EA60 7711 3043 F274 D798 7713 3017 EA60 7215 300A F274 D5D6 7613 3017 EA60 7212 300A 771A 009F F272 D948 F162 FFF8 4482 F461 F280 8292 EA16 6168 0001 F830 D957 7712 3043 1092 F844 D957 F274 D95F 771A 0038 E802 1868 6868 FFFE F944 D970 8A07 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/d90b_sub_d90b.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
