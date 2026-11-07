/* ROM6 0xACBB ACBB_FRAG_ACBB -- 56w (Pool).
 * Verified encoding: src/rom6/kernel/acbb_frag_acbb.asm (recombine MATCH).
 * ORIGIN 0xACBB
 * EXPECT: 7715 AEB3 7712 25F6 61F8 3EC8 0002 F120 0103 F495 FD30 E9C0 771A 0004 F072 ACD6 4815 6D95 8192 7E92 61F8 3EC8 0002 F120 0100 F495 FD30 E9B4 8192 7692 3A98 7712 2602 EC09 7092 3E81 61F8 3EC8 0002 F820 ACF3 7715 3E83 E5B8 E5B8 74F8 0008 000C F040 0010 F495 75F8 0008 000C F073 AE22
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * gap into AE70 filler zone
 * (see src/rom6/kernel/acbb_frag_acbb.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
