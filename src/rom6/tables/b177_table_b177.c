/* ROM6 0xB177 TABLE_B177 -- 6w.
 * Verified encoding: src/rom6/tables/b177_table_b177.asm (recombine MATCH).
 * ORIGIN 0xB177
 * EXPECT: B17D B1ED B21F B26E B308 B346
 *
 * Intent: Worker address table (6 code addresses from B17D to B346 in the audio/worker region; read-only data, no code).
 */
static const unsigned int table_b177[6] = {
    0xB17D, 0xB1ED, 0xB21F, 0xB26E, 0xB308, 0xB346
};
