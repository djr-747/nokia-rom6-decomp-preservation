/* ROM6 0xAFB5 TABLE_AFB5 -- 10w.
 * Verified encoding: src/rom6/tables/afb5_table_afb5.asm (recombine MATCH).
 * ORIGIN 0xAFB5
 * EXPECT: AFBF AFD3 AFF9 B017 B04B B050 B062 B080 B0BD B0C2
 *
 * Intent: Read-only data table (10 words, pure .word data, no code).
 */
static const unsigned int table_afb5[10] = {
    0xAFBF, 0xAFD3, 0xAFF9, 0xB017, 0xB04B, 0xB050, 0xB062, 0xB080,
    0xB0BD, 0xB0C2
};
