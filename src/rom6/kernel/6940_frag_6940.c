/* ROM6 0x6940 FRAG_6940 -- 13w.
 * Verified encoding: src/rom6/kernel/6940_frag_6940.asm (recombine MATCH).
 * ORIGIN 0x6940
 * EXPECT: F110 0020 F84E 694D F010 0011 880E F495 34E9 0002 FC30 F073 6954
 *
 * Intent: Difference gate with bit bail. B = A-live-in - 32, positive tail-enters FRAG_694D (bc 0x694d,bgt: has .asm, no C yet, forward extern). T = A - 17 (sub plus stlm a,t); bit T of *(AR1-live-in + 2) set returns (bitt plus rc tc; T in-range assumed, noted). Else tail-enters FRAG_6954 (b 0x6954, C: frag_6954 this turn). SUB per op_sub. Bound 6940-694C.
 */
extern void frag_694D(void);
extern void frag_6954(void);

void frag_6940(int a_live, int *par1)
{
    int t;
    /* sub #32,a,b (B dead); bc bgt */
    if (a_live - 32 > 0) {
        frag_694D();                             /* tail, unbound C */
        return;
    }
    t = a_live - 17;                             /* sub #17,a; stlm a,t */
    /* nop */
    if (((*(par1 + 2) >> t) & 1) != 0)            /* bitt; rc tc */
        return;
    frag_6954();                                 /* b 0x6954 tail */
}
