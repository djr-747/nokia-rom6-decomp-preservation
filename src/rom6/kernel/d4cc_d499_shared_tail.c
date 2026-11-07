/* ROM6 0xD4CC D499_SHARED_TAIL -- 2w cell move, one EXPECT.
 * Verified encoding: src/rom6/kernel/d4cc_d499_shared_tail.asm (recombine MATCH).
 * ORIGIN 0xD4CC
 * EXPECT: 7186 0B60
 *
 * Intent: *(0xB60) = *(AR6) (mvdk *ar6,0xb60: dmad-dest move, AR6
 * entry-live). Interior span entered via 0xD45A bc bneq (per .asm
 * header). AR6 rides out unchanged. Bound D4CC-D4CD.
 */
void frag_D4CC(int *par6)
{
    *(volatile int *)0xB60 = *par6;            /* mvdk *ar6,0xb60 */
    /* interior: rejoins the D499 tail exterior */
}
