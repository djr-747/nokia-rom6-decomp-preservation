/* ROM6 0xD29E D29E_LEAF_D29E -- 28w (Pool).
 * Verified encoding: src/rom6/kernel/d29e_leaf_d29e.asm (recombine MATCH).
 * ORIGIN 0xD29E
 * EXPECT: 4A07 7707 0740 F074 0682 EA14 105A F030 0001 FB45 DAD2 7712 0ED6 EA00 7712 0ED6 F274 D2BA 7713 2579 10F8 0C4C F030 0002 F944 DC43 8A07 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS trampoline leaf.
 * (see src/rom6/kernel/d29e_leaf_d29e.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
