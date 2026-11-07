/* ROM6 0xD39E D39E_LEAF_D39E -- 32w (Pool).
 * Verified encoding: src/rom6/kernel/d39e_leaf_d39e.asm (recombine MATCH).
 * ORIGIN 0xD39E
 * EXPECT: 7713 3161 EC04 E589 7713 3161 7717 0002 770E C000 7714 0010 E736 771A 0004 4486 F272 D3B6 F162 E000 F620 9D22 4496 F586 4486 6B84 0001 6E8F D3AA 6DAE 8C86 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS param-loop leaf.
 * (see src/rom6/kernel/d39e_leaf_d39e.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
