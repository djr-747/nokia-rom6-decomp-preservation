/* ROM6 0xD9C9 D9C9_COEF_TABLE_24 -- 24w.
 * Verified encoding: src/rom6/tables/d9c9_coef_table_24.asm (recombine MATCH).
 * ORIGIN 0xD9C9
 * EXPECT: 0568 081D 0D5C 13F4 1A56 1FBA 2687 2B54 31AA 3585 0003 0004 0002 0002 0001 0002 0004 0024 0001 0001 0008 0028 0401 0200
 *
 * Intent: Read-only coefficient table (24 words); loaded by mvpd 0xD9C9 block-moves at D9F7/DA13 into *AR2+ (math routine data).
 */
static const unsigned int d9c9_coef_table_24[24] = {
    0x0568, 0x081D, 0x0D5C, 0x13F4, 0x1A56, 0x1FBA, 0x2687, 0x2B54,
    0x31AA, 0x3585, 0x0003, 0x0004, 0x0002, 0x0002, 0x0001, 0x0002,
    0x0004, 0x0024, 0x0001, 0x0001, 0x0008, 0x0028, 0x0401, 0x0200
};
