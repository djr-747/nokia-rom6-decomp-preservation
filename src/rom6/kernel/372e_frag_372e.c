/* ROM6 0x372E FRAG_372E -- 37w.
 * Verified encoding: src/rom6/kernel/372e_frag_372e.asm (recombine MATCH).
 * ORIGIN 0x372E
 * EXPECT: 60F8 0008 0006 F820 3753 71D2 27FE 71D2 27FF 71D2 2940 71D2 2941 71D2 2979 71D2 244F 71D2 2450 F074 2E2F F074 E79D F074 E80C 7713 27E9 7714 009E 7715 0002 7683 0008 F074 2C88 F073 2E64
 *
 * Intent: Clause-6 stage with epilogue chain. TC =
 * (cell 0x8 == 6) (cmpm, oracle: TC = equality); mismatch
 * tail-calls frag_3753 (bc 0x3753,ntc; the callee now has
 * C intent, parameterless) and returns. Else seven cells
 * (0x27FE/0x27FF/0x2940/0x2941/0x2979/0x244F/0x2450) each
 * take *(AR2) with AR2 += AR0 per cell (mvdk +0% source
 * per the 351d convention: read pre-step address, step by
 * AR0; circular wrap needs caller-live BK, linear modeled
 * flagged); then runs 0x2E2F, 0xE79D (dark stub, extern)
 * and 0xE80C (dark block, extern); AR3 = 10217, AR4 =
 * 158, AR5 = 2 (entry ARs clobbered); cell AR3 = 8;
 * runs routine_2C88 (dark, extern; the routine_2C88
 * spelling matches the 375E neighbor) and tail-branches
 * to frag_2E64 (extern). ARs/A/B dead at exit (flagged).
 * Bound 372E-3752.
 */
extern void frag_3753(void);
extern void sub_2E2F(void);
extern void sub_E79D(void);
extern void sub_E80C(void);
extern void routine_2C88(void);
extern void frag_2E64(void);

void frag_372E(int ar0_live, int *ar2_in)
{
    int *ar2 = ar2_in;
    int *ar3;
    if (*(volatile int *)0x8 != 6) {                  /* cmpm; bc ntc */
        frag_3753();
        return;
    }
    *(volatile int *)0x27FE = *ar2;                  /* mvdk *ar2+%,imm */
    ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    *(volatile int *)0x27FF = *ar2;
    ar2 += ar0_live;
    *(volatile int *)0x2940 = *ar2;
    ar2 += ar0_live;
    *(volatile int *)0x2941 = *ar2;
    ar2 += ar0_live;
    *(volatile int *)0x2979 = *ar2;
    ar2 += ar0_live;
    *(volatile int *)0x244F = *ar2;
    ar2 += ar0_live;
    *(volatile int *)0x2450 = *ar2;
    ar2 += ar0_live;
    sub_2E2F();                                      /* call 0x2e2f */
    sub_E79D();                                      /* call 0xe79d */
    sub_E80C();                                      /* call 0xe80c */
    ar3 = (int *)10217;                              /* stm #10217,ar3 */
    /* stm #158,ar4; stm #2,ar5 (dead, noted) */
    *ar3 = 8;                                        /* st #8,*ar3 */
    routine_2C88();                                  /* call 0x2c88 */
    frag_2E64();                                      /* b 0x2e64 (tail) */
}
