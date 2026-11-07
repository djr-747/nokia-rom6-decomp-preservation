/* ROM6 0x9A37 9A37_FRAG_9A37 -- 25w (Pool).
 * Verified encoding: src/rom6/kernel/9a37_frag_9a37.asm (recombine MATCH).
 * ORIGIN 0x9A37
 * EXPECT: 881A 9418 F063 00FF F072 9A41 1A92 6FD3 0C98 F0E8 F0E8 F3FF F808 9A4C F7BB 68F8 20FF EFFF F6EB 7313 21FC 6DC3 FE00 7313 21FC
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: RPTB loop grows A <<=16 per pass with BRC = entry-A-low (unbound) -- 40-bit accumulator growth has no exact 32-bit long form
 * (see src/rom6/kernel/9a37_frag_9a37.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
