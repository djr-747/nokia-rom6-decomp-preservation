/* ROM6 0x4384 4384_DIV_CORE_4384 -- 54w (Pool).
 * Verified encoding: src/rom6/kernel/4384_div_core_4384.asm (recombine MATCH).
 * ORIGIN 0x4384
 * EXPECT: F074 0606 4B84 4A17 6F84 0D20 F84B 43B6 F48E 1184 8C82 F58E 7717 0060 490E 0982 8182 891A 890E 1184 F78F 4F87 7684 0001 F540 F072 43A7 5487 F843 43A6 F273 43A7 F461 1A84 F661 F540 4E87 480E 881A E800 F072 43AF F0E1 1A84 F180 5687 4782 F0FF F073 43B7 E900 8A17 8B84 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS divide core.
 * (see src/rom6/kernel/4384_div_core_4384.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
