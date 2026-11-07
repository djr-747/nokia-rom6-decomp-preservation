/* ROM6 0x85FD 85FD_BLOCK_COPY_85FD -- 20w (Pool).
 * Verified encoding: src/rom6/kernel/85fd_block_copy_85fd.asm (recombine MATCH).
 * ORIGIN 0x85FD
 * EXPECT: E742 EC05 7194 30D0 7712 30D0 7713 0005 1092 771A 000F F072 860B F490 F591 6D8C 8184 6C8B 8605 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/85fd_block_copy_85fd.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
