/* ROM6 0x35BB 35BB_XC_LANE_35BB -- 10w (Pool).
 * Verified encoding: src/rom6/kernel/35bb_xc_lane_35bb.asm (recombine MATCH).
 * ORIGIN 0x35BB
 * EXPECT: 10F8 0011 7711 051D 6881 F7DF FF46 6981 0820 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * gap wave-13).
 * (see src/rom6/kernel/35bb_xc_lane_35bb.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
