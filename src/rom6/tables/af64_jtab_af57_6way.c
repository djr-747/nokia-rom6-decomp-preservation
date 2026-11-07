/* ROM6 0xAF64 JTAB_AF57_6WAY -- 6w.
 * Verified encoding: src/rom6/tables/af64_jtab_af57_6way.asm (recombine MATCH).
 * ORIGIN 0xAF64
 * EXPECT: AF6A AF74 AF79 AF7E AF83 AF88
 *
 * Intent: 6-way jump table consumed by the AF57 BACC dispatch. Every
 * entry is a verified handler head (calld 0xA2B9 lanes, ret exits).
 */
static const unsigned int jtab_af57_6way[6] = {
    0xAF6A, 0xAF74, 0xAF79, 0xAF7E, 0xAF83, 0xAF88
};
