/* ROM6 0x4DA7 4DA7_DISPATCH_4DA7 -- 51w (Pool).
 * Verified encoding: src/rom6/rf/4da7_dispatch_4da7.asm (recombine MATCH).
 * ORIGIN 0x4DA7
 * EXPECT: F074 059C 4A08 F0FF F000 B104 8811 7213 264A 1081 60F8 250F 0022 F820 4DD7 60F8 34BF 0000 F830 4DD7 61F8 3490 0002 F830 4DD7 60F8 34BF 0004 11F8 264A FF30 F310 37E0 FF20 F310 3AE0 61F8 3490 0001 F495 F495 FF30 F300 3AE0 FF20 F300 2460 8913 F6E2 7711 0008
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * gap-i
 * (see src/rom6/rf/4da7_dispatch_4da7.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
