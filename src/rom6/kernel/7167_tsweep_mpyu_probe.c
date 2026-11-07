/* ROM6 0x7167 7167_TSWEEP_MPYU_PROBE -- 60w (Pool).
 * Verified encoding: src/rom6/kernel/7167_tsweep_mpyu_probe.asm (recombine MATCH).
 * ORIGIN 0x7167
 * EXPECT: F074 05B4 E900 770E 0021 248B F462 4093 FC42 F300 0001 770E 0042 248B F462 4093 FC42 F300 0001 770E 0083 248B F462 4093 FC42 F300 0001 770E 0106 248B F462 4093 FC42 F300 0001 770E 020C 248B F462 4093 FC42 F300 0001 770E 0419 248B F462 4093 FC42 F300 0001 770E 0831 248B F462 4093 FC42 F300 0001 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/7167_tsweep_mpyu_probe.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
