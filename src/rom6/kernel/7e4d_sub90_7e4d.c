/* ROM6 0x7E4D SUB90_7E4D -- 59w straight-line filter setup + repeat lanes.
 * Verified encoding: src/rom6/kernel/7e4d_sub90_7e4d.asm (recombine MATCH).
 * ORIGIN 0x7E4D
 * EXPECT: F074 059E 76F8 2578 0000 7712 2584 7713 2ABB 7711 000B F074 7E88 7713 2585 7712 2ABB 1082 F030 FF03 1183 F762 F330 00FC F2A0 8092 771A 0004 F072 7E6F 44E3 0001 1A83 F47A 8093 771A 0003 F272 7E80 7713 2585 1083 F030 00FF 1182 F2A8 8092 1293 F0F8 1182 F2A8 8092 1083 F030 00FF 1182 FE00 F2A8 8092
 *
 * Intent: Entry via 4x call (7DCx zone) with no live regs (void). Runs
 * dark SUB_059E (low-zone mini-kernel, zero in mask dump per the 7e88
 * precedent). Cell 0x2578 = 0 (st). Seats AR2 = 9604, AR3 = 10939,
 * AR1 = 11. Runs sub31_7E88. Reseats AR3 = 9605, AR2 = 10939. A =
 * *AR2 masked to -253 low bits (and #-253); B = *AR3 shifted left 2
 * (sfta, exact); B &= 252; A |= B (or b,a); *AR2++ = A-low. rptb 0x7e6f
 * (BRC 4, 5x): A = *(AR3+1) << 16 (ld offset+shift); A |= (unsigned)
 * *AR3 (or Smem zero-extends per 2289); A >>= 6 arithmetic (sfta,
 * SXM flagged); *AR3++ = A-low. rptbd 0x7e80 (delay stm #9605,ar3 runs
 * once; block 4x BRC 3 + 1): per pass A = *AR3 & 0xFF, B = *AR2,
 * A |= B << 8 (OR_ACC_SHIFT, S=bit9 D=bit8 ground), *AR2++ = A-low,
 * then A = unsigned *AR3++ >> 8 logical (ldu + SFTL_ACC, exact) and the
 * same or/store pair. Tail: A = *AR3 & 0xFF, B = *AR2; retd with its 2
 * delay words (or + store) running before the return; span ends 7E87.
 * T untouched (dark, noted); BRC dead after (loop consts, noted). Out
 * cells/A/B/ARs. EXPECT from the image.
 */
extern void sub_059E(void); /* low-region: zero in mask dump (7e88 precedent) */
extern void sub31_7E88(void);

void sub90_7E4D(void)
{
    long a;
    long b;
    int *ar1;
    int *ar2;
    int *ar3;
    int i;

    sub_059E();                                              /* call 0x59e */
    *(volatile int *)0x2578 = 0;                             /* st #0,*(0x2578) */
    ar2 = (int *)(long)9604;                                 /* stm #9604,ar2 */
    ar3 = (int *)(long)10939;                                /* stm #10939,ar3 */
    ar1 = (int *)(long)11;                                   /* stm #11,ar1 */
    sub31_7E88();                                            /* call 0x7e88 */
    ar3 = (int *)(long)9605;                                 /* stm #9605,ar3 */
    ar2 = (int *)(long)10939;                                /* stm #10939,ar2 */
    a = (long)*ar2;                                          /* ld *ar2,a */
    a &= -253L;                                              /* and #-253,a */
    b = (long)*ar3;                                          /* ld *ar3,b */
    b <<= 2;                                                 /* sfta b,2 */
    b &= 252L;                                               /* and #252,b */
    a |= b;                                                  /* or b,a */
    *ar2++ = (int)(a & 0xFFFFL);                             /* stl a,*ar2+ */
    for (i = 0; i < 5; i++) {                                /* rptb 0x7e6f */
        a = (long)*(ar3 + 1) << 16;                          /* ld *ar3(0x1),16,a */
        a |= (long)(unsigned)*ar3;                           /* or *ar3,a */
        a >>= 6;                                             /* sfta a,-6 (arith, SXM flagged) */
        *ar3++ = (int)(a & 0xFFFFL);                         /* stl a,*ar3+ */
    }
    ar3 = (int *)(long)9605;                                 /* rptbd delay (runs once) */
    for (i = 0; i < 4; i++) {                                /* rptbd 0x7e80 */
        a = (long)*ar3;                                      /* ld *ar3,a */
        a &= 0xFFL;                                          /* and #255,a */
        b = (long)*ar2;                                      /* ld *ar2,b */
        a |= b << 8;                                         /* or b,8,a */
        *ar2++ = (int)(a & 0xFFFFL);                         /* stl a,*ar2+ */
        a = (long)(unsigned)*ar3++;                          /* ldu *ar3+,a */
        a >>= 8;                                             /* sftl a,-8 (logical, exact: a >= 0) */
        b = (long)*ar2;                                      /* ld *ar2,b */
        a |= b << 8;                                         /* or b,8,a */
        *ar2++ = (int)(a & 0xFFFFL);                         /* stl a,*ar2+ */
    }
    a = (long)*ar3;                                          /* ld *ar3,a */
    a &= 0xFFL;                                              /* and #255,a */
    b = (long)*ar2;                                          /* ld *ar2,b */
    /* retd (delays run before the return) */
    a |= b << 8;                                             /* delay: or b,8,a */
    *ar2++ = (int)(a & 0xFFFFL);                             /* delay: stl a,*ar2+ */
    (void)ar1;
}
