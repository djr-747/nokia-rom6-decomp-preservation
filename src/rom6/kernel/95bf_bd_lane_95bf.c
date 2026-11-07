/* ROM6 0x95BF 95BF_BD_LANE_95BF -- 35w (Pool).
 * Verified encoding: src/rom6/kernel/95bf_bd_lane_95bf.asm (recombine MATCH).
 * ORIGIN 0x95BF
 * EXPECT: F0F8 1184 F1A0 81D4 7314 21FA E803 F273 9667 6882 FF7F F130 FF00 F330 FDFF F310 1C00 F84D 95EA 6982 0080 F030 00FF F130 FFFD F310 001C F84D 95E2 E800 E900 F273 9667 81F8 20FD
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * gap wave-13, dead).
 * (see src/rom6/kernel/95bf_bd_lane_95bf.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
