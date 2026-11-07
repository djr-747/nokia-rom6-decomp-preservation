/* ROM6 0xE50B ROUTINE_E50B -- 27w AGT-gated MAC lane.
 * Verified encoding: src/rom6/kernel/e50b_routine_e50b.asm (recombine MATCH).
 * ORIGIN 0xE50B
 * EXPECT: EA00 7711 1000 7710 0100 7714 FB5A 7715 FB9B 771A 0009 F272 E524 7716 3F00 A206 FA46 E51A 318D 6DAE 6DB6 A4BA 0111 F763 3E16 E445 FC00
 *
 * Intent: 10-tap AGT-gated MAC loop (RPTBD, BRC = 9). DP =
 * 0; pointers 4096/256/-1190/-1125 preloaded. Per tap: A =
 * (*AR2 - *AR4)<<16 (SUB dual MOD0 = X - Y per
 * op_dual_arithmetic), AR4--; BCD to E51A if AGT (deferred;
 * taken body runs the MPYA/scale/store leg, fall-through
 * re-loops); MPYA leg: A = T**AR5- (T caller-live dark,
 * flagged), scale leg B += mem(0x11)<<16, B <<= 3, A =
 * (mem(0x16)<<16) + B (4-operand ADD per SPRU172), store A
 * low to *AR3 with a parallel LD of *AR2- into T; AR3--,
 * AR2--. LMS/FIR tap-update shape: AR2 source, AR3 sink,
 * AR4/AR5 taps. (Wave-13: dual-SUB <<16 and ADD Smem <<16
 * corrected per the oracle leaves.)
 */
void routine_E50B(void)
{
    long a;
    long b;
    int *ar0;
    int *ar1;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;  /* live-in (dark, flagged) */
    int *ar4;
    int *ar5;
    int t;  /* T live-in (dark, flagged) */
    int i;

    /* ld #0,dp (DP = 0) */
    ar1 = (int *)4096;                                         /* stm #4096,ar1 */
    ar0 = (int *)256;                                          /* stm #256,ar0 */
    ar4 = (int *)-1190;                                        /* stm #-1190,ar4 */
    ar5 = (int *)-1125;                                        /* stm #-1125,ar5 */
    /* stm #9,brc */
    for (i = 0; i < 10; i++) {                                 /* rptbd 0xe524 */
        a = ((long)*ar2 - (long)*ar4--) << 16;                 /* sub *ar2,*ar4-,a */
        if (a > 0) {                                           /* bcd 0xe51a,agt (deferred; taken runs the leg) */
            a = (long)t * (long)*ar5--;                        /* mpya *ar5- */
            /* mar *ar6-0 (delay) */
            /* mar *ar6+0 (delay) */
            a = (long)*ar5++ * (long)*ar4++;                   /* mpy *ar5+,*ar4+,a (dual: X*Y, no T) */
            b += (long)*(volatile int *)0x11 << 16;            /* add 0x11,b */
            b <<= 3;                                           /* sfta b,3 */
            a = ((long)*(volatile int *)0x16 << 16) + b;      /* add 0x16,16,b,a */
            *ar3-- = (int)(a & 0xFFFFL);                       /* st *ar3- || ld *ar2-,t */
            t = *ar2--;
        }
    }
    /* ret */
    (void)b; (void)ar0; (void)ar1;
}
