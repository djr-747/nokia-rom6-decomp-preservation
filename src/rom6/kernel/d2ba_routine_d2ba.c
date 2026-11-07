/* ROM6 0xD2BA D2BA_ROUTINE_D2BA -- 40w (Pool).
 * Verified encoding: src/rom6/kernel/d2ba_routine_d2ba.asm (recombine MATCH).
 * ORIGIN 0xD2BA
 * EXPECT: F074 070E 4A07 4A13 61F8 0A5A 0001 F920 DAFD E723 EA00 F274 D31D 6DEB 0039 8A13 7717 0010 7711 E9EE 771A 000F F272 D2DA E900 4812 6F81 0C18 8814 3091 4812 3484 F592 8193 6E8F D2D0 771A 000F 8A07 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS 070e-family head.
 * (see src/rom6/kernel/d2ba_routine_d2ba.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
