/* ROM6 0xDBDA DBDA_SUB_DBDA -- 32w (Pool).
 * Verified encoding: src/rom6/kernel/dbda_sub_dbda.asm (recombine MATCH).
 * ORIGIN 0xDBDA
 * EXPECT: E751 F071 0027 8095 8814 7716 1000 771A 0009 EA00 F272 DBF8 770E 0005 E715 F274 DBFA 7717 0001 F48C 0014 8010 F274 DBFA 7717 0000 6DB5 4516 FD47 F784 CAA3 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/dbda_sub_dbda.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
