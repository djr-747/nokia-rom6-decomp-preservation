/* ROM6 0xDD3A DD3A_CLAMP_SCAN_DD3A -- 51w (Pool).
 * Verified encoding: src/rom6/kernel/dd3a_clamp_scan_dd3a.asm (recombine MATCH).
 * ORIGIN 0xDD3A
 * EXPECT: E903 8362 890E 7712 0EC5 7713 0062 11F8 0ECB FA4C DD6D 7714 0063 E85E 0882 1182 F300 0170 8184 2192 F310 0069 0182 FF43 E510 1184 8184 7715 0EC9 6D8A 1082 F010 0005 1195 7713 0EC7 F486 8083 E809 0093 6F85 0D20 8083 1085 F010 0009 FF4E E535 8083 4484 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/dd3a_clamp_scan_dd3a.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
