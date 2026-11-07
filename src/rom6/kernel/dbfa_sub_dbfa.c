/* ROM6 0xDBFA DBFA_SUB_DBFA -- 30w (Pool).
 * Verified encoding: src/rom6/kernel/dbfa_sub_dbfa.asm (recombine MATCH).
 * ORIGIN 0xDBFA
 * EXPECT: 5682 7683 0000 F130 0001 F4BC F495 FD4C F5BC F163 1000 F84D DC0B FD20 F5BC FD30 F4BC F130 0001 F47F FF30 F04F 8000 6E8F DBFD 1B83 9911 FE00 4E82 941F
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/dbfa_sub_dbfa.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
