/* ROM6 0x4FC2 4FC2_SUB_4FC2 -- 52w (Pool).
 * Verified encoding: src/rom6/kernel/4fc2_sub_4fc2.asm (recombine MATCH).
 * ORIGIN 0x4FC2
 * EXPECT: F074 059C 7712 2460 771A 0007 F272 4FCD E800 E900 3982 3C92 F061 0079 F847 4FF2 F060 0079 F48E F495 F48F F78F F78F F48D 7714 2F21 8284 F53D F685 F074 4348 7714 0008 6284 0014 F474 F000 002C E932 F486 E941 F487 7714 2F69 0884 E900 F495 FD43 E901 FE00 81F8 2F1D
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: SQURA/SQUR squares (square family oracle-unbound
 * (see src/rom6/kernel/4fc2_sub_4fc2.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
