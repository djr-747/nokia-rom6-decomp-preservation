/* ROM6 0x7067 7067_DIVSQRT_7067 -- 64w (Pool).
 * Verified encoding: src/rom6/kernel/7067_divsqrt_7067.asm (recombine MATCH).
 * ORIGIN 0x7067
 * EXPECT: F074 0598 61F8 051F 0080 F210 03CF F842 7077 F310 0200 F820 7077 FF4A 7713 3EE3 E880 1182 FA4D 7098 770E 0000 4494 1A8C 34F8 0009 F485 F47C EC0F 1E82 F468 F468 770A 0000 FD30 F484 4583 F77C 76F8 000B 0000 F620 F47E F001 4000 76F8 0008 0000 F470 F130 00FF 8960 F768 F495 F495 61F8 0060 0080 F830 70A6 76F8 0060 0080 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/7067_divsqrt_7067.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
