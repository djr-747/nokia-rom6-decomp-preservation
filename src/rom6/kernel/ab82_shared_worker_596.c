/* ROM6 0xAB82 AB82_SHARED_WORKER_596 -- 80w (Pool).
 * Verified encoding: src/rom6/kernel/ab82_shared_worker_596.asm (recombine MATCH).
 * ORIGIN 0xAB82
 * EXPECT: F074 0596 4A12 7712 0013 60F8 250F 0022 F820 AB9C 60F8 34BF 0004 7712 0027 FF30 7712 003A 60F8 34BF 0000 F495 F495 FF30 7712 0013 7713 2667 F010 0040 F844 ABA8 7712 0017 7713 0080 F310 0040 E800 8A08 7714 000A F310 0126 F844 ABB4 7714 0002 F310 FF40 F84A ABBD E800 74F8 0008 000E F030 3FFF F500 8911 60F8 262C 0040 F830 ABCC 60F8 262C 0050 F830 ABCC 11F8 2611 F073 ABCE 11F8 260E 4814 F074 3D79 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS audio/message shared work
 * (see src/rom6/kernel/ab82_shared_worker_596.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
