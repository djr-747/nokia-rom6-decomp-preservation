/* ROM6 0x5A68 FRAG_5A68 -- 68w banzd triple nest, one EXPECT.
 * Verified encoding: src/rom6/kernel/5a68_frag_5a68.asm (recombine MATCH).
 * ORIGIN 0x5A68
 * EXPECT: F074 059C 7719 09CC 62F8 264C 0072 8810 7716 0003 7715 0005 7714 0000 E741 771A 0012 F072 5A9E E713 60F8 250F 0022 F820 5A86 6FF8 352C 0C42 F073 5A88 F022 2B1C 6DDB 00F8 0013 F130 0003 63F8 000B FFFC 890E F47E 8813 7719 0889 1483 F030 000F 8082 6DF1 02B2 7719 09CC 6DEA 0006 6DEA FF8F 6E8D 5A76 6DEC 0086 6DE8 0072 6E8E 5A72 6DEA 006C FC00
 *
 * Intent: Triple-nested deinterleave with T-seeded nibble positions.
 * Post-RET abut entry after FC00@5A67 (thin: AR2 = store window,
 * T = caller-live for the first inner iteration only, flagged).
 * Runs dark SUB_059C (call); BK = 2508; A = *(0x264C) * 114 (mpy);
 * AR0 = A-low (constant stride base for the run); AR6 = 3, AR5 = 5,
 * AR4 = 0. Outer BANZD over AR6 re-arms AR5 = 5 (banzd 0x5a72;
 * test-then-decrement per op_branch_sind_common: taken = (AR != 0),
 * writeback AR - 1; AR6 = 3 gives four outer passes). Middle BANZD over
 * AR5 re-enters 5A76 (five back-edges = six middle passes per outer).
 * Middle head: AR1 = AR4 (mvmm); BRC = 18 re-arms a 19-iteration RPTB:
 * AR3 = AR1 (mvmm); id 0x250F == 34 loads A = *(0x352C) << 2
 * (LD Smem,SHFT: same word1 convention as ADD Smem SHIFT per
 * op_add_smem_shift, SXM = 1 assumed, flagged) else A = 11036 << 2
 * (LD #lk,SHFT); AR3 += AR0 circular mod BK (mar *ar3+0%: single-subtract
 * wrap, hardware rule); A += *(0x13) (SXM = 1); B = A & 3 (A kept);
 * B = *(0xB) * -4 (mpy Smem,#lk into B, same family as op_mpy_smem_lk);
 * T = B-low; A >>= 2 arithmetic (sfta); AR3 = A-low; BK = 2185;
 * A = *(AR3-address) << T (LD Xmem,TS per op_ld_xmem_shift; T here is
 * the wrapped-negative product above -- effective barrel count
 * trace-confirmable, same HYPOTHESIS class as SUB_5C34);
 * A &= 15 (and #15,a: lk zero-extended); *(AR2-window) = A-low (stl);
 * AR1 += 690 circular mod BK = 2185 (mar *+ar1(0x2b2)%); BK = 2508;
 * AR2-window += 6 (mar *+ar2(0x6)). Loop tail: AR2-window -= 113
 * (mar *+ar2(0xff8f): 16-bit signed offset, standard). BANZD delays
 * always run: middle delays AR4 += 134, AR0 += 114 (mar pair); outer
 * delay AR2-window += 108 (mar); fall-through ends at RET @5AAB.
 * BK/AR0/AR4/AR2-window persist across passes (never re-armed inside);
 * AR3/AR1/T re-derived per pass. Bound 5A68-5AAB.
 */
extern void sub_059C(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void frag_5A68(int *par2, int t_live)
{
    long a;
    long b;
    int t = t_live;
    int ar0;
    int ar1;
    int ar3;
    int ar4 = 0;
    int ar5;
    int ar6 = 3;
    int bk = 2508;
    int *par2w = par2;
    int take;
    int i;

    sub_059C();                                        /* call 0x59c */
    a = (long)*(volatile int *)0x264C * 114L;          /* mpy */
    ar0 = (int)(a & 0xFFFF);                           /* stlm a,ar0 */
    /* stm #3,ar6; stm #5,ar5; stm #0,ar4 (ar5 re-armed per outer) */
    do {                                         /* banzd ar6 outer */
        ar5 = 5;                            /* 5A72: stm #5,ar5 */
        do {                                 /* banzd ar5 middle */
            ar1 = ar4;                          /* 5A76: mvmm ar4,ar1 */
            /* stm #18,brc re-armed below as the 19-count */
            for (i = 0; i < 19; i++) {           /* rptb 0x5a9e */
                ar3 = ar1;                       /* mvmm ar1,ar3 */
                if (*(volatile int *)0x250F == 34)   /* cmpm */
                    a = (long)*(volatile int *)0x352C << 2; /* ld,2 */
                else
                    a = 11036L << 2;             /* ld #11036,2,a */
                ar3 += ar0;                      /* mar *ar3+0% */
                if (ar3 >= bk)
                    ar3 -= bk;
                a += (long)*(volatile int *)0x13; /* add *(0x13),a */
                b = a & 3L;                      /* and #3,a,b */
                b = (long)*(volatile int *)0x0B * -4L; /* mpy -4,b */
                t = (int)(b & 0xFFFF);             /* stlm b,t */
                a >>= 2;                         /* sfta a,-2 */
                ar3 = (int)(a & 0xFFFF);           /* stlm a,ar3 */
                bk = 2185;                       /* stm #2185,bk */
                a = (long)*(volatile int *)ar3 << t; /* ld *ar3,ts,a */
                a &= 15;                         /* and #15,a */
                *par2w = (int)(a & 0xFFFF);        /* stl a,*ar2 */
                ar1 += 690;                      /* mar *+ar1(0x2b2)% */
                if (ar1 >= bk)
                    ar1 -= bk;
                bk = 2508;                       /* stm #2508,bk */
                par2w += 6;                      /* mar *+ar2(0x6) */
            }
            par2w -= 113;            /* mar *+ar2(0xff8f) (-113) */
            ar4 += 134;              /* banzd delay mar *+ar4(0x86) */
            ar0 += 114;              /* banzd delay mar *+ar0(0x72) */
            take = (ar5 != 0);       /* banzd test-then-dec */
            ar5 = (ar5 - 1) & 0xFFFF;
        } while (take);                          /* banzd 0x5a76 */
        par2w += 108;                /* banzd delay mar *+ar2(0x6c) */
        take = (ar6 != 0);           /* banzd test-then-dec */
        ar6 = (ar6 - 1) & 0xFFFF;
    } while (take);                              /* banzd 0x5a72 */
    /* ret @5AAB (T/AR2-live-out noted above) */
}
