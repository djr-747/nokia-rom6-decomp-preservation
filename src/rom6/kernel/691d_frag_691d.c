/* ROM6 0x691D FRAG_691D -- 11w.
 * Verified encoding: src/rom6/kernel/691d_frag_691d.asm (recombine MATCH).
 * ORIGIN 0x691D
 * EXPECT: F010 0021 880E F495 34E9 0004 F830 6928 FE00 6982 0100
 *
 * Intent: Shifted-bit test with delayed return. A-live-in -= 33 into T (sub plus stlm a,t, T hardware state); bit T of *(AR1-live-in + 4) set runs FRAG_6928 (bitt plus bc 0x6928,tc, C: frag_6928; T in-range assumed, noted per 690e). Else sets bit 8 through live-in AR2 in the retd delay slot (always runs); return. SUB dst = src minus operand per op_sub. Bound 691D-6927.
 */
extern void frag_6928(void);

void frag_691D(int a_live, int *par1, int *par2)
{
    int t = a_live - 33;                         /* sub #33,a; stlm a,t */
    /* nop */
    /* bitt *+ar1(0x4): TC = bit T of cell (T in-range assumed) */
    if (((*(par1 + 4) >> t) & 1) != 0) {          /* bc 0x6928,tc */
        frag_6928();                             /* tail call */
        return;
    }
    *par2 |= 256;                               /* retd delay: orm */
    /* retd */
}
