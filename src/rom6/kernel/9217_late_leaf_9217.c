/* ROM6 0x9217 LATE_LEAF_9217 -- 28w.
 * Verified encoding: src/rom6/kernel/9217_late_leaf_9217.asm (recombine MATCH).
 * ORIGIN 0x9217
 * EXPECT: F074 0594 7313 0060 7710 0009 7713 3218 7715 3200 7714 3210 7719 0020 F020 FE00 EC1F 8095 7715 3200 E800 8085 7712 3222 7717 2F80 E776 FC00
 *
 * Intent: Late-stage preset writer. Runs 0x594 (dark, helper_0594);
 * cell0x60 = AR3-value (mvmd, entry AR3); AR0 = 9, AR3 = 12824,
 * AR5 = 12800, AR4 = 12816, BK = 32 (all dead after, noted);
 * A = -512; 32 stores of A-low (0xFE00) at AR5++ (rpt #31);
 * AR5 = 12800; A = 0; *AR5 = 0; AR2 = 12834, AR7 = 12160,
 * AR6 = AR7-value (mvmm); return (all ARs/A dead, flagged).
 * All stores exact (small constants; A-low of -512 = 0xFE00).
 * Bound 9217-9232.
 */
extern void helper_0594(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void late_leaf_9217(int ar3_live)
{
    int *ar3;
    int *ar5;
    int *ar4;
    int *ar2;
    int ar6;
    int ar7;
    long a;
    int i;
    helper_0594();                                      /* call 0x594 (dark) */
    *(volatile int *)0x60 = ar3_live;                /* mvmd ar3,0x60 */
    /* stm #9,ar0; stm #12824,ar3; stm #12800,ar5; stm #12816,ar4 (dead, noted) */
    /* stm #32,bk (dead, noted) */
    a = -512;                                        /* ld #-512,a */
    ar5 = (int *)12800;
    for (i = 0; i < 32; i++)                         /* rpt #31 */
        *ar5++ = (int)(a & 0xFFFF);                  /* stl a,*ar5+ (= 0xFE00) */
    ar5 = (int *)12800;                              /* stm #12800,ar5 */
    a = 0;                                           /* ld #0,a */
    *ar5 = 0;                                        /* stl a,*ar5 */
    ar2 = (int *)12834;                              /* stm #12834,ar2 */
    ar7 = 12160;                                     /* stm #12160,ar7 */
    ar6 = ar7;                                       /* mvmm ar7,ar6 */
    /* ret (all dead, flagged) */
    (void)ar3; (void)ar4; (void)ar2; (void)ar6; (void)a;
}
