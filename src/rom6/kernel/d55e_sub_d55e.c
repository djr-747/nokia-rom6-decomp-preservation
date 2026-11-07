/* ROM6 0xD55E D55E_SUB_D55E -- 19w (Pool).
 * Verified encoding: src/rom6/kernel/d55e_sub_d55e.asm (recombine MATCH).
 * ORIGIN 0xD55E
 * EXPECT: 771A 0026 E723 F272 D568 108A 8004 218A F630 808B 1083 7712 0B66 2182 F630 8083 FE00 7082 3004
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/d55e_sub_d55e.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
