/* ROM6 0x795D ROUTINE_795D -- 10w.
 * Verified encoding: src/rom6/kernel/795d_routine_795d.asm (recombine MATCH).
 * ORIGIN 0x795D
 * EXPECT: A43E A5BE B03E B3BE B030 E58E B330 FE00 E58E E765
 *
 * Intent: Dual-MAC dot-product step. A = *AR5 x *AR4, B = *AR5+ x *AR4
 * (MPY dual-mem, no T, integer mode assumed flagged); three MAC folds
 * (values assumed small for 32-bit long, flagged); one MVDD shuffle;
 * then the retd delays always run (second MVDD shuffle plus AR5 = AR6)
 * before the far return. *ar4+0% advances AR4 by AR0 each tap (linear;
 * modulo wrap needs caller-live BK, flagged). All ARs caller-live and
 * dead at return (no writeback, flagged). A/B die at retd except the
 * delay-store side effect (flagged). Bound 795D-7966.
 */
void routine_795D(int *ar5, int *ar4, int *ar2, int ar6_live, int ar0_live)
{
    long a;
    long b;
    a = (long)*ar5 * *ar4;                         /* mpy *ar5,*ar4+0%,a */
    ar4 += ar0_live;
    b = (long)*ar5 * *ar4;                         /* mpy *ar5+,*ar4+0%,b */
    ar5++;
    ar4 += ar0_live;
    a += (long)*ar5 * *ar4;                        /* mac *ar5,*ar4+0%,a */
    ar4 += ar0_live;
    b += (long)*ar5 * *ar4;                        /* mac *ar5+,*ar4+0%,b */
    ar5++;
    ar4 += ar0_live;
    a += (long)*ar5 * *ar2;                        /* mac *ar5,*ar2,a */
    *ar4 = *ar2++;                                 /* mvdd *ar2+,*ar4+0% */
    ar4 += ar0_live;
    b += (long)*ar5 * *ar2;                        /* mac *ar5,*ar2,b */
    *ar4 = *ar2++;                                 /* retd delay: mvdd (always runs) */
    ar4 += ar0_live;
    ar5 = (int *)ar6_live;                         /* retd delay: mvmm ar6,ar5 */
    (void)a;                                       /* A/B/ARs dead at retd (flagged) */
    (void)b;
    (void)ar5;
    /* retd */
}
