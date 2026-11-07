/* ROM6 0x66AC FRAG_66AC -- 12w.
 * Verified encoding: src/rom6/kernel/66ac_frag_66ac.asm (recombine MATCH).
 * ORIGIN 0x66AC
 * EXPECT: 1081 7710 2FDC 1180 F487 F110 000E F84B 66B8 E900 F073 66CB
 *
 * Intent: Min gate with two tails. AR0 = 12252 (dead preset, feeds the cell read); A = *AR1-live-in, B = cell 12252, A = min(A,B) (MIN signed per op_compare); B = A - 14, negative tail-enters FRAG_66B8 (bc 0x66b8,blt, C: frag_66B8 with A plus AR0/AR1/AR6/AR5 passthrough). Else B = 0 tail-enters FRAG_66CB (b 0x66cb, C: frag_66CB). SUB dst = src minus operand per op_sub. Bound 66AC-66B7.
 */
extern void frag_66B8(int a_live, int *par0, int *par1, int *par6, int *par5);
extern void frag_66CB(int b_live, int *par5);

void frag_66AC(int *par1, int *par6, int *par5)
{
    int a;
    int b;
    int *ar0 = (int *)12252;                     /* stm #12252,ar0 */
    a = *par1;                                   /* ld *ar1,a */
    b = *ar0;                                    /* ld *ar0,b */
    a = (a < b) ? a : b;                         /* min a (signed) */
    b = a - 14;                                  /* sub #14,a,b */
    if (b < 0) {                                 /* bc 0x66b8,blt */
        frag_66B8(a, ar0, par1, par6, par5);     /* tail call */
        return;
    }
    frag_66CB(0, par5);                          /* ld #0,b; b tail */
}
