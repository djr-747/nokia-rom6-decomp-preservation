/* ROM6 0x644A SUB13_644A -- 14w (interior entry of SUB13_643E).
 * Verified encoding: src/rom6/kernel/644b_sub13_644a.asm (recombine MATCH).
 * ORIGIN 0x644A
 * EXPECT: FC00 7685 0000 7712 0915 1086 0092 7713 2FD7 8093 E505 1083 F010 0033
 *
 * Intent: Window preload head. Word0 is the prior span's RET (verified,
 * not modeled). *AR5 = 0; AR2 = 2325; A = *AR6 + *AR2++ (ADD Xmem,
 * SXM = 1 sign-extension flagged); AR3 = 12247; *AR3++ = A-low;
 * *AR3 = *AR2 then AR3-- (MVDD, AR2 unstepped); A = *AR3 - 51.
 * A/AR2/AR3 run live into 0x6457 (no binding yet, flagged).
 * Bound 644A-6457, falls through.
 */
void sub13_644A(int *par5, int *par6)
{
    int *ar2;
    int *ar3;
    long a;
    *par5 = 0;                                     /* st #0,*ar5 */
    ar2 = (int *)2325;                             /* stm #2325,ar2 */
    a = (long)*par6;                               /* ld *ar6,a */
    a += (long)*ar2++;                             /* add *ar2+,a */
    ar3 = (int *)12247;                            /* stm #12247,ar3 */
    *ar3++ = (int)(a & 0xFFFF);                    /* stl a,*ar3+ */
    *ar3 = *ar2;                                   /* mvdd *ar2,*ar3- */
    ar3--;
    a = (long)*ar3;                                /* ld *ar3,a */
    a -= 51;                                       /* sub #51,a */
    (void)a;                                       /* A/AR2/AR3 live into 0x6457 (flagged) */
}
