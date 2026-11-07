/* ROM6 ORIGIN 0x4F3A (37w): SUB_4F3A -- CRC-style sfta/xor fold, twice.
 * Verified encoding: src/rom6/kernel/4f3a_sub_4f3a.asm (recombine MATCH).
 * EXPECT: F074 059C 7208 2F80 7209 2F81 771A 000F 7711 0001 F120 02BA F072 4F4C F47F F495 F495 FD0C F2C0 7209 2F82 6E89 4F46 771A 0008 F030 03FF 60F8 0008 03FF 7711 0000 FD20 6D91 FE00 7311 2F20
 *
 * Intent: dark call 0x59C. A = (cell 0x2F81 << 16) | cell 0x2F80
 * (mvdm al/ah pair; 32-bit exact in C long, guard unmodeled). B = 698.
 * BRC = 15; rptb 0x4F4C (RSA = 0x4F48, REA = 0x4F4C, inclusive, 16
 * passes): A arith>>= 1 (sfta; C = old bit 0); two nops (C preserved);
 * C set executes A ^= B (xc 1,c over the xor slot, op_xc taken-runs;
 * C clear skips the REA word yet still closes the iteration per the
 * oracle end comparator). A-high = cell 0x2F82 (mvdm); BANZD
 * 0x4F46,*AR1- (AR1 1 -> 0, taken; latch always decrements, taken iff
 * pre-dec nonzero): 2 delay slots run on both paths (standard
 * D-branch; slot count per TI pipeline, flagged since the oracle only
 * stages the delay flag): BRC = 8, A &= 1023 (wipes the reloaded high:
 * dead load under the 2-slot reading, noted). Branch re-runs the rptb
 * (9 passes), reloads A-high, BANZD falls (AR1 0 -> -1, delays run),
 * TC = (cell 0x8 == 1023); AR1 = 0, !TC steps it to 1 (xc 1,ntc over
 * mar, 39A4 precedent); retd with delay cell 0x2F20 = AR1, then return.
 * A/B/C/AR1/BRC all set in-span; AR2/AR3 untouched; T unused;
 * TC recomputed. Bound 4F3A-4F5E (abuts 4F5F).
 */
extern void sub_059C(void);

void sub_4F3A(void)
{
    long a;
    long b;
    int c;
    int tc;
    int ar1;
    int i;

    sub_059C();                                        /* call 0x59c */
    a = ((long)*(volatile int *)0x2F81 << 16)          /* mvdm al/ah */
        | (long)(unsigned)*(volatile int *)0x2F80;
    b = 698L;                                          /* ld #698,b */
    ar1 = 1;                                           /* stm #1,ar1 */
    /* stm #15,brc; rptb 0x4f4c: [0x4f48,0x4f4c], 16 passes */
    for (i = 0; i < 16; i++) {
        c = (a & 1L) != 0;                             /* sfta C = bit 0 */
        a >>= 1;                                       /* sfta a,-1 (arith) */
        /* nop; nop (C preserved) */
        if (c)                                         /* xc 1,c */
            a ^= b;                                    /* xor b,a (shift 0) */
    }
    a = (a & 0xFFFFL) | ((long)*(volatile int *)0x2F82 << 16);
                                                       /* mvdm 0x2f82,ah */
    ar1--;                                             /* banzd (taken) */
    /* delay slot 1: stm #8,brc */
    a &= 1023L;                                        /* delay slot 2 (wipes high, noted) */
    /* branch 0x4f46: rptb again, 9 passes */
    for (i = 0; i < 9; i++) {
        c = (a & 1L) != 0;
        a >>= 1;
        /* nop; nop */
        if (c)
            a ^= b;
    }
    a = (a & 0xFFFFL) | ((long)*(volatile int *)0x2F82 << 16);
                                                       /* mvdm 0x2f82,ah */
    ar1--;                                             /* banzd (not taken) */
    /* delay slot 1: stm #8,brc (BRC dead after) */
    a &= 1023L;                                        /* delay slot 2 */
    /* fallthrough */
    tc = (*(volatile int *)0x8 == 1023);                /* cmpm */
    ar1 = 0;                                           /* stm #0,ar1 */
    if (!tc)                                           /* xc 1,ntc */
        ar1++;                                         /* mar *ar1+ */
    *(volatile int *)0x2F20 = ar1;                     /* retd delay */
    /* retd: return */
}
