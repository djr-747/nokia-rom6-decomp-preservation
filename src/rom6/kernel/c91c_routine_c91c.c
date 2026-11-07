/* ROM6 0xC91C C91C_ROUTINE_C91C -- 73w (Pool).
 * Verified encoding: src/rom6/kernel/c91c_routine_c91c.asm (recombine MATCH).
 * ORIGIN 0xC91C
 * EXPECT: E805 4E62 8010 7717 0004 E807 881A 8065 7712 1100 ED00 F162 0027 8364 4A17 8317 F272 C939 E900 E713 E764 E735 E800 4717 B0AB E4D8 8092 F485 6DCF F586 6B64 FFFF 8A17 5662 F61F 5764 811A 6E8F C92A 6D91 4E62 F48E 7712 1100 7713 0CF2 6BF8 000E FFFE 7666 0000 7715 0066 7717 0004 771A 0003 F272 C95F E734 6D93 5692 F48F 5792 F78F 2A85 D53E 83DC 6E8F C955 771A 0003 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS mac kernel.
 * (see src/rom6/kernel/c91c_routine_c91c.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
