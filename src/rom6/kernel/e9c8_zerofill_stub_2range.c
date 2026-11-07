/* ROM6 0xE9C8 E9C8_ZEROFILL_STUB_2RANGE -- 14w (Pool).
 * Verified encoding: src/rom6/kernel/e9c8_zerofill_stub_2range.asm (recombine MATCH).
 * ORIGIN 0xE9C8
 * EXPECT: E800 80F8 294B 7710 297A EC17 8090 7710 241A EC2F 8090 8A09 8A08 F4E6
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * Pool: FBACC computed far jump (oracle-unbound dispatch
 * (see src/rom6/kernel/e9c8_zerofill_stub_2range.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
