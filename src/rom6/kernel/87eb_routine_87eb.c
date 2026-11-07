/* ROM6 0x87EB ROUTINE_87EB -- 40w FRCT MAC/min-max lane.
 * Verified encoding: src/rom6/kernel/87eb_routine_87eb.asm (recombine MATCH).
 * ORIGIN 0x87EB
 * EXPECT: F074 0590 F7B6 7711 B3C6 7713 B3B6 7714 B3D6 7715 B3BE 7716 11BA 771A 0007 F272 8810 7710 0008 E767 F02E 0002 EC03 6FB7 0C0E 6D96 3193 3F91 F360 0100 F777 F770 1094 F587 1095 F586 F520 8192 F6B6 FC00
 *
 * Intent: Calls sub_0590 (low-zone unsourced, flagged);
 * FRCT = 1 (ssbx, hardware; cleared at tail); AR1 = -19514,
 * AR3 = -19530, AR4 = -19498, AR5 = -19522, AR6 = 4538,
 * BRC = 7; AR0 = 8 (rptbd delay, unused, out flagged).
 * RPTBD block (8x; the mvmm delay-slot word is inside the
 * block, count-verified): AR7 = AR6 (mvmm, tracks); A =
 * 2<<14; 4x A += *(AR7)<<14 (rpt #3, +0 frozen); AR6++
 * (mar); B = *(AR3++) x A-high (mpya Smem, oracle
 * op_mpya_smem; FRCT = 1 known so the product doubles,
 * OVM flagged); B += *(AR1++)<<16; B += 256<<16; B >>= 9
 * then >>= 16 arithmetic (sfta, SXM-gated sign flagged);
 * A = *(AR4++); B = min(A,B) (signed full-width, oracle
 * op_compare); A = *(AR5++); B = max(A,B); B = B - A (sub
 * a,b, dst-minus-src per 2c8a precedent); *(AR2++) = B-low
 * (AR2 caller-live dark, flagged). FRCT cleared (rsbx);
 * return. LD sign-extension SXM dark flagged; ADD/MPYA OVM
 * flagged. In AR2/cells; out cells/ARs.
 * EXPECT from the image.
 */
void routine_87EB(void)
{
    long a;
    long b;
    int *ar1;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;
    int *ar4;
    int *ar5;
    int *ar6;
    int *ar7;
    int i;
    int j;

    sub_0590();                                              /* call 0x590 (low-zone, flagged) */
    /* ssbx st1,frct (FRCT = 1 known for the mpya below) */
    ar1 = (int *)-19514;                                     /* stm #-19514,ar1 */
    ar3 = (int *)-19530;                                     /* stm #-19530,ar3 */
    ar4 = (int *)-19498;                                     /* stm #-19498,ar4 */
    ar5 = (int *)-19522;                                     /* stm #-19522,ar5 */
    ar6 = (int *)4538;                                       /* stm #4538,ar6 */
    /* stm #7,brc; rptbd 0x8810: stm #8,ar0 delay runs once (unused, out flagged) */
    for (i = 0; i < 8; i++) {                                /* rptbd block x (BRC+1) */
        ar7 = ar6;                                           /* mvmm ar6,ar7 */
        a = 2L << 14;                                        /* ld #2,14,a */
        for (j = 0; j < 4; j++)                              /* rpt #3 (k+1) */
            a += (long)*ar7 << 14;                           /* add *ar7+0,14,a (OVM flagged) */
        ar6++;                                               /* mar *ar6+ */
        b = (long)*ar3++ * (long)(short)((a >> 16) & 0xFFFFL); /* mpya *ar3+ (B = Smem x A-high) */
        b = b << 1;                                          /* (FRCT = 1: product doubles) */
        b += (long)*ar1++ << 16;                             /* add *ar1+,16,b (OVM flagged) */
        b += 256L << 16;                                     /* add #256,16,b */
        b = b >> 9;                                          /* sfta b,-9 (SXM-gated, flagged) */
        b = b >> 16;                                         /* sfta b,-16 */
        a = (long)*ar4++;                                    /* ld *ar4+,a (SXM dark, flagged) */
        if (a < b)                                           /* min b (oracle op_compare) */
            b = a;
        a = (long)*ar5++;                                    /* ld *ar5+,a */
        if (a > b)                                           /* max b */
            b = a;
        b = b - a;                                           /* sub a,b */
        *ar2++ = (int)(b & 0xFFFFL);                         /* stl b,*ar2+ */
    }
    /* rsbx st1,frct (hardware, comment only) */
    /* ret */
}
