/* ROM6 0x2BA1 2BA1_PA1_PA56_HANDSHAKE -- 9w (Pool).
 * Verified encoding: src/rom6/boot/2ba1_pa1_pa56_handshake.asm (recombine MATCH).
 * ORIGIN 0x2BA1
 * EXPECT: 7682 4000 F495 7582 0001 EC0D F495 F073 283D
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * gap 2BA3-2BA9 owned
 * (see src/rom6/boot/2ba1_pa1_pa56_handshake.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
