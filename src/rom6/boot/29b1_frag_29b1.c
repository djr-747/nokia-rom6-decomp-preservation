/* ROM6 0x29B1 FRAG_29B1 -- 8w.
 * Verified encoding: src/rom6/boot/29b1_frag_29b1.asm (recombine MATCH).
 * ORIGIN 0x29B1
 * EXPECT: 7683 0002 7713 1274 7712 126E F073 2A8A
 *
 * Intent: Preset plus join. Stores 2 through live-in AR3, presets AR3 = 4724 and AR2 = 4718 (dead after, noted), tail-enters FRAG_2A73 span 2 at 0x2A8A (b: has .asm, no C yet, forward extern). Bound 29B1-29B8.
 */
extern void frag_2A73(void);

void frag_29B1(int *par3)
{
    *par3 = 2;                                   /* st #2,*ar3 */
    /* stm #4724,ar3; stm #4718,ar2 (dead presets) */
    frag_2A73();                                 /* b 0x2a8a tail */
}
