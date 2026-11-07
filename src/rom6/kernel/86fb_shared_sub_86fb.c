/* ROM6 0x86FB SHARED_SUB_86FB -- 48w keyed-mix loop with early exit.
 * Verified encoding: src/rom6/kernel/86fb_shared_sub_86fb.asm (recombine MATCH).
 * ORIGIN 0x86FB
 * EXPECT: F074 0590 F6B8 E735 F071 004B 8095 7715 0060 7685 000F 7710 0061 7680 0001 7716 0010 7711 B241 771A 000F 4594 F072 8722 F591 F808 8722 1081 1885 1C85 880E 4813 6F81 0C18 8812 1480 F495 1A82 8082 6D91 6C8E 870E F7B8 6893 1FFF FE00 6883 7FFF
 *
 * Intent: Runs sub_0590 (low-zone, flagged). SXM = 0
 * (rsbx, hardware; SXM-ruled loads/shifts below
 * flagged). AR5 = AR3 entry; A = 0 with 76x
 * *(AR5++) = 0 (rptz a,#75; RPT N + 1). AR5 = 96,
 * *(96) = 15; AR0 = 97, *(97) = 1; AR6 = 16; AR1 =
 * -19903. Outer banz loop (16 passes, test-then-
 * decrement per 2fe8: taken iff pre-dec nonzero,
 * always decrements): BRC = 15; B = *(AR4++) << 16
 * (ld, SXM = 0 zeroext flagged). RPTB 8713-8722
 * (16 passes): B rol-through-C (82d9 idiom, C
 * entry-dark flagged); C clear aborts the repeat to
 * the mar end word (bc nc, dad2 abandon precedent);
 * A = *(AR1) (SXM = 0 zeroext); A &= *(AR5); A ^=
 * *(AR5) (Smem zeroext); T = A-low (stlm); A = AR3
 * register value (ldm); A += *(AR1) >> 8 logical
 * (add -8, SXM = 0 per oracle); AR2 = A-low
 * (stlm); A = *(AR0) << T (ld ts, 82d9 form; T-low
 * 6 bits effective per oracle, counts >= 32
 * unbound flagged); A |= *(AR2); *(AR2) = A-low;
 * AR1++ (mar). SXM = 1 (ssbx, hardware); *(AR3++)
 * &= 8191 (andm); retd delay *(AR3) &= 32767
 * (andm) runs before the return. Out AR1/AR2/AR3/
 * AR5/BRC/T; entry AR3/AR4 caller-live.
 * EXPECT from the image.
 */
extern void sub_0590(void); /* low-zone unsourced, flagged per 87eb */

void shared_sub_86FB(int *ar3_in, int *ar4_in)
{
    long a;
    long b;
    int *ar0;
    int *ar1;
    int *ar2;
    int *ar3 = ar3_in;   /* entry AR3 (caller-live, flagged) */
    int *ar4 = ar4_in;   /* entry AR4 (caller-live, flagged) */
    int *ar5;
    int t;
    int c;   /* live-in (dark, flagged): ROL carry */
    int nc;
    int brc;
    int ar6;
    int i;
    int j;

    sub_0590();                                            /* call 0x590 */
    /* rsbx st1,sxm (SXM = 0, hardware) */
    ar5 = ar3;                                             /* mvmm ar3,ar5 */
    a = 0L;                                                /* rptz a,#75 */
    for (j = 0; j < 76; j++)                               /* RPT N + 1 */
        *ar5++ = (int)(a & 0xFFFFL);                       /* stl a,*ar5+ */
    ar5 = (int *)(long)96;                                 /* stm #96,ar5 */
    *ar5 = 15;                                             /* st #15,*ar5 */
    ar0 = (int *)(long)97;                                 /* stm #97,ar0 */
    *ar0 = 1;                                              /* st #1,*ar0 */
    ar6 = 16;                                              /* stm #16,ar6 */
    ar1 = (int *)(long)-19903;                             /* stm #-19903,ar1 */
    while (ar6-- != 0) {                                   /* banz (test-then-dec) */
        brc = 15;                                          /* stm #15,brc */
        b = (long)((unsigned long)(unsigned)*ar4++ << 16); /* ld *ar4+,16,b */
        for (i = 0; i < brc + 1; i++) {                     /* rptb 0x8722 */
            nc = (int)((b >> 31) & 1L);                    /* rol b */
            b = (long)(((unsigned long)b << 1) | (unsigned long)c);
            c = nc;
            if (c == 0) {                                  /* bc 0x8722,nc */
                ar1++;                                     /* mar (end word runs) */
                break;                                     /* repeat abandoned */
            }
            a = (long)(unsigned)*ar1;                      /* ld *ar1,a (SXM = 0) */
            a &= (long)(unsigned)*ar5;                     /* and *ar5,a */
            a ^= (long)(unsigned)*ar5;                     /* xor *ar5,a */
            t = (int)(a & 0xFFFFL);                        /* stlm a,t */
            a = (long)ar3;                                 /* ldm ar3,a */
            a += (long)((unsigned long)(unsigned)*ar1 >> 8); /* add *ar1,-8,a */
            ar2 = (int *)(long)(a & 0xFFFFL);              /* stlm a,ar2 */
            a = (long)*ar0 << t;                           /* ld *ar0,ts,a */
            a |= (long)(unsigned)*ar2;                     /* or *ar2,a */
            *ar2 = (int)(a & 0xFFFFL);                     /* stl a,*ar2 */
            ar1++;                                         /* mar *ar1+ */
        }
    }
    /* ssbx st1,sxm (SXM = 1, hardware) */
    *ar3 &= 8191;                                          /* andm #8191,*ar3+ */
    ar3++;
    /* retd (delay runs before the return) */
    *ar3 &= 32767;                                         /* delay: andm #32767,*ar3 */
}
