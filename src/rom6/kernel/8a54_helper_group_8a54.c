/* ROM6 0x8A54 8A54_HELPER_GROUP_8A54 -- 81w (Pool).
 * Verified encoding: src/rom6/kernel/8a54_helper_group_8a54.asm (recombine MATCH).
 * ORIGIN 0x8A54
 * EXPECT: F074 0612 4A07 4A12 F6BE F7B9 F7B6 ED00 EA5E 766F 0001 766E FFF9 7714 2F70 7715 3098 7717 0003 4A14 F074 8AA5 8A14 F074 8B03 6E8F 8A67 6DED 0011 7715 3090 7713 B3BE 7714 B3C6 4594 771A 0007 F272 8A84 7712 B3CE A039 F46A F621 E900 3792 F700 CBAB F074 8B30 7712 2F71 7715 110A E723 771A 009F 4492 F272 8A96 770E 6E14 2A85 8285 F400 C889 8A13 7712 2F71 4492 771A 009F F272 8AA2 F162 FFF8 F280 C889 8A07 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS helper group.
 * (see src/rom6/kernel/8a54_helper_group_8a54.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
