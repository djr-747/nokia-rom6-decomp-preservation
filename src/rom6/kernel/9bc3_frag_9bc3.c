/* ROM6 0x9BC3 FRAG_9BC3 -- 50w banz sieve with class exits.
 * Verified encoding: src/rom6/kernel/9bc3_frag_9bc3.asm (recombine MATCH).
 * ORIGIN 0x9BC3
 * EXPECT: 7212 2F00 7214 2F01 7216 2F02 F074 9C4D 4817 F845 9BBE 7716 0000 E765 7711 2F00 6AF8 0014 0001 E763 E767 6C84 9BDB 6DD2 6D96 6C84 9BE6 6F82 0D58 6D94 6D96 F273 9BEB F330 00FF 11D2 6D8C 6D96 F330 00FF F210 00C1 F845 9BF5 F210 007D F845 9BF8 F073 9C15
 *
 * Intent: AR2/AR4/AR6 = cells 0x2F00/0x2F01/0x2F02
 * (mvdm; AR4/AR6 register-values, AR2 pointer).
 * Runs wrap_9C4D(AR2, AR4, AR6). A = AR7 register
 * value (ldm, AR7 entry-dark, flagged); A == 0 runs
 * the 9BBE epilogue inline (ld #-1,a; cell 0x20FA =
 * -1; return -- skips the 9c4d call, verified
 * against the 9B72 tail words). Else AR6 = 0,
 * AR5 = AR3 = AR7 = (int *)AR6; AR1 = 12032; cell
 * 0x14 ^= 1 (xorm). First banz (test-then-dec
 * per 2fe8): nonzero skips the *ar2+% step to the
 * 9BDB join; else AR2 += AR0-live (mar *ar2+%,
 * 351d linear convention, wrap flagged). Join:
 * AR6++. Second banz: nonzero enters the 9BE6
 * lane, else B = *AR2 >> 8 (ld -8, SXM? flagged
 * per 4b9a); AR4++; AR6++; the bd delay (B &= 255)
 * runs before taking the 9BEB join. 9BE6 lane: B =
 * *AR2 (ld, SXM? flagged); AR2 += AR0-live; AR4--;
 * AR6++; B &= 255; falls into 9BEB. Join 9BEB:
 * A = B - 193; zero tail-calls frag_9BF5(AR7) and
 * returns; else A = B - 125; zero tail-calls
 * frag_9BF8(AR6, AR0-live, AR2, AR4) and returns;
 * else tail-calls frag_9C15 (shared 4-entry join
 * in asm-only 9C13, intake varies per entry, dark,
 * flagged) and returns. Entry AR0/AR7 caller-live
 * dark.
 * EXPECT from the image.
 */
extern void wrap_9C4D(int *ar2, int ar4_live, int ar6_live);
extern void frag_9BF5(int *par7);
extern void frag_9BF8(int ar6_live, int ar0_live, int *ar2_in, int ar4_live);
extern void frag_9C15(void); /* joins 9c13 interior @9C15; shared join, dark, flagged */

void frag_9BC3(int ar0_live)
{
    long a;
    long b;
    int *ar1;
    int *ar2;
    int *ar3;
    int *ar5;
    int *ar7;   /* live-in (dark, flagged) until set */
    int ar4v;
    int ar6v;

    ar2 = (int *)(long)*(volatile int *)0x2F00;            /* mvdm 0x2f00,ar2 */
    ar4v = *(volatile int *)0x2F01;                        /* mvdm 0x2f01,ar4 */
    ar6v = *(volatile int *)0x2F02;                        /* mvdm 0x2f02,ar6 */
    wrap_9C4D(ar2, ar4v, ar6v);                             /* call 0x9c4d */
    a = (long)ar7;                                         /* ldm ar7,a */
    if (a == 0L) {                                         /* bc 0x9bbe,aeq */
        a = -1L;                                           /* (9BBE:) ld #-1,a */
        *(volatile int *)0x20FA = (int)(a & 0xFFFFL);      /* stl a,*(0x20fa) */
        return;
    }
    ar6v = 0;                                              /* stm #0,ar6 */
    ar5 = (int *)(long)ar6v;                               /* mvmm ar6,ar5 */
    ar1 = (int *)(long)12032;                              /* stm #12032,ar1 */
    *(volatile int *)0x14 ^= 1;                            /* xorm #1,*(0x14) */
    ar3 = (int *)(long)ar6v;                               /* mvmm ar6,ar3 */
    ar7 = (int *)(long)ar6v;                               /* mvmm ar6,ar7 */
    if (ar4v-- != 0)                                       /* banz 0x9bdb */
        goto join_db;
    ar2 += ar0_live;                                       /* mar *ar2+% (wrap flagged) */
join_db:
    ar6v++;                                                /* mar *ar6+ */
    if (ar4v-- != 0)                                       /* banz 0x9be6 */
        goto lane_e6;
    b = (long)(*ar2 >> 8);                                 /* ld *ar2,-8,b (SXM?) */
    ar4v++;                                                /* mar *ar4+ */
    ar6v++;                                                /* mar *ar6+ */
    /* bd 0x9beb (delay runs before the branch) */
    b &= 255L;                                             /* delay: and #255,b */
    goto join_eb;
lane_e6:
    b = (long)*ar2;                                        /* ld *ar2+%,b (SXM?) */
    ar2 += ar0_live;                                       /* +0% step (wrap flagged) */
    ar4v--;                                                /* mar *ar4- */
    ar6v++;                                                /* mar *ar6+ */
    b &= 255L;                                             /* and #255,b */
    /* falls into join_eb */
join_eb:
    a = b - 193L;                                          /* sub #193,b,a */
    if (a == 0L) {                                         /* bc 0x9bf5,aeq */
        frag_9BF5(ar7);                                    /* b 0x9bf5 (tail) */
        return;
    }
    a = b - 125L;                                          /* sub #125,b,a */
    if (a == 0L) {                                         /* bc 0x9bf8,aeq */
        frag_9BF8(ar6v, ar0_live, ar2, ar4v);              /* b 0x9bf8 (tail) */
        return;
    }
    frag_9C15();                                           /* b 0x9c15 (tail) */
}
