/* ROM6 0x66B8 FRAG_66B8 -- 13w.
 * Verified encoding: src/rom6/kernel/66b8_frag_66b8.asm (recombine MATCH).
 * ORIGIN 0x66B8
 * EXPECT: 1181 0980 F785 F310 0014 0986 F84B 66C5 F100 0006 0186 F073 66CB
 *
 * Intent: Absorb gate with two tails. B = *AR1-live-in - *AR0-live-in, absolute value, - 20, - *AR6-live-in (sub chain plus abs); negative tail-enters FRAG_66C5 (bc 0x66c5,blt, C: frag_66C5). Else B = A-live-in + 6 + *AR6 tail-enters FRAG_66CB (add pair per op_add, C: frag_66CB). A/ARs passed through. Bound 66B8-66C4.
 */
extern void frag_66C5(int *par0, int *par1, int *par6, int *par5);
extern void frag_66CB(int b_live, int *par5);

void frag_66B8(int a_live, int *par0, int *par1, int *par6, int *par5)
{
    int b;
    b = *par1;                                   /* ld *ar1,b */
    b -= *par0;                                  /* sub *ar0,b */
    b = (b < 0) ? -b : b;                        /* abs b */
    b -= 20;                                     /* sub #20,b */
    b -= *par6;                                  /* sub *ar6,b */
    if (b < 0) {                                 /* bc 0x66c5,blt */
        frag_66C5(par0, par1, par6, par5);       /* tail call */
        return;
    }
    b = a_live + 6 + *par6;                     /* add #6,a,b; add *ar6,b */
    frag_66CB(b, par5);                          /* b 0x66cb tail */
}
