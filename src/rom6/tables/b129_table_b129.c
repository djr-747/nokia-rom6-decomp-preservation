/* ROM6 0xB129 TABLE_B129 -- 6w.
 * Verified encoding: src/rom6/tables/b129_table_b129.asm (recombine MATCH).
 * ORIGIN 0xB129
 * EXPECT: B12F B141 B146 B14B B157 B15C
 *
 * Intent: Worker address table (6 code addresses in the B1xx worker region: B12F/B15C heads bound in C, remainder unbound; read-only data, no code).
 */
static const unsigned int table_b129[6] = {
    0xB12F, 0xB141, 0xB146, 0xB14B, 0xB157, 0xB15C
};
