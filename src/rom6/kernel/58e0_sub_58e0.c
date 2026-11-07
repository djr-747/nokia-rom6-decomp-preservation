/* ROM6 0x58E0 58E0_SUB_58E0 -- 37w (Pool).
 * Verified encoding: src/rom6/kernel/58e0_sub_58e0.asm (recombine MATCH).
 * ORIGIN 0x58E0
 * EXPECT: F074 05FC 7712 0060 771A 0038 7692 0040 F272 5903 768A 01C8 F55E 8913 F130 0003 F762 890E 0092 32F8 000B E90F 6DB3 F782 F793 6884 000F 1983 0584 8183 6F8A 0D20 6DEC 0002 FD4E F640 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: word 32F8@58F3 (disasm ld *(0xb),asm) matches no ti-c54x catalog row (nearest LD_ASM_SMEM 0x3280/FFE0 composes 32E0, MOD rows 32A0-32D0/FFF8 exclude 32F8)
 * (see src/rom6/kernel/58e0_sub_58e0.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
