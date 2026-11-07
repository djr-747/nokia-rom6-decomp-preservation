/* ROM6 0x8936 8936_FRAG_8936 -- 32w (Pool).
 * Verified encoding: src/rom6/kernel/8936_frag_8936.asm (recombine MATCH).
 * ORIGIN 0x8936
 * EXPECT: 7712 055A 1082 F110 0005 F84A 89B3 F000 0001 8082 7712 2F3A 7715 0003 7711 10FC F074 89F4 F063 0003 82E2 FFFC 1182 F310 000B E800 6E8D 8946 F586 8192 F073 891C
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/8936_frag_8936.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
