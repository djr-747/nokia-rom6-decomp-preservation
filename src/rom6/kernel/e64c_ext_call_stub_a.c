/* ROM6 0xE64C E64C_EXT_CALL_STUB_A -- 40w (Pool).
 * Verified encoding: src/rom6/kernel/e64c_ext_call_stub_a.asm (recombine MATCH).
 * ORIGIN 0xE64C
 * EXPECT: F074 05AC 61F8 058F 000F FC20 61F8 058F 0002 F830 E671 F274 2282 7712 000C FC20 61F8 058F F000 F830 E671 7713 27E9 7714 009E 7715 0002 7683 0004 F074 2C88 68F8 058F 0FFF 69F8 058F 1000 F981 AA02 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/e64c_ext_call_stub_a.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
