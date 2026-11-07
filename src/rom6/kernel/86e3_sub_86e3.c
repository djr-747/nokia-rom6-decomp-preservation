/* ROM6 0x86E3 86E3_SUB_86E3 -- 24w (Pool).
 * Verified encoding: src/rom6/kernel/86e3_sub_86e3.asm (recombine MATCH).
 * ORIGIN 0x86E3
 * EXPECT: F074 0590 F6B8 7715 0010 7711 B241 771A 000F 4813 F072 86F5 6F81 0C18 8812 3091 4813 3482 F592 8194 6C8D 86EA F7B8 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: BITT T-test + ROLTC rotate-with-carry (both oracle-unbound)
 * (see src/rom6/kernel/86e3_sub_86e3.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
