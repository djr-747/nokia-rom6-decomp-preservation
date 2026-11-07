/* ROM6 0xDB8C DB8C_EXP_NORM_DB8C -- 53w (Pool).
 * Verified encoding: src/rom6/modem/db8c_exp_norm_db8c.asm (recombine MATCH).
 * ORIGIN 0xDB8C
 * EXPECT: E721 770E 0010 771A 0027 F4B9 F272 DB97 E712 E900 1492 E200 F868 DBA0 6B0E FFFF F273 DB92 771A 0027 8C7A E801 F600 F48E 8C7B F48F 827C F48D F162 3000 F53D 677C 6000 E801 187B 837C F845 DBB8 770E 5A82 227C 827C 6B7B FFFF 770E 287A 227C E910 097A 6F7B 0F3F 890E FE00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: mpyr 0x7c,a x2 (MPY-with-round: no catalog row, no leaf anywhere in the oracle). Secondaries grounded-or-flagged (sqdst/op_sqdst core
 * (see src/rom6/modem/db8c_exp_norm_db8c.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
