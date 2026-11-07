/* ROM6 0x9F28 9F28_MSG_STAGE_9F28 -- 13w (Pool).
 * Verified encoding: src/rom6/kernel/9f28_msg_stage_9f28.asm (recombine MATCH).
 * ORIGIN 0x9F28
 * EXPECT: 4A12 4A13 7712 1100 7713 093A F274 9F19 771A 008B 8A13 8A12 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * gap orphan
 * (see src/rom6/kernel/9f28_msg_stage_9f28.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
