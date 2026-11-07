/* ROM6 0xE9D6 ZERO_24 -- 24w.
 * Verified encoding: src/rom6/tables/e9d6_zero_24.asm (recombine MATCH).
 * ORIGIN 0xE9D6
 * EXPECT: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
 *
 * Intent: 24 zero words E9D6-E9ED; padding between fbacc tail (E9D5) and
 * the E9EE paired-word table; no refs, no intent (see asm header).
 */
static const unsigned int zero_24_e9d6[24] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};
