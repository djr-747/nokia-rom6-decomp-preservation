/* ROM6 0x8B03 ROUTINE_8B03 -- 45w MACR table build.
 * Verified encoding: src/rom6/kernel/8b03_routine_8b03.asm (recombine MATCH).
 * ORIGIN 0x8B03
 * EXPECT: 1085 1195 F010 0028 7713 1109 FD43 1183 F010 0050 771A 0027 FD46 1183 8183 F020 B3DE 008D 8812 F020 118B 0883 8813 7182 2F2C 7712 2F2E 7314 2F2D F272 8B25 4592 302C 2B93 CB8A 7712 1113 EC4F 7092 113B 7213 2F2D EC27 E598 FC00
 *
 * Intent: A = *(AR5) (AR5 dark); B = *(AR5++); A -= 40;
 * AR3 = 4361. A < 0 skips B = *(AR3) (xc 1,alt); A -= 80;
 * BRC = 39; A > 0 skips B = *(AR3) (xc 1,agt) -- the two
 * skips are mutually exclusive (A0 < 40 vs A0 > 120), so B
 * = *(4361) always, noted; *(AR3) = B-low. A = -19490 +
 * (*(AR5--)<<16) (AR5 net unchanged); AR2 = A-low; A =
 * 4491 - (*(AR3)<<16); AR3 = A-low; *(0x2F2C) = *(AR2)
 * (mvdk, dmad dest); AR2 = 12078; *(0x2F2D) = AR4-entry
 * (mvmd, AR4 dark). RPTBD block is the macr alone (REA =
 * 0x8B25 = the macr; delays ld *ar2+,16,b + ld *(0x2C),t
 * run once): 40x B += round(*(AR3++) x T) (macar form,
 * exact rounding per oracle op_multiply; FRCT doubling
 * dark, flagged; SXM dark flagged). Then once: *(AR4++) =
 * B-low with B = *(AR2++) reloaded in parallel (the reload
 * is dead -- B unread after, noted). AR2 = 4371; 80x
 * *(AR2++) = *(0x113B) (rpt #79 mvkd); AR3 = *(0x2F2D)
 * (mvdm restores the AR4 snapshot); 40x *(AR2++) = *(AR3++)
 * (rpt #39 mvdd); return. T/AR5/AR4-entry dark; out
 * cells/ARs.
 * EXPECT from the image.
 */
void routine_8B03(void)
{
    long a;
    long b;
    int *ar2;
    int *ar3;
    int *ar4;  /* live-in (dark, flagged) */
    int *ar5;  /* live-in (dark, flagged) */
    int t;
    long p;
    int i;

    a = (long)*ar5;                                          /* ld *ar5,a (SXM dark, flagged) */
    b = (long)*ar5++;                                        /* ld *ar5+,b */
    a -= 40;                                                 /* sub #40,a */
    ar3 = (int *)4361;                                       /* stm #4361,ar3 */
    if (a >= 0)                                              /* xc 1,alt */
        b = (long)*ar3;                                      /* ld *ar3,b */
    a -= 80;                                                 /* sub #80,a */
    /* stm #39,brc */
    if (a <= 0)                                              /* xc 1,agt */
        b = (long)*ar3;                                      /* ld *ar3,b */
    *ar3 = (int)(b & 0xFFFFL);                               /* stl b,*ar3 */
    a = -19490;                                              /* ld #-19490,a */
    a += (long)*ar5-- << 16;                                 /* add *ar5-,a */
    ar2 = (int *)(a & 0xFFFFL);                              /* stlm a,ar2 */
    a = 4491;                                                /* ld #4491,a */
    a -= (long)*ar3 << 16;                                   /* sub *ar3,a */
    ar3 = (int *)(a & 0xFFFFL);                              /* stlm a,ar3 */
    *(volatile int *)0x2F2C = *ar2;                          /* mvdk *ar2,0x2f2c */
    ar2 = (int *)12078;                                      /* stm #12078,ar2 */
    *(volatile int *)0x2F2D = (int)(long)ar4;                /* mvmd ar4,0x2f2d */
    /* rptbd 0x8b25: delays run once */
    b = (long)*ar2++ << 16;                                  /* ld *ar2+,16,b (delay) */
    t = *(volatile int *)0x2C;                               /* ld 0x2c,t (delay) */
    for (i = 0; i < 40; i++) {                               /* (BRC+1; BRC = 39) */
        p = (long)*ar3++ * (long)t;                          /* macar *ar3+,b (FRCT dark, flagged) */
        b = (b + p + 0x8000L) & ~0xFFFFL;                    /* (rounding, oracle) */
    }
    *ar4++ = (int)(b & 0xFFFFL);                             /* st b,*ar4+ (parallel) */
    b = (long)*ar2++;                                        /* ld *ar2+,b (dead reload, noted) */
    ar2 = (int *)4371;                                       /* stm #4371,ar2 */
    for (i = 0; i < 80; i++)                                 /* rpt #79 (k+1) */
        *ar2++ = *(volatile int *)0x113B;                    /* mvkd 0x113b,*ar2+ */
    ar3 = (int *)(long)*(volatile int *)0x2F2D;              /* mvdm 0x2f2d,ar3 */
    for (i = 0; i < 40; i++)                                 /* rpt #39 */
        *ar2++ = *ar3++;                                     /* mvdd *ar3+,*ar2+ */
    /* ret */
}
