/* ROM6 0xDB19 DB19_SUB_DB19 -- 37w (Pool).
 * Verified encoding: src/rom6/kernel/db19_sub_db19.asm (recombine MATCH).
 * ORIGIN 0xDB19
 * EXPECT: 7711 EB3F 771A 005D 4812 6F81 0C18 8813 3091 7710 0000 F272 DB2F 3483 4812 6F81 0C18 8813 FD20 6D90 3091 3483 4812 F495 FD20 6D90 4910 F310 0002 E802 FC4B F310 000E E801 FC4B E800 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/db19_sub_db19.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
