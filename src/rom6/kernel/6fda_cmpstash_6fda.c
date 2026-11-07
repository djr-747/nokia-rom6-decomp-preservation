/* ROM6 0x6FDA 6FDA_CMPSTASH_6FDA -- 32w (Pool).
 * Verified encoding: src/rom6/kernel/6fda_cmpstash_6fda.asm (recombine MATCH).
 * ORIGIN 0x6FDA
 * EXPECT: F074 05B4 60F8 250F 0022 F820 6FE4 F074 712D FC20 E800 7214 245E 7712 245E E5A1 7208 265C F000 25A1 08F8 0014 FA46 6FF6 4814 F495 F020 25A1 8082 0983 FC4B FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/6fda_cmpstash_6fda.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
