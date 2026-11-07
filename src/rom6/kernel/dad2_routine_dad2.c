/* ROM6 0xDAD2 ROUTINE_DAD2 -- 43w fill/compare/store engine.
 * Verified encoding: src/rom6/kernel/dad2_routine_dad2.asm (recombine MATCH).
 * ORIGIN 0xDAD2
 * EXPECT: E810 185A FA45 DADD 7713 0A66 EC04 7093 0ED6 7083 0F0E E820 185A FA45 DAEF 7713 0A66 EC04 7193 0ED6 1083 80F8 0EE7 80F8 0EF4 80F8 0F01 80F8 0F0E 7713 0EDB EC0B 8293 6D93 EC0B 8293 6D93 EC0B 8293 6D93 FE00 EC0B 8293
 *
 * Intent: A = 16 & *(0x5A) (SXM dark, flagged); AR3 = 2662
 * (bcd delay, runs on both lanes); A == 0 skips the fill
 * (bcd aeq to the second and-lane; BCD preserves ... A is
 * recomputed, TC untouched). Fill: 5x *(AR3++) = *(0xED6)
 * (rpt #4 mvkd, dmad source per ab2c finding) then *(AR3) =
 * *(0xF0E). A = 32 & *(0x5A); AR3 = 2662 (bcd delay); A !=
 * 0 runs the compare lane: 5x *(0xED6) = *(AR3++) (mvdk,
 * dmad dest, last wins); A = *(AR3); AL out to cells
 * 0xEE7/0xEF4/0xF01/0xF0E; A == 0 skips it (bcd aeq to the
 * 3803 join). AR3 = 3803; three groups of 12x *(AR3++) =
 * A-high (rpt #11 sth, ASM dark flagged) plus mar *ar3+
 * each; retd delays run pre-return as a single *(AR3++) =
 * A-high (the rpt #11 + sth pair: RPT loads but return
 * fires after the 2 delay words, repeat abandoned);
 * return. A/AR3 computed; out cells/AR3.
 * EXPECT from the image.
 */
void routine_DAD2(void)
{
    long a;
    int *ar3;
    int i;
    int g;

    a = 16;                                                  /* ld #16,a */
    a &= (unsigned int)*(volatile int *)0x5A;                /* and 0x5a,a (zero-extend) */
    ar3 = (int *)2662;                                       /* stm #2662,ar3 (bcd delay) */
    if (a != 0) {                                            /* bcd 0xdadd,aeq */
        for (i = 0; i < 5; i++)                              /* rpt #4 (k+1) */
            *ar3++ = *(volatile int *)0xED6;                 /* mvkd 0xed6,*ar3+ */
        *ar3 = *(volatile int *)0xF0E;                       /* mvkd 0xf0e,*ar3 */
    }
    a = 32;                                                  /* ld #32,a */
    a &= (unsigned int)*(volatile int *)0x5A;                /* and 0x5a,a */
    ar3 = (int *)2662;                                       /* stm #2662,ar3 (bcd delay) */
    if (a != 0) {                                            /* bcd 0xdaef,aeq */
        for (i = 0; i < 5; i++)                              /* rpt #4 */
            *(volatile int *)0xED6 = *ar3++;                 /* mvdk *ar3+,0xed6 (last wins) */
        a = (long)*ar3;                                      /* ld *ar3,a (SXM dark) */
        *(volatile int *)0xEE7 = (int)(a & 0xFFFFL);          /* stl x4 */
        *(volatile int *)0xEF4 = (int)(a & 0xFFFFL);
        *(volatile int *)0xF01 = (int)(a & 0xFFFFL);
        *(volatile int *)0xF0E = (int)(a & 0xFFFFL);
    }
    ar3 = (int *)3803;                                       /* stm #3803,ar3 */
    for (g = 0; g < 3; g++) {
        for (i = 0; i < 12; i++)                             /* rpt #11 (k+1) */
            *ar3++ = (int)((a >> 16) & 0xFFFFL);             /* sth a,*ar3+ (ASM dark) */
        ar3++;                                               /* mar *ar3+ */
    }
    /* retd: delays run, then return */
    *ar3++ = (int)((a >> 16) & 0xFFFFL);                     /* (single sth; repeat abandoned) */
    /* retd */
}
