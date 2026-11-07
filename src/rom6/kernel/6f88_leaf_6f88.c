/* ROM6 0x6F88 6F88_LEAF_6F88 -- 41w (Pool).
 * Verified encoding: src/rom6/kernel/6f88_leaf_6f88.asm (recombine MATCH).
 * ORIGIN 0x6F88
 * EXPECT: F074 05B4 7714 3E94 61F8 051F 0080 F820 6F9F 11F8 2611 F310 007C F84F 6F9F 11F8 2611 F310 03CF F84A 6F9F 7714 3EDC FD43 E800 4184 770E 1555 FD4E 4484 F48C F462 F001 4000 76F8 0008 0000 770E 0003 F48C FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/6f88_leaf_6f88.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
