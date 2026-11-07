/* ROM6 0xDA21 FRAG_DA21 -- 17w.
 * Verified encoding: src/rom6/kernel/da21_frag_da21.asm (recombine MATCH).
 * ORIGIN 0xDA21
 * EXPECT: 7658 0007 4458 F844 DA35 8059 E804 185A F845 DA32 765A 0018 765C 7081 FE00 765D 6958
 *
 * Intent: Cell-0x58 preset gate. Cell = 7; A = cell << 16 (nonzero,
 * so the bc aneq to FRAG_DA35 is always taken -- the words below are
 * dead but modeled for completeness, flagged): cell0x59 = A-low
 * (= 0); A = 4 AND cell0x5A (da40 pattern); zero tail-enters
 * FRAG_DA32, else cell0x5A = 24, cell0x5C = 28801; the retd delay
 * cell0x5D = 26968 always runs; return. Cells absolute per the da40
 * precedent (DP = 0 assumed, flagged). Bound DA21-DA31.
 */
extern void frag_DA35(void);
extern void frag_DA32(void);

void frag_DA21(void)
{
    long a;
    *(volatile int *)0x58 = 7;                       /* st #7,0x58 */
    a = (long)*(volatile int *)0x58 << 16;           /* ld 0x58,16,a */
    if (a != 0) {                                    /* bc 0xda35,aneq (always taken) */
        frag_DA35();
        return;
    }
    /* Dead below (flagged): cell holds 7 */
    *(volatile int *)0x59 = (int)(a & 0xFFFF);       /* stl a,0x59 (= 0) */
    a = 4 & (unsigned short)*(volatile int *)0x5A;   /* ld #4,a; and 0x5a,a */
    if (a == 0) {                                    /* bc 0xda32,aeq */
        frag_DA32();
        return;
    }
    *(volatile int *)0x5A = 24;                      /* st #24,0x5a */
    *(volatile int *)0x5C = 28801;                   /* st #28801,0x5c */
    *(volatile int *)0x5D = 26968;                   /* retd delay: st (always runs) */
    /* retd */
}
