/* ROM6 0xFF40 RUN_FF40 -- 33w LMS update + distance lane.
 * Verified encoding: src/rom6/kernel/ff40_run_ff40.asm (recombine MATCH).
 * ORIGIN 0xFF40
 * EXPECT: 7719 077E 7712 0081 F074 FF69 7719 0FFF 7712 1000 F074 FF69 8910 E900 4719 E118 7714 FF7A 7712 000B F074 FF5E E302 82F8 1001 7310 1000 F074 FF5E F6E1 EC06 F495 FC00

 *
 * Intent: LMS coefficient-update lane plus an absolute-
 * distance sample. BK = 1918; AR2 = 129; run sub_FF69
 * (C entry exists); BK = 4095; AR2 = 4096; run sub_FF69
 * again; AR0 = BL (entry B dark, flagged); B = 0; 26x
 * LMS *AR3,*AR2+ (rpt 0x19): A += (X << 16) + 0x8000 and
 * B += signed X*Y (FRCT-doubling flagged, FRCT dark) per
 * the oracle LMS leaf op_lms_dual (the dc18
 * "oracle-unbound" note is stale for this form); AR4 =
 * -134 (stm word 0xFF7A); AR2 = 11; run the interior
 * FF5E nop lane (call 0xff5e: 2 nops + ret -- timing
 * lane, modeled as a static); ABDST sample A =
 * ((*AR2) - (*AR4)) << 16 (B-update dead in-span,
 * flagged); store A MSW to cell 0x1001; cell 0x1000 =
 * AR0 (MVMD); run FF5E lane again; IDLE 2 (sleep until
 * interrupt -- extern cpu_idle placeholder per the 84af
 * precedent); 7x NOP alignment sled (rpt #6); return.
 * In AR3 (dark); out cells 0x1000/0x1001.
 * (Wave-13: EXPECT from the image word map; LMS per the
 * oracle leaf, not the stale dc18 note.)
 */
extern void sub_FF69(void);
extern void cpu_idle(int mode); /* IDLE sleep; no ROM definition */

static void lane_FF5E(void)
{
    /* 2x nop + ret (timing lane at FF5E; no C form for nop) */
}

void run_FF40(void)
{
    long a;
    long b;
    long d;
    int *ar0;
    int *ar2;
    int *ar3;  /* live-in (dark, flagged) */
    int *ar4;
    int i;

    /* stm #1918,bk (BK = 1918) */
    ar2 = (int *)129;                                          /* stm #129,ar2 */
    sub_FF69();                                                /* call 0xff69 */
    /* stm #4095,bk (BK = 4095) */
    ar2 = (int *)4096;                                         /* stm #4096,ar2 */
    sub_FF69();                                                /* call 0xff69 */
    ar0 = (int)(b & 0xFFFFL);                                  /* stlm b,ar0 (entry B dark) */
    b = 0;                                                     /* ld #0,b */
    for (i = 0; i < 26; i++) {                                 /* rpt 0x19 */
        a += ((long)*ar3 << 16) + 0x8000L;                     /* lms *ar3,*ar2+ (A channel per op_lms_dual) */
        b += (long)*ar3 * (long)*ar2++;                        /* lms B channel (signed X*Y; FRCT-doubling flagged) */
    }
    ar4 = (int *)-134;                                         /* stm #-134,ar4 */
    ar2 = (int *)11;                                           /* stm #11,ar2 */
    lane_FF5E();                                               /* call 0xff5e (interior nop lane) */
    d = (long)*ar2 - (long)*ar4;                               /* abdst *ar2,*ar4 (B-update dead in-span, flagged) */
    a = d << 16;
    *(volatile int *)0x1001 = (int)((a >> 16) & 0xFFFFL);     /* sth a,*(0x1001) */
    *(volatile int *)0x1000 = (int)ar0;                        /* mvmd ar0,0x1000 */
    lane_FF5E();                                               /* call 0xff5e */
    cpu_idle(2);                                               /* idle 2 */
    for (i = 0; i < 7; i++)                                    /* rpt #6 */
        ;                                                      /* nop */
    /* ret */
    (void)b;
}
