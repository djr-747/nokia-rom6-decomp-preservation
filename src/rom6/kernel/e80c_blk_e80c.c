/* ROM6 0xE80C E80C_BLK_E80C -- 43w (Pool).
 * Verified encoding: src/rom6/kernel/e80c_blk_e80c.asm (recombine MATCH).
 * ORIGIN 0xE80C
 * EXPECT: F074 05B0 76F8 244D 0000 76F8 29A7 0000 76F8 29A8 0000 76F8 29A6 2AAF 68F8 058F 0FFF 69F8 058F 1000 76F8 29AF 0000 7712 B780 EC09 7192 2992 68F8 09F0 FFFE 68F8 0B3A FFFE 68F8 0C84 FFFE 68F8 0DCE FFFE F074 05B0 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/e80c_blk_e80c.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
