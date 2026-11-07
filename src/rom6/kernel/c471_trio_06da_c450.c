/* ROM6 0xC471 TRIO_06DA_C450 lane 3 -- 27w vector add/copy lane.
 * Verified encoding: src/rom6/kernel/c471_trio_06da_c450.asm (recombine MATCH).
 * ORIGIN 0xC471
 * EXPECT: F074 06DA E746 E727 10F8 2AEA F847 C47E E721 F074 C53D E764 E772 771A 0007 F272 C485 7713 28AC A089 8294 EC47 E58A EC07 7192 28AC FC00
 *
 * Intent: Lane 3 of the C450/C460/C471 trio (sibling lanes:
 * C450 add + bulk copy, C460 call + BRC fill; this lane adds
 * the C53D leg and the accumulate-then-move tail). Call
 * shared head 0x6DA (RAM: zero in mask dump); stash AR4/AR6,
 * AR2/AR7; if *(0x2AEA) set take the C53D leg with AR2 as
 * cursor (in-image span C53D, asm-verified, no C entry yet --
 * provisional link name); restore pointers; BRC = 7, AR3 =
 * 10412; RPTBD block x8: A += *AR2 + *AR3 (ADD Smem pair:
 * dst_old + Smem<<16 each per op_add_smem), stream A MSW to
 * *AR4+; 72x bulk move *AR2+ to *AR4+; 8x store to 0x28AC;
 * return. (Wave-13: ADD Smem <<16 corrected per the oracle
 * leaf.)
 */
extern void sub_06DA(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_C53D(void); /* in-image span C53D, asm-verified, no C entry yet */

void trio_06DA_C471(void)
{
    long a;
    int *ar1;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;  /* live-in (dark, flagged) */
    int *ar4;  /* live-in (dark, flagged) */
    int *ar6;
    int *ar7;
    int i;

    sub_06DA();                                                /* call 0x6da (RAM) */
    ar6 = ar4;                                                 /* mvmm ar4,ar6 */
    ar7 = ar2;                                                 /* mvmm ar2,ar7 */
    a = (long)*(volatile int *)0x2AEA;                         /* ld *(0x2aea),a */
    if (a > 0) {                                               /* bc 0xc47e,aleq (taken when A<=0 skips; leg runs when A>0) */
        ar1 = ar2;                                             /* mvmm ar2,ar1 */
        sub_C53D();                                            /* call 0xc53d */
    }
    ar4 = ar6;                                                 /* mvmm ar6,ar4 */
    ar2 = ar7;                                                 /* mvmm ar7,ar2 */
    /* stm #7,brc */
    ar3 = (int *)10412;                                        /* stm #10412,ar3 (rptbd delay) */
    for (i = 0; i < 8; i++) {                                  /* rptbd 0xc485 */
        a += (long)*ar2++ << 16;                               /* add *ar2+,*ar3+,a */
        a += (long)*ar3++ << 16;
        *ar4++ = (int)((a >> 16) & 0xFFFFL);                   /* sth a,*ar4+ */
    }
    for (i = 0; i < 72; i++)                                   /* rpt #71 */
        *ar4++ = *ar2++;                                       /* mvdd *ar2+,*ar4+ */
    for (i = 0; i < 8; i++) {                                  /* rpt #7 */
        *(volatile int *)0x28AC = *ar2++;                      /* mvdk *ar2+,0x28ac */
    }
    /* ret */
    (void)ar1;
}
