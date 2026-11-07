/* ROM6 0xE06A E06A_MAC_KERNEL_SHARED -- 56w (Pool).
 * Verified encoding: src/rom6/modem/e06a_mac_kernel_shared.asm (recombine MATCH).
 * ORIGIN 0xE06A
 * EXPECT: E712 E713 F062 8000 7710 FFB2 A59A F272 E07D B39A B39A EC4B B39A B3DE F486 F520 9D3D A50A B39A B39A 1169 0185 8185 4911 0985 8913 8914 826A 406A 6F6B 0C9F A49A EC4C B09A F274 E54B B09A B09A F461 7713 006A 7714 006C 8284 4094 9A6F A51A A496 356F A412 356F 1068 326E FE00 F782 F76F
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: max a (F486 MAX_ACC: catalog row exists but no oracle leaf anywhere). Secondaries grounded-or-flagged (duals/op_mac_dual
 * (see src/rom6/modem/e06a_mac_kernel_shared.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
