/* ROM6 0x4433 DISPATCH_TABLE_6 -- 6w.
 * Verified encoding: src/rom6/tables/4433_dispatch_table_6.asm (recombine MATCH).
 * ORIGIN 0x4433
 * EXPECT: 4439 4439 4453 4444 446D 4474
 *
 * Intent: Dispatch address table (6 code addresses in the 0x44xx worker region, read-only data, no code).
 */
static const unsigned int dispatch_table_6[6] = {
    0x4439, 0x4439, 0x4453, 0x4444, 0x446D, 0x4474
};
