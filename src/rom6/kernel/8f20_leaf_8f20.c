/* ROM6 0x8F20 8F20_LEAF_8F20 -- 90w (Pool).
 * Verified encoding: src/rom6/kernel/8f20_leaf_8f20.asm (recombine MATCH).
 * ORIGIN 0x8F20
 * EXPECT: 4543 4321 8343 F020 B3E6 F610 8812 E806 0842 3082 8046 3246 7712 2F27 771A 000C F272 8F39 7621 0004 4582 F682 F48C 4521 F514 8392 EC10 7095 2F23 F071 0027 7308 2F50 F020 B3EE 0043 8812 1046 0820 7182 2F45 8021 3021 1420 8047 F020 2F50 0025 8812 7710 0003 1046 F484 8046 3246 1044 4547 7719 0000 7714 2F47 771A 000C F272 8F68 7713 2F27 9091 F46D F46F 3745 1044 CB2C 7712 1014 EC4F 7092 103C 7713 2F50 771A 0027 F272 8F77 7714 2F7D A09A 8292 ED00 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS bd-target leaf.
 * (see src/rom6/kernel/8f20_leaf_8f20.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
