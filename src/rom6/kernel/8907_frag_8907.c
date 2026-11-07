/* ROM6 0x8907 FRAG_8907 -- 21w.
 * Verified encoding: src/rom6/kernel/8907_frag_8907.asm (recombine MATCH).
 * ORIGIN 0x8907
 * EXPECT: 61F8 0577 8000 771A 0003 E902 FD20 E903 F272 8915 7712 2F32 1082 F487 8092 6184 0001 F830 8936 6984 0001
 *
 * Intent: Min-reduce with flag tail. TC = (cell0x577 & 0x8000) != 0
 * (bitf, 32b4 precedent); B = 2, TC clear makes B = 3 (xc 1,ntc:
 * taken executes, per ti-c54x op_xc); AR2 = 12082 (rptbd delay,
 * once); 4 passes of A = *AR2, B = min(B,A) (MIN single writes B
 * per the 6657 comment; commutative, exact), *(AR2++) = A-low
 * (same-value stores, executed); A/B dead after (flagged). TC =
 * (*AR4 & 1) != 0; set tail-enters dark 0x8936 (bc; entry unbound,
 * flagged), else *AR4 |= 1 and falls through (no binding yet,
 * flagged). RPTBD block [RSA = PC + 4 = 0x8913, REA = 0x8915];
 * execution stays deferred, flagged. Bound 8907-891B.
 */
extern void frag_8936(void);

void frag_8907(int *ar4)
{
    int tc;
    long a;
    long b;
    int i;
    int *ar2;
    tc = (*(volatile int *)0x577 & 0x8000) != 0;      /* bitf *(0x577),#-32768 */
    b = 2;                                            /* ld #2,b */
    if (!tc)                                          /* xc 1,ntc (taken runs ld) */
        b = 3;                                       /* ld #3,b */
    ar2 = (int *)12082;                               /* rptbd delay: stm (once) */
    for (i = 0; i < 4; i++) {                         /* stm #3,brc; rptbd 0x8915 */
        a = (long)*ar2;                               /* ld *ar2,a */
        if (a < b)                                    /* min a (B = min) */
            b = a;
        *ar2++ = (int)(a & 0xFFFF);                   /* stl a,*ar2+ */
    }
    (void)a;                                          /* A/B dead after (flagged) */
    (void)b;
    tc = (*ar4 & 1) != 0;                             /* bitf *ar4,#1 */
    if (tc) {                                         /* bc 0x8936,tc */
        frag_8936();
        return;
    }
    *ar4 |= 1;                                        /* orm #1,*ar4 */
    /* fall-through to 0x891c (no binding yet, flagged) */
}
