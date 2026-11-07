/* ROM6 0x5282 DISPATCH_SLED_A -- 66w (span 5282-52C3, single entry).
 * Verified encoding: src/rom6/rf/5282_dispatch_sled_a.asm (recombine MATCH).
 * ORIGIN 0x5282
 * EXPECT: 7710 314A 7711 24B4 7712 312A 7713 2494 7714 318A 7715 03D9 7716 310A 7717 25A1 1087 0886 F843 52AA 6D96 F844 529F 5690 4E91 F273 52AF E589 E5AB 6DE8 0002 4816 F010 310A 08F8 31AA FA43 5292 6D92 6D94 E800 4E91 8093 7695 0080 6D97 4817 F010 25A1 08F8 265C F842 52C0 4816 F010 310A 08F8 31AA F843 5292 F073 52AA 76F8 245E 25A1 FC00
 *
 * Intent: RF dispatch-sled prologue (5282 family head; the 52F7+
 * merge fragments live in sibling spans). Sets AR0-AR7 to table
 * bases (stm immediates, DARAM locals). L5292 loop head: A =
 * *AR7 - *AR6 signed (ld/sub, 71a3/28a5 sign-extend); A < 0
 * joins the zero-fill at L52AA (bc alt, COND_ALT sign test per
 * op_branch_cond_common). Else AR6++ (mar); A != 0 skips the
 * double-copy (bc aneq to L529F). Else the copy: A = 32-bit
 * *AR0 (dld, high word first per op_dld_long32: A = (w0 << 16)
 * | w1, AR0 += 2; SXM dark in-span, sign-extended form assumes
 * SXM = 1, flagged); 32-bit store to *AR1 (dst, high first per
 * op_dst_long32 and the 3d79 precedent: *ar1++ = high,
 * *ar1++ = low); bd 0x52af unconditional with its two 1-word
 * delay slots both running (WORD-count rule: mvdd *ar2+ to *ar3+,
 * mvdd *ar4+ to *ar5+, single-word moves per the 3273
 * precedent), then lands L52AF. L529F: AR0 += 2 (mar offset);
 * A = AR6-value (ldm, zero-extend per the 3273 precedent); A -=
 * 12554 (sub); A -= *(0x31AA) signed (sub absolute, e54b
 * shape); bcd 0x5292,alt runs its mar delays on both paths
 * (delays first, A untouched so order-equivalent) and loops to
 * L5292 on A < 0. L52AA zero-fill: A = 0; dst 0 to *AR1;
 * *AR3++ = 0 (stl); *AR5++ = 128 (st). L52AF: AR7++ (mar);
 * A = AR7-value; A -= 9633; A -= *(0x265C); A >= 0 stores 9633
 * to cell 0x245E and returns (bc ageq, st, ret). Else recompute
 * A from AR6 (ldm/sub/sub identical to L529F); A < 0 loops to
 * L5292 (bc alt); else joins L52AA (b). Single entry, no
 * live-ins (all ARs/A recomputed); memory outs via the AR
 * cursors and cell 0x245E; void.
 */
void frag_5282(void)
{
    long a;
    int *ar0 = (int *)12618;                         /* stm #12618,ar0 */
    int *ar1 = (int *)9396;                          /* stm #9396,ar1 */
    int *ar2 = (int *)12586;                         /* stm #12586,ar2 */
    int *ar3 = (int *)9364;                          /* stm #9364,ar3 */
    int *ar4 = (int *)12682;                         /* stm #12682,ar4 */
    int *ar5 = (int *)985;                           /* stm #985,ar5 */
    int *ar6 = (int *)12554;                         /* stm #12554,ar6 */
    int *ar7 = (int *)9633;                          /* stm #9633,ar7 */
l5292:
    a = (long)*ar7;                                  /* ld *ar7,a */
    a -= (long)*ar6;                                 /* sub *ar6,a */
    if (a < 0)                                       /* bc 0x52aa,alt */
        goto l52aa;
    ar6++;                                           /* mar *ar6+ */
    if (a != 0)                                      /* bc 0x529f,aneq */
        goto l529f;
    a = ((long)*ar0 << 16) |                         /* dld *ar0+,a (SXM=1 assumed) */
        ((unsigned)*(ar0 + 1) & 0xFFFF);
    ar0 += 2;
    *ar1++ = (int)((a >> 16) & 0xFFFF);              /* dst a,*ar1+ (high) */
    *ar1++ = (int)(a & 0xFFFF);                      /* dst (low) */
    /* bd 0x52af (always taken; both 1-word delays run) */
    *ar3++ = *ar2++;                                 /* mvdd *ar2+,*ar3+ (delay 1) */
    *ar5++ = *ar4++;                                 /* mvdd *ar4+,*ar5+ (delay 2) */
    goto l52af;
l529f:
    ar0 += 2;                                        /* mar *+ar0(0x2) */
    a = (long)(unsigned)ar6;                         /* ldm ar6,a (3273 precedent) */
    a -= 12554L;                                     /* sub #12554,a */
    a -= (long)*(volatile int *)0x31AA;              /* sub *(0x31aa),a */
    ar2++;                                           /* bcd delays (both paths) */
    ar4++;                                           /* mar *ar4+ */
    if (a < 0)                                       /* bcd 0x5292,alt */
        goto l5292;
l52aa:
    a = 0;                                           /* ld #0,a */
    *ar1++ = (int)((a >> 16) & 0xFFFF);              /* dst a,*ar1+ (high, 0) */
    *ar1++ = (int)(a & 0xFFFF);                      /* dst (low, 0) */
    *ar3++ = (int)(a & 0xFFFF);                      /* stl a,*ar3+ */
    *ar5++ = 128;                                    /* st #128,*ar5+ */
l52af:
    ar7++;                                           /* mar *ar7+ */
    a = (long)(unsigned)ar7;                         /* ldm ar7,a */
    a -= 9633L;                                      /* sub #9633,a */
    a -= (long)*(volatile int *)0x265C;              /* sub *(0x265c),a */
    if (a >= 0)                                      /* bc 0x52c0,ageq */
        goto l52c0;
    a = (long)(unsigned)ar6;                         /* ldm ar6,a */
    a -= 12554L;                                     /* sub #12554,a */
    a -= (long)*(volatile int *)0x31AA;              /* sub *(0x31aa),a */
    if (a < 0)                                       /* bc 0x5292,alt */
        goto l5292;
    goto l52aa;                                      /* b 0x52aa */
l52c0:
    *(volatile int *)0x245E = 9633;                  /* st #9633,*(0x245e) */
    /* ret */
}
