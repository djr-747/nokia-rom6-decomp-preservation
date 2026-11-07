/* ROM6 0xAE70 AE70_RET_AE70 -- 1w (Pool).
 * Verified encoding: src/rom6/kernel/ae70_ret_ae70.asm (recombine MATCH).
 * ORIGIN 0xAE70
 * EXPECT: FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * gap wave-13).
 * (see src/rom6/kernel/ae70_ret_ae70.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
