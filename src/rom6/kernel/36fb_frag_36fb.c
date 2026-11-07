/* ROM6 0x36FB FRAG_36FB -- 51w.
 * Verified encoding: src/rom6/kernel/36fb_frag_36fb.asm (recombine MATCH).
 * ORIGIN 0x36FB
 * EXPECT: F074 05B2 60F8 0008 0005 F820 372E 76F8 058F 0002 71D2 29AA 71D2 29AB 71D2 29B2 71D2 29B3 12F8 29AA 00F8 29AB 80F8 29A9 71D2 29B0 76F8 29B1 0000 10F8 29A9 F010 0001 47F8 0008 71D2 2D34 F074 2E2F 7713 27E9 7714 009E 7715 0002 7683 0008 F074 2C88 F073 2E64
 *
 * Intent: Clause-5 stage with counted store. Runs 0x5B2
 * (dark, extern); TC = (cell 0x8 == 5) (cmpm, oracle: TC =
 * equality); mismatch tail-calls frag_372E with live
 * AR0/AR2 (bc 0x372e,ntc; the callee now has C intent;
 * no AR2 step precedes the branch so entry values pass
 * through) and returns. Else cell 0x58F = 2; four cells
 * (0x29AA/0x29AB/0x29B2/0x29B3) each take *(AR2) with
 * AR2 += AR0 per cell (mvdk +0% source per the 351d
 * convention, wrap flagged); A = unsigned cell 0x29AA +
 * sign-extended cell 0x29AB (ldu then add Smem, SXM = 1
 * flagged; sum < 2^17, long-safe); cell 0x29A9 = A-low;
 * cell 0x29B0 = *(AR2), AR2 += AR0; cell 0x29B1 = 0;
 * A = cell 0x29A9 - 1 (sub lk, dead after, noted); RC+1
 * passes (rpt Smem cell 0x8) of cell 0x2D34 = *(AR2) with
 * AR2 += AR0 per pass; then runs 0x2E2F (extern),
 * AR3 = 10217, AR4 = 158, AR5 = 2 (entry ARs clobbered),
 * cell AR3 = 8, routine_2C88 (dark, extern) and
 * tail-branches to frag_2E64 (extern). ARs/A/B dead at
 * exit (flagged). Bound 36FB-372D. Branch-entered from
 * 36F3 (entry state externally driven, flagged).
 */
extern void sub_05B2(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void frag_372E(int ar0_live, int *ar2_in);
extern void dispatcher_entry_2E2F(void);
extern void routine_2C88(void); /* joins 2c88_ring_report_gate; see docs/evidence/extern-triage.md */
extern void frag_2E64(void); /* joins 2e64_dispatch_match_loop; see docs/evidence/extern-triage.md */

void frag_36FB(int ar0_live, int *ar2_in)
{
    int *ar2 = ar2_in;
    int *ar3;
    long a;
    int rc;
    int i;
    sub_05B2();                                      /* call 0x5b2 */
    if (*(volatile int *)0x8 != 5) {                  /* cmpm; bc ntc */
        frag_372E(ar0_live, ar2);
        return;
    }
    *(volatile int *)0x58F = 2;                       /* st #2,*(0x58f) */
    *(volatile int *)0x29AA = *ar2;                  /* mvdk *ar2+%,imm */
    ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    *(volatile int *)0x29AB = *ar2;
    ar2 += ar0_live;
    *(volatile int *)0x29B2 = *ar2;
    ar2 += ar0_live;
    *(volatile int *)0x29B3 = *ar2;
    ar2 += ar0_live;
    a = (unsigned long)(unsigned)*(volatile int *)0x29AA;  /* ldu */
    a += (long)*(volatile int *)0x29AB;              /* add Smem (SXM flagged) */
    *(volatile int *)0x29A9 = (int)(a & 0xFFFF);     /* stl a */
    *(volatile int *)0x29B0 = *ar2;                  /* mvdk */
    ar2 += ar0_live;
    *(volatile int *)0x29B1 = 0;                     /* st #0 */
    a = (long)*(volatile int *)0x29A9;               /* ld (SXM flagged) */
    a -= 1;                                          /* sub #1,a (dead, noted) */
    rc = *(volatile int *)0x8;                       /* rpt *(0x8) */
    for (i = 0; i < rc + 1; i++) {                   /* mvdk loop */
        *(volatile int *)0x2D34 = *ar2;
        ar2 += ar0_live;                             /* +0% (wrap flagged) */
    }
    dispatcher_entry_2E2F();                                      /* call 0x2e2f */
    ar3 = (int *)10217;                              /* stm #10217,ar3 */
    /* stm #158,ar4; stm #2,ar5 (dead, noted) */
    *ar3 = 8;                                        /* st #8,*ar3 */
    routine_2C88();                                  /* call 0x2c88 */
    frag_2E64();                                      /* b 0x2e64 (tail) */
}
