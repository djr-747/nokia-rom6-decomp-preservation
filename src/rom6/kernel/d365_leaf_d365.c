/* ROM6 0xD365 D365_LEAF_D365 -- 57w (Pool).
 * Verified encoding: src/rom6/kernel/d365_leaf_d365.asm (recombine MATCH).
 * ORIGIN 0xD365
 * EXPECT: 7313 300D E805 EC27 8293 880E 8204 7605 0001 7606 0002 7608 000D 771A 0004 F272 D39C 7609 0007 1192 1009 F280 8814 F75D 1905 20E4 FC2C F47F 0004 8007 000D 8813 10E2 0004 1809 8814 F020 1000 FD4C F484 8083 20E4 FC2C F47F 0004 6F07 0D20 000D 8814 1083 FD4B F484 0084 8084 6B04 0001 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS mpy-loop leaf.
 * (see src/rom6/kernel/d365_leaf_d365.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
