/* ROM6 0x379F 379F_PORT_LANE_379F -- 33w (Pool).
 * Verified encoding: src/rom6/kernel/379f_port_lane_379f.asm (recombine MATCH).
 * ORIGIN 0x379F
 * EXPECT: 10D2 F030 0001 F7BB 74F8 000B 0002 F845 37C0 76F8 0548 0000 76F8 0549 0001 F330 7FFF F495 75F8 000B 0002 F495 74F8 000B 0037 F340 0010 F495 75F8 000B 0037 F073 37D3
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: ssbx st1,intm has no C form (hardware state). Post-branch head (prev b 2e64)
 * (see src/rom6/kernel/379f_port_lane_379f.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
