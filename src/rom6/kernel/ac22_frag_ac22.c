/* ROM6 0xAC22 FRAG_AC22 -- 42w AR-select + accumulate lane.
 * Verified encoding: src/rom6/kernel/ac22_frag_ac22.asm (recombine MATCH).
 * ORIGIN 0xAC22
 * EXPECT: 9401 8810 6B84 FFFF 61F8 3EC8 0040 F495 F495 F110 0400 F820 AC3C 7714 0DEA F84B AC41 F010 079E 7714 0B46 FF42 7714 0746 F073 AC41 7714 0DE8 FF4A 7714 0AE2 61F8 3EC8 0010 6DB4 E50A 1083 FD30 F47D 0084 8084 FC00
 *
 * Intent: A = *(AR2)<<1 (AR2 dark); AR0 = A-low; *(AR4) -=
 * 1 (addm, AR4 dark, flagged); B = A - 1024 (sub 3-op).
 * Bit 6 of *(0x3EC8) clear selects AR4 = 3560 (bc ntc to
 * the 3560 join; SUB preserves TC), with B < 0 overriding
 * to 2786 (xc fall-through); else B < 0 keeps entry AR4
 * (bc blt straight to the bitf), else A -= 1950 with AR4 =
 * 2886 for A >= 0 (xc skips the 1862 stm) or 1862 for A < 0
 * (fall-through stm), both taking b to the bitf and skipping
 * the 2786 override. Every path then runs bitf *(0x3EC8),#16
 * (the xc skips only the 2-word stm, so TC = bit 4
 * unconditionally; any-bit TC per oracle). AR4 += AR0 (mar);
 * *(AR4++) = *(AR2) (mvdd, AR2 unstepped); A = *(AR3) (SXM
 * dark, flagged); TC set skips A >>= 3 (xc 1; sfta
 * arithmetic, SXM-gated, flagged);
 * A += *(AR4)<<16; *(AR4) = A-low; return. AR2/AR3/AR4
 * entry dark; A/B/TC/AR0 computed; out cells/ARs/A.
 * EXPECT from the image.
 */
void frag_AC22(void)
{
    long a;
    long b;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;  /* live-in (dark, flagged) */
    int *ar4;  /* live-in (dark, flagged) */
    int ar0;
    int tc;

    a = (long)*ar2 << 1;                                     /* ld *ar2,1,a (SXM dark, flagged) */
    ar0 = (int)(a & 0xFFFFL);                                /* stlm a,ar0 */
    *ar4 += -1;                                              /* addm #-1,*ar4 */
    tc = (*(volatile int *)0x3EC8 & 64) != 0;                 /* bitf *(0x3ec8),#64 */
    /* nop; nop */
    b = a - 1024;                                            /* sub #1024,a,b (TC preserved) */
    if (!tc) {                                               /* bc 0xac3c,ntc */
        ar4 = (int *)3560;
        if (b < 0)                                           /* xc 2,bgeq (fall-through only) */
            ar4 = (int *)2786;
    } else if (b >= 0) {
        a -= 1950;                                           /* sub #1950,a */
        if (a >= 0)                                          /* xc 2,ageq + b (both reach bitf) */
            ar4 = (int *)2886;                               /* (1862 stm skipped) */
        else
            ar4 = (int *)1862;                               /* (fall-through stm, then b) */
        /* b 0xac41 (skips the 2786 override) */
    }
    /* (blt path: AR4 = entry, A unchanged) */
    tc = (*(volatile int *)0x3EC8 & 16) != 0;                 /* bitf *(0x3ec8),#16 (all paths run it) */
    ar4 += ar0;                                              /* mar *ar4+0 */
    *ar4++ = *ar2;                                           /* mvdd *ar2,*ar4+ */
    a = (long)*ar3;                                          /* ld *ar3,a (SXM dark, flagged) */
    if (!tc)                                                 /* xc 1,tc */
        a = a >> 3;                                          /* sfta a,-3 (SXM-gated, flagged) */
    a += (long)*ar4 << 16;                                   /* add *ar4,a */
    *ar4 = (int)(a & 0xFFFFL);                               /* stl a,*ar4 */
    /* ret */
}
