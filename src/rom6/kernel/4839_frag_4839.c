/* ROM6 0x4839 4839_FRAG_4839 -- 31w (Pool).
 * Verified encoding: src/rom6/kernel/4839_frag_4839.asm (recombine MATCH).
 * ORIGIN 0x4839
 * EXPECT: F074 059E 7712 0160 7711 0006 1194 771A 000F F072 4849 F590 F808 4849 6A82 000F 6D92 6C89 483F 1184 771A 0001 F072 4856 F590 F808 4856 6A82 000F 6D92 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: ROR-through-carry (rotate count rides the unbound carry flag -- no oracle form
 * (see src/rom6/kernel/4839_frag_4839.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
