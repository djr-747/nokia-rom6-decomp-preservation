/* ROM6 0x3EC0 3EC0_PORT_SWEEP_3EC0 -- 33w (Pool).
 * Verified encoding: src/rom6/kernel/3ec0_port_sweep_3ec0.asm (recombine MATCH).
 * ORIGIN 0x3EC0
 * EXPECT: F495 F495 75F8 000B 0032 F495 F495 75F8 0008 0004 EC11 F495 71F8 0008 058E 76F8 13D0 0040 61F8 051E 2000 F830 3ED8 F6BB F020 3A98 F495 75F8 0008 000A EC11 F495 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: rsbx st1,intm has no C form (hardware state). Post-portw head
 * (see src/rom6/kernel/3ec0_port_sweep_3ec0.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
