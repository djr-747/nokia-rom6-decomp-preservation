/* ROM6 0x35A0 FRAG_35A0 -- 27w.
 * Verified encoding: src/rom6/kernel/35a0_frag_35a0.asm (recombine MATCH).
 * ORIGIN 0x35A0
 * EXPECT: 69F8 054F 0004 E723 10D2 6F82 0D58 F330 00FF 8915 11D2 F330 00FF 8916 F030 0008 7714 2512 FF44 7714 2549 F074 3640 F074 2E2F F073 2E64
 *
 * Intent: Nibble-split into class select. cell0x54F |= 4; AR3 =
 * AR2-value (mvmm); A = unsigned *AR2 with AR2 += AR0-live
 * (ldu +0%, circular wrap needs caller-live BK, linear flagged);
 * B = *AR2 >> 8 arithmetic (LD shift -8 per the 457f precedent)
 * & 255, AR5 = B-low; B = *AR2 (AR2 += AR0), & 255, AR6 = B-low;
 * A &= 8 (imm positive, exact); AR4 = 9490, A-nonzero makes it
 * 9545 (xc 2,aneq covers the 2-word stm only, per ti-c54x op_xc;
 * 688C-class audit). Calls FRAG_3640 with entry-AR0 writeback
 * (C: frag_3640; AR3/AR4 as computed, A as masked; 3640 never
 * returns -- all its paths tail out -- so the trailing dark
 * call + branch are dead, flagged). AR2/AR0 caller-live (AR0
 * doubles as step and 3640 out-param), dead after. Bound 35A0-35BA.
 */
extern void frag_3640(int a_live, int *par3, int *par4, int *par0_out);
extern void dispatcher_entry_2E2F(void);
extern void frag_2E64(void); /* joins 2e64_dispatch_match_loop; see docs/evidence/extern-triage.md */

void frag_35A0(int *ar2_in, int ar0_live, int *par0_out)
{
    int *ar2 = ar2_in;
    int *ar3;
    int *ar4;
    long a;
    long b;
    *(volatile int *)0x54F |= 4;                     /* orm #4,*(0x54f) */
    ar3 = ar2;                                       /* mvmm ar2,ar3 */
    a = (unsigned long)(unsigned)*ar2;               /* ldu *ar2+%,a */
    ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    b = (long)*ar2 >> 8;                             /* ld *ar2,-8,b (arith, flagged) */
    b &= 255;                                        /* and #255,b */
    /* stlm b,ar5 (dead, noted) */
    b = (long)*ar2;                                  /* ld *ar2+%,b */
    ar2 += ar0_live;
    b &= 255;                                        /* and #255,b */
    /* stlm b,ar6 (dead, noted) */
    a &= 8;                                          /* and #8,a */
    ar4 = (int *)9490;                               /* stm #9490,ar4 */
    if (a != 0)                                      /* xc 2,aneq (covers stm only) */
        ar4 = (int *)9545;                           /* stm #9545,ar4 */
    /* call always runs: */
    frag_3640((int)a, ar3, ar4, par0_out);           /* call 0x3640 */
    /* 3640 never returns (flagged): below dead */
    dispatcher_entry_2E2F();                                      /* call 0x2e2f (dark) */
    frag_2E64();                                     /* b 0x2e64 (dark tail) */
}
