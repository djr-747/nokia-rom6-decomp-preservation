/* ROM6 0x7937 SUB_7937 -- 38w quad-call store engine.
 * Verified encoding: src/rom6/kernel/7937_sub_7937.asm (recombine MATCH).
 * ORIGIN 0x7937
 * EXPECT: F074 059E 4A16 4A10 7714 0218 7715 0524 7719 0004 E756 F272 7959 7710 0001 F074 795D F274 795D 9A92 9B92 F484 F274 795D 9B92 9A92 F484 F784 F274 795D 9A92 9B92 F784 9B92 9A92 8A10 8A16 FC00
 *
 * Intent: Calls sub_059E (low-zone unsourced, flagged); saves
 * AR6/AR0 (pshm, balanced by popms); AR4 = 536, AR5 = 1316,
 * BK = 4 (no % modes in-span; outs, flagged); AR6 = AR5
 * (mvmm, dead -- restored by popm, flagged). RPTBD block
 * 0x7949-0x7959 runs BRC+1 times (BRC caller-live dark,
 * flagged; delays = AR0 = 1 which each pass observes):
 * plain call ROUTINE_795D, then three CALLD ROUTINE_795D
 * each preceded by its two store delays: pass stores 8
 * shifted high-words through caller-live AR3 (dark,
 * flagged), sth X,2,*ar3+ = bits 31-16 of X<<2 (25F2
 * precedent, per ti-c54x op_sth; extension dark, flagged):
 * [a,b] call [a] [b,a] call [a,b] call [b,a] with neg a
 * after the first call, neg a + neg b mid-pass, neg b before
 * the last pair. Tail restores AR0/AR6, return. A/B defined
 * by ROUTINE_795D (dark, flagged).
 * EXPECT from the image.
 */
void sub_7937(void)
{
    long a;  /* defined by ROUTINE_795D (dark, flagged) */
    long b;  /* defined by ROUTINE_795D (dark, flagged) */
    int *ar2;  /* live-in (dark, flagged; observed by ROUTINE_795D) */
    int *ar3;  /* live-in (dark, flagged) */
    int *ar4;
    int *ar5;
    int *ar6;
    int brc;  /* live-in (dark, flagged) */
    int i;

    sub_059E();                                              /* call 0x59e (low-zone, flagged) */
    /* pshm ar6; pshm ar0 (balanced by popms; caller-live, comment only) */
    ar4 = (int *)536;                                        /* stm #536,ar4 */
    ar5 = (int *)1316;                                       /* stm #1316,ar5 */
    /* stm #4,bk (no % in-span; out, flagged) */
    ar6 = ar5;                                               /* mvmm ar5,ar6 (dead; popm restores) */
    /* rptbd 0x7959: stm #1,ar0 delay runs once; block runs brc+1 */
    /* stm #1,ar0 (delay; observed by every pass) */
    for (i = 0; i <= (unsigned)brc; i++) { /* (BRC+1 passes incl. 0xFFFF wrap) */
        routine_795D();                                      /* call 0x795d */
        *ar3++ = (int)(((a << 2) >> 16) & 0xFFFFL);          /* sth a,2 (calld delays) */
        *ar3++ = (int)(((b << 2) >> 16) & 0xFFFFL);          /* sth b,2 */
        routine_795D();                                      /* calld 0x795d */
        a = -a;                                              /* neg a */
        *ar3++ = (int)(((b << 2) >> 16) & 0xFFFFL);          /* sth b,2 (delays) */
        *ar3++ = (int)(((a << 2) >> 16) & 0xFFFFL);          /* sth a,2 */
        routine_795D();                                      /* calld 0x795d */
        a = -a;                                              /* neg a */
        b = -b;                                              /* neg b */
        *ar3++ = (int)(((a << 2) >> 16) & 0xFFFFL);          /* sth a,2 (delays) */
        *ar3++ = (int)(((b << 2) >> 16) & 0xFFFFL);          /* sth b,2 */
        routine_795D();                                      /* calld 0x795d */
        b = -b;                                              /* neg b */
        *ar3++ = (int)(((b << 2) >> 16) & 0xFFFFL);          /* sth b,2 */
        *ar3++ = (int)(((a << 2) >> 16) & 0xFFFFL);          /* sth a,2 */
    }
    /* popm ar0; popm ar6 (balanced; comment only) */
    /* ret */
    (void)ar2;
    (void)ar4;
    (void)ar5;
    (void)ar6;
}
