/* ROM6 0xE42D E42D_BLK_E42D -- 21w (Pool).
 * Verified encoding: src/rom6/kernel/e42d_blk_e42d.asm (recombine MATCH).
 * ORIGIN 0xE42D
 * EXPECT: E752 F274 E442 E765 E726 6E8F E3C7 826C 826D F073 E43B 4D6C 6C8F E3C7 7213 0063 7214 0062 FE00 EC09 E59A
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: banzd to exterior E3C7 + delay-slot word have no direct C form (flagged). Bound E42D-E441 (post-RET head
 * (see src/rom6/kernel/e42d_blk_e42d.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
