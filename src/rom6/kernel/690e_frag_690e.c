/* ROM6 0x690E FRAG_690E -- 15w.
 * Verified encoding: src/rom6/kernel/690e_frag_690e.asm (recombine MATCH).
 * ORIGIN 0x690E
 * EXPECT: F110 0020 F84E 691D F010 0011 880E F495 34E9 0003 F830 6928 FE00 6982 0100
 *
 * Intent: T-bit test with delayed return. B = A-live-in - 32, positive tail-enters FRAG_691D (bc 0x691d,bgt: has .asm, no C yet, forward extern). T = A - 17 (stlm a,t, T hardware state, single-bit select); bit T of *(AR1-live-in + 3) set runs FRAG_6928 (bitt plus bc 0x6928,tc, C: frag_6928; T in-range assumed, noted). Else sets bit 8 through live-in AR2 in the retd delay slot (always runs); return. SUB dst = src minus operand per op_sub. Bound 690E-691C.
 */
extern void frag_691D(void);
extern void frag_6928(void);

void frag_690E(int a_live, int *par1, int *par2)
{
    int t;
    /* sub #32,a,b (B dead); bc bgt */
    if (a_live - 32 > 0) {
        frag_691D();                             /* tail, unbound C */
        return;
    }
    t = a_live - 17;                             /* sub #17,a; stlm a,t */
    /* nop */
    /* bitt *+ar1(0x3): TC = bit T of cell (T in-range assumed) */
    if (((*(par1 + 3) >> t) & 1) != 0) {          /* bc 0x6928,tc */
        frag_6928();                             /* tail call */
        return;
    }
    *par2 |= 256;                               /* retd delay: orm */
    /* retd */
}
