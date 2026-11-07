/* ROM6 0xBADB ROUTINE_BADB -- 59w FRCT-set dual-MAC filter worker.
 * Verified encoding: src/rom6/kernel/badb_routine_badb.asm (recombine MATCH).
 * ORIGIN 0xBADB
 * EXPECT: F074 06AA 61F8 2B08 0003 FC20 61F8 0577 0800 FC20 4A07 F7B9 F7B6 ED00 61F8 2AEB 0001 FA30 BAF8 7713 2B04 45F8 2B03 30F8 2207 2083 F486 F073 BAFC 30F8 2206 2083 F461 8283 E725 7716 0017 951D 44F8 2B06 F53D 8386 771A 0006 F072 BB0B 3C86 3192 8395 A418 771A 0098 F072 BB11 CC8B 7183 2B06 8A07 FC00
 *
 * Intent: Entry via 3x calld (A78D/A917/A995) with AR2 caller-live
 * dark (param, 8b9d precedent). Runs dark SUB_06AA (low-zone
 * mini-kernel, no symbol, opaque). TC gates over cells with carry
 * cleared when clear (rc ntc; carry 0-modeled dark, unread). Saves ST1
 * (pshm) then sets OVM = 1, FRCT = 1 (ssbx; the FRCT = 1 is KNOWN
 * in-span, so every mpy/mpya product below doubles -- modeled with
 * << 1, unlike the dark-FRct flagged forms elsewhere; OVM saturation
 * assumed small-values per the 3d3d house rule, flagged). ASM = 0
 * (ld #0,asm; dead, no ASM-shifted ops, noted). TC = (cell 0x2AEB & 1);
 * bcd 0xbaf8 runs its 2 delay words always (AR3 = 11012; B = cell
 * 0x2B03 << 16) then branches on TC. Taken (BAF8): T = cell 0x2206;
 * A = (*AR3 x T) << 1 (mpy); A <<= 1 (sfta); *AR3 = A-high. Not taken:
 * T = cell 0x2207; A = (*AR3 x T) << 1; A = max(A,B) signed (max a,
 * 22f3 idiom); b joins BAFC. Join: AR5 = AR2 (mvmm); AR6 = 23;
 * B = *AR3 << 13 (ld shift); A = cell 0x2B06 << 16; B -= A >> 3
 * arithmetic (sub a,-3,b, SXM flagged); *AR6 = B-high; rptb 0xbb0b
 * (BRC 6, 7x): A += (long)*AR6 << 16 (ADD_SMEM_SH16, SXM flagged per
 * 22f3); B = ((*AR2 x A-high) << 1), T = *AR2, AR2++ (MPYA_SMEM: B
 * replaced, T loaded per wave-14, e442 threading precedent); *AR5++ =
 * B-high. Tail: A = (*AR3 x T) << 1, AR2++ (mpy); rptb 0xbb11
 * (BRC 152, 153x): *AR5++ = A-low then A = (*AR2++ x T) << 1 in
 * parallel (st||mpy, store reads pre-write A per the st||ld rule);
 * cell 0x2B06 = *AR3 (mvdk dmad=dest); restores ST1 (popm); ret. Out
 * cells/A/B/T/ARs/TC/C; AR2 consumed. EXPECT from the image.
 */
extern void sub_06AA(void); /* dark, no symbol (low-zone mini-kernel) */

void routine_BADB(int *ar2_in)
{
    long a;
    long b;
    int t;
    int tc;
    int carry = 0;  /* C54x carry in (dark, flagged); never read in-span */
    int st1save;    /* pshm/popm st1 slot */
    int *ar2 = ar2_in;
    int *ar3;
    int *ar5;
    int *ar6;
    int i;

    sub_06AA();                                              /* call 0x6aa */
    tc = ((*(volatile int *)0x2B08 & 3) != 0);               /* bitf *(0x2b08),#3 */
    if (!tc)                                                 /* rc ntc */
        carry = 0;
    tc = ((*(volatile int *)0x577 & 2048) != 0);              /* bitf *(0x577),#2048 */
    if (!tc)                                                 /* rc ntc */
        carry = 0;
    st1save = 0;            /* pshm st1 (entry ST1 dark, restored below) */
    /* ssbx st1,ovm (OVM = 1; small-values assumed, flagged) */
    /* ssbx st1,frct (FRCT = 1; products double below) */
    /* ld #0,asm (ASM = 0; dead, noted) */
    tc = ((*(volatile int *)0x2AEB & 1) != 0);                /* bitf *(0x2aeb),#1 */
    ar3 = (int *)(long)11012;                                /* bcd delay: stm (always) */
    b = (long)*(volatile int *)0x2B03 << 16;                 /* bcd delay: ld *(0x2b03),16,b */
    if (tc) {                                                /* bcd 0xbaf8,tc */
        t = *(volatile int *)0x2206;                         /* ld *(0x2206),t */
        a = ((long)*ar3 * (long)t) << 1;                     /* mpy *ar3,a (FRCT = 1) */
        a <<= 1;                                             /* sfta a,1 */
        *ar3 = (int)((a >> 16) & 0xFFFFL);                   /* sth a,*ar3 */
    } else {
        t = *(volatile int *)0x2207;                         /* ld *(0x2207),t */
        a = ((long)*ar3 * (long)t) << 1;                     /* mpy *ar3,a (FRCT = 1) */
        if (a < b)                                           /* max a (signed, 22f3) */
            a = b;
    }
    ar5 = ar2;                                               /* mvmm ar2,ar5 */
    ar6 = (int *)(long)23;                                   /* stm #23,ar6 */
    b = (long)*ar3 << 13;                                    /* ld *ar3,13,b */
    a = (long)*(volatile int *)0x2B06 << 16;                 /* ld *(0x2b06),16,a */
    b -= a >> 3;                                             /* sub a,-3,b (arith, SXM flagged) */
    *ar6 = (int)((b >> 16) & 0xFFFFL);                       /* sth b,*ar6 */
    for (i = 0; i < 7; i++) {                                /* rptb 0xbb0b */
        a += (long)*ar6 << 16;                               /* add *ar6,16,a (SXM flagged) */
        b = ((long)*ar2 * (long)(short)((a >> 16) & 0xFFFFL)) << 1;
        t = *ar2;                                            /* mpya *ar2+ (B replaced, T loaded) */
        ar2++;
        *ar5++ = (int)((b >> 16) & 0xFFFFL);                 /* sth b,*ar5+ */
    }
    a = ((long)*ar3 * (long)t) << 1;                         /* mpy *ar3,*ar2+,a (FRCT = 1) */
    ar2++;
    for (i = 0; i < 153; i++) {                              /* rptb 0xbb11 */
        *ar5++ = (int)(a & 0xFFFFL);                         /* st a,*ar5+ (pre-write A) */
        a = ((long)*ar2++ * (long)t) << 1;                   /* || mpy *ar2+,a (FRCT = 1) */
    }
    (void)st1save;          /* popm st1 (entry ST1 restored) */
    (void)carry;
}
