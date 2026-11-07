/* ROM6 0xA8B9 FRAG_A8B9 -- 5w.
 * Verified encoding: src/rom6/kernel/a8b9_frag_a8b9.asm (recombine MATCH).
 * ORIGIN 0xA8B9
 * EXPECT: 7712 2579 E800 EC08 8092
 *
 * Intent: fill 9 DARAM cells at 9593 with 0 (stm + ld #0,a +
 * rpt #8 + stl a,*ar2+).
 */
void frag_a8b9_zero(void)
{
    int i, *p = (int *)9593;              /* stm #9593,ar2 */
    for (i = 0; i < 9; i++)               /* ld #0,a / rpt #8 */
        *p++ = 0;                         /* stl a,*ar2+ */
}
