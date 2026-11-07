/* ROM6 0x3862 FRAG_3862 -- 23w.
 * Verified encoding: src/rom6/kernel/3862_frag_3862.asm (recombine MATCH).
 * ORIGIN 0x3862
 * EXPECT: 6DF2 FFFD 7713 2F00 4815 F000 0005 F47F F843 386F 47F8 0008 E5C9 7713 2F00 6DED 0006 F274 2C88 7714 008E F073 37DF
 *
 * Intent: Backstep blit gate. AR2 -= 3 circular (wrap needs base+BK,
 * linear modeled flagged); AR3 = 12032; A = AR5-value + 5, halved
 * arithmetic (ldm + SFTA, SXM = 1 assumed flagged); A >= 0 runs
 * RC = *(0x8) + 1 dual moves *(AR3++) = *AR2 with AR2 += AR0-live
 * (rpt Smem + MVDD +0%, 457f precedent; wrap flagged) and re-arms
 * AR3 (bc 0x386f,alt skips exactly the rpt + mvdd, exact); AR5 += 6;
 * AR4 = 142 (calld delay) then dark SUB_2C88; tail-branch FRAG_37DF
 * (void per the 381b/3850 precedent; B clobber risk flagged).
 * AR2/AR5 caller-live (values), dead after. Bound 3862-3878.
 */
extern void sub_2C88(void);
extern void frag_37DF(void);

void frag_3862(int *ar2_in, int ar5_live, int ar0_live)
{
    int *ar2 = ar2_in;
    int *ar3;
    int ar5 = ar5_live;
    long a;
    int rc;
    int i;
    ar2 -= 3;                                        /* mar *+ar2(0xfffd)% (wrap flagged) */
    ar3 = (int *)12032;                              /* stm #12032,ar3 */
    a = (long)ar5 + 5;                               /* ldm ar5,a; add #5,a */
    a = a >> 1;                                      /* sfta a,-1 */
    if (a >= 0) {                                    /* bc 0x386f,alt (skips rpt+mvdd) */
        rc = *(volatile int *)0x8;                   /* rpt *(0x8) */
        for (i = 0; i < rc + 1; i++) {               /* mvdd *ar2+0%,*ar3+ */
            *ar3++ = *ar2;
            ar2 += ar0_live;                         /* +0%: AR2 += AR0 (wrap flagged) */
        }
        ar3 = (int *)12032;                          /* stm #12032,ar3 */
    }
    ar5 += 6;                                        /* mar *+ar5(0x6) */
    /* calld delay: AR4 = 142 */
    sub_2C88();                                      /* calld 0x2c88 (dark) */
    frag_37DF();                                     /* b 0x37df */
    (void)ar5;                                       /* ARs dead at tail (flagged) */
}
