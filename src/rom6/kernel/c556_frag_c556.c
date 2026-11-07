/* ROM6 0xC556 FRAG_C556 -- 32w MAC/MAS lattice chain.
 * Verified encoding: src/rom6/kernel/c556_frag_c556.asm (recombine MATCH).
 * ORIGIN 0xC556
 * EXPECT: 7716 0008 F272 C574 7717 000C 942F B010 E506 F47E E900 A761 F630 B821 F461 E4BA 8094 6F82 0D2E 900E F47C 2C8F 2597 F630 E940 358D F769 2486 F519 F583 8392 FC00

 *
 * Intent: Dual-MAC lattice chain (RPTBD block through REA
 * 0xC574, BRC caller-set dark -- one representative pass
 * modeled, flagged). AR6 = 8; delay stm AR7 = 12; block
 * head A = *AR4 << 15. Per pass: A += X*Y dual MAC
 * (*AR3 * *AR2, no T); *AR4- = *AR2 (mvdd); A >>= 2;
 * B = 0; B += unsigned(*AR4-) * signed(*AR3) (MACSU dual,
 * X-unsigned, flagged); A -= B >> 16 (SUB acc-src shift
 * form); A -= *AR4 * *AR3 (MAS dual, no T); A <<= 1;
 * parallel store AL to *AR4+ with T = *AR5+ loaded;
 * store AL to *AR4+; B = (*AR2 << 14) - A (4-op SUB);
 * A += *AR2 << 14 (3-op ADD); A >>= 4; A -= T * *AR7-
 * (MAS single, T dark, flagged); B = unsigned(*AR7+) * T
 * (MPYU, T dark); A -= B >> 16; B = 64; B += T * *AR5-
 * (MACA, round flagged); B <<= 9; A = unsigned(*AR6) * T;
 * B += A >> 7; SAT B (OVM dark, flagged); store B MSW to
 * *AR2+; return (the ret sits at the block end: first pass
 * returns, repeat moot, flagged). T never loaded in-span
 * (dark throughout, flagged). Viterbi/lattice update
 * shape: AR2/AR3/AR4/AR5/AR6/AR7 cursors live (dark).
 * (Wave-13: written in the established style with the
 * oracle-grounded dual/shift/4-op forms.)
 */
void frag_C556(void)
{
    long a;
    long b;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;  /* live-in (dark, flagged) */
    int *ar4;  /* live-in (dark, flagged) */
    int *ar5;  /* live-in (dark, flagged) */
    int *ar6;
    int *ar7;
    int t;  /* T live-in, never loaded in-span (dark, flagged) */

    ar6 = (int *)8;                                            /* stm #8,ar6 */
    /* rptbd 0xc574 (delays: stm #12,ar7 + block head ld) */
    ar7 = (int *)12;                                           /* (delay 1) */
    a = (long)*ar4 << 15;                                      /* (delay 2 / block head) ld *ar4,15,a */
    /* (one representative RPTBD pass; BRC dark) */
    a += (long)*ar3 * (long)*ar2;                              /* mac *ar3,*ar2,a (dual) */
    *ar4-- = *ar2;                                             /* mvdd *ar2,*ar4- */
    a >>= 2;                                                   /* sfta a,-2 */
    b = 0;                                                     /* ld #0,b */
    b += (long)(unsigned)*ar4-- * (long)*ar3;                  /* macsu *ar4-,*ar3,b (X-unsigned) */
    a -= b >> 16;                                              /* sub b,-16,a */
    a -= (long)*ar4 * (long)*ar3;                              /* mas *ar4,*ar3,a (dual) */
    a <<= 1;                                                   /* sfta a,1 */
    *ar4++ = (int)(a & 0xFFFFL);                               /* st a,*ar4+ || ld *ar5+,t */
    t = *ar5++;
    *ar4++ = (int)(a & 0xFFFFL);                               /* stl a,*ar4+ */
    b = ((long)*ar2 << 14) - a;                                /* sub *ar2,14,a,b (4-op) */
    a += (long)*ar2 << 14;                                     /* add *ar2,14,a */
    a >>= 4;                                                   /* sfta a,-4 */
    a -= (long)t * (long)*ar7--;                               /* mas *ar7-,a */
    b = (long)(unsigned)*ar7++ * (long)t;                      /* mpyu *ar7+,b */
    a -= b >> 16;                                              /* sub b,-16,a */
    b = 64;                                                    /* ld #64,b */
    b += (long)t * (long)*ar5--;                               /* maca *ar5-,b (round flagged) */
    b <<= 9;                                                   /* sfta b,9 */
    a = (long)(unsigned)*ar6 * (long)t;                        /* mpyu *ar6,a */
    b += a >> 7;                                               /* add a,-7,b */
    /* sat b (OVM dark, flagged) */
    if (b > 0x7FFFFFFFL) b = 0x7FFFFFFFL;
    if (b < -0x80000000L) b = -0x80000000L;
    *ar2++ = (int)((b >> 16) & 0xFFFFL);                       /* sth b,*ar2+ */
    /* ret */
    (void)t;
}
