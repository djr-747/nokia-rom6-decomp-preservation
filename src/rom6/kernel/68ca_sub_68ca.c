/* ROM6 0x68CA 68CA_SUB_68CA -- 45w (Pool).
 * Verified encoding: src/rom6/kernel/68ca_sub_68ca.asm (recombine MATCH).
 * ORIGIN 0x68CA
 * EXPECT: E900 10F8 0564 F844 68F6 10F8 0565 0886 7712 0915 0882 F846 68F6 10F8 036D 08F8 250D 11F8 0565 FF43 F300 0001 F010 0002 F300 0004 FF42 F300 0001 6F82 0E20 E901 F495 FD43 E900 61F8 054F 0400 10F8 0545 F820 68F6 FD45 E900 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/68ca_sub_68ca.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
