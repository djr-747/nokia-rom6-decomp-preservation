/* ROM6 0x3CD2 3CD2_PORT4850_SEQ -- 73w (Pool).
 * Verified encoding: src/rom6/rf/3cd2_port4850_seq.asm (recombine MATCH).
 * ORIGIN 0x3CD2
 * EXPECT: F074 0638 61F8 051F 0080 F820 3CDE 61F8 263B 0004 F073 3CDF F5BC 45F8 3E94 FF20 45F8 3EDC F487 45F8 3E96 7712 3E95 F830 3CEF 45F8 3EDF 7712 3EDD F4BC F520 F84A 3CF5 F5BC 4082 770E 5555 11F8 263B F330 0004 7712 0474 FF4D 7712 049C 45F8 0012 F689 71F8 0009 0012 1082 F030 03FF E900 FD30 E901 F84C 3D13 F120 EFFF F280 F073 3D16 F120 1000 F2A0 F495 75F8 0008 0029 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/rf/3cd2_port4850_seq.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
