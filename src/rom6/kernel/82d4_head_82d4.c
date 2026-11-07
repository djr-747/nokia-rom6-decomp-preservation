/* ROM6 0x82D4 82D4_HEAD_82D4 -- 5w (Pool).
 * Verified encoding: src/rom6/kernel/82d4_head_82d4.asm (recombine MATCH).
 * ORIGIN 0x82D4
 * EXPECT: F6BE EA00 6DEA 0007 E721
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: rsbx st1,cpl has no C form (hardware state, 8220/ssbx precedent) -- stays .asm.
 * (see src/rom6/kernel/82d4_head_82d4.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
