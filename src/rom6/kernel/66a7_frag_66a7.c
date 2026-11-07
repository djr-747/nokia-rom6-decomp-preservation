/* ROM6 0x66A7 FRAG_66A7 -- 5w.
 * Verified encoding: src/rom6/kernel/66a7_frag_66a7.asm (recombine MATCH).
 * ORIGIN 0x66A7
 * EXPECT: F100 0012 0186 F073 66CB
 *
 * Intent: Sum handoff. B = A-live-in + 18 (add #18,a,b) + *AR6-live-in (add *ar6,b per op_add); tail-enters FRAG_66CB with B live (b 0x66cb: has .asm, no C yet, forward extern with B arg per 388c precedent). Bound 66A7-66AB.
 */
extern void frag_66CB(int b_live);

void frag_66A7(int a_live, int *par6)
{
    int b = a_live + 18;                         /* add #18,a,b */
    b += *par6;                                  /* add *ar6,b */
    frag_66CB(b);                                /* b 0x66cb tail */
}
