/* ROM6 0x85AD 85AD_XOR_CHAIN_85AD -- 55w (Pool).
 * Verified encoding: src/rom6/kernel/85ad_xor_chain_85ad.asm (recombine MATCH).
 * ORIGIN 0x85AD
 * EXPECT: 7192 0013 1293 F0C8 1C83 138B F3C8 1D83 F330 FFFF F3E8 F3B0 1D83 F330 FFFF F3E8 F3B0 7192 0013 1D93 1C83 F0E8 1C8B F0F8 7192 0013 1D83 F3E8 1D93 F3F8 F330 FFFF F3E8 F3B0 1D83 F330 FFFF F3E8 F3B0 1C8B F030 FFFF F0E8 F0B0 1C93 1C83 F030 FFFF F0E8 F0B0 7182 0013 8093 8183 FC00
 *
 * Intent: Pool -- C intent deferred per the asm span's own documented blocker:
 * HYPOTHESIS.
 * (see src/rom6/kernel/85ad_xor_chain_85ad.asm header for the full evidence record). No C entry is claimed;
 * the span stays owned by its verified .asm encoding.
 */
