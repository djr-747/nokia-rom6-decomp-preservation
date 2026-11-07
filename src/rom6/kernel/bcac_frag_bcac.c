/* ROM6 0xBCAC BCAC_FRAG_BCAC -- 14w (Pool).
 * Verified encoding: src/rom6/kernel/bcac_frag_bcac.asm (recombine MATCH).
 * ORIGIN 0xBCAC
 * EXPECT: 4483 F072 BCB8 BCB2 C922 AA0A BC72 C822 D660 F47F F63F C10D CA1C FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: MASR/MACR rounded variants + || parallel pairs (oracle-unbound)
 * (see src/rom6/kernel/bcac_frag_bcac.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
