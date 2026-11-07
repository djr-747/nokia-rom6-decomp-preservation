/* ROM6 0x66C5 FRAG_66C5 -- 6w.
 * Verified encoding: src/rom6/kernel/66c5_frag_66c5.asm (recombine MATCH).
 * ORIGIN 0x66C5
 * EXPECT: 1080 1181 F486 F100 0006 0186
 *
 * Intent: Max join with fall-through tail. A = *AR0-live-in, B = *AR1-live-in, A = max(A,B) (MAX signed per op_compare); B = A + 6 + *AR6-live-in; falls into the FRAG_66CB head (abut 66C5+6 = 66CB), modeled as tail call frag_66CB (exact: 66cb body executes next). Bound 66C5-66CA.
 */
extern void frag_66CB(int b_live, int *par5);

void frag_66C5(int *par0, int *par1, int *par6, int *par5)
{
    int a = *par0;                               /* ld *ar0,a */
    int b = *par1;                               /* ld *ar1,b */
    a = (a >= b) ? a : b;                        /* max a (signed) */
    b = a + 6 + *par6;                           /* add #6,a,b; add *ar6,b */
    frag_66CB(b, par5);                          /* fall-through as tail */
}
