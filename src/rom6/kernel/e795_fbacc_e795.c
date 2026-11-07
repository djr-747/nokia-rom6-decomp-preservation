/* ROM6 0xE795 E795_FBACC_E795 -- 8w (Pool).
 * Verified encoding: src/rom6/kernel/e795_fbacc_e795.asm (recombine MATCH).
 * ORIGIN 0xE795
 * EXPECT: F074 05AE F074 2C88 8A09 8A08 F4E6 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: fbacc a (F4E6) with runtime target has no grounded C form (5C4F cala rule). Post-fbacc head
 * (see src/rom6/kernel/e795_fbacc_e795.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
