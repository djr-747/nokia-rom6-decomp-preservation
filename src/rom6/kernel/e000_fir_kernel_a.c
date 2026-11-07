/* ROM6 0xE000 FIR_KERNEL_A -- 42w dual-MAC FIR kernel.
 * Verified encoding: src/rom6/kernel/e000_fir_kernel_a.asm (recombine MATCH).
 * ORIGIN 0xE000
 * EXPECT: 7662 8000 7714 0C4B 7715 FEFA E726 F272 E028 7713 0C49 A463 A52B 3563 A453 B39B 3563 B38B B38B B383 F763 8384 4294 9A2F 0962 8396 A547 B347 B387 A463 B3A7 3563 A453 B313 3563 F763 8383 4293 9A1F 0962 8396 FC00
 *
 * Intent: *(0x62) = -32768; AR4 = 3147, AR5 = -262, AR6 =
 * AR2-entry (dark); AR3 = 3145 (rptbd delay, runs once).
 * RPTBD block (BRC caller-live dark, flagged; exact
 * BRC+1 incl. wrap): dual-MAC FIR section A with
 * coefficient/data ARs stepping net AR2 +2/pass (AR3/AR4/AR5
 * net zero, AR6 +2): A = *(AR4--) x *(AR5) (mpy dual, FRCT
 * doubling dark, flagged); B = *(AR4) x *(AR5++) (mpy
 * dual); B += *(0x63) x A-high, T = *(0x63) (maca, oracle
 * op_maca_smem); A = *(AR3--) x *(AR5); B += *(AR3++) x
 * *(AR5++); B += *(0x63) x A-high; B += *(AR2++) x *(AR5++)
 * twice; B += *(AR2++) x *(AR5); B <<= 3 (sfta, OVM
 * flagged); *(AR4) = B-high (sth, ASM dark); A =
 * (B - *(AR4++))<<16 (sub 4-op, dd77 precedent); *(AR4) =
 * bits 31-16 of A<<15 (sth 15, 25F2 precedent); B -=
 * *(0x62)<<16 (bias); *(AR6++) = B-high; mirror section on
 * the - side (mpy/mac with AR2-/AR5- preprint, A =
 * *(AR4--) x *(AR5), B += *(AR4++) x *(AR5-), maca,
 * A = *(AR3--) x *(AR5), B += *(AR3) x *(AR5), maca);
 * B <<= 3; *(AR3) = B-high; A = (B - *(AR3++))<<16;
 * *(AR3) = bits 31-16 of A<<15; B -= *(0x62)<<16;
 * *(AR6++) = B-high; repeat. SXM/OVM/FRCT/ASM dark
 * flagged; dual products signed 16x16 (oracle op_multiply).
 * A/B entry dead; out cells/ARs/T.
 * EXPECT from the image.
 */
void fir_kernel_A_E000(void)
{
    long a;
    long b;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;
    int *ar4;
    int *ar5;
    int *ar6;
    int t;
    int brc;  /* live-in (dark, flagged) */
    int i;

    *(volatile int *)0x62 = -32768;                              /* st #-32768,0x62 */
    ar4 = (int *)3147;                                          /* stm #3147,ar4 */
    ar5 = (int *)-262;                                          /* stm #-262,ar5 */
    ar6 = ar2;                                                  /* mvmm ar2,ar6 */
    /* rptbd 0xe028: stm #3145,ar3 delay runs once */
    ar3 = (int *)3145;
    for (i = 0; i <= (unsigned)brc; i++) {                      /* (BRC+1 incl. wrap; BRC dark) */
        a = (long)*ar4-- * (long)*ar5;                          /* mpy *ar4-,*ar5,a (FRCT dark) */
        b = (long)*ar4 * (long)*ar5++;                          /* mpy *ar4,*ar5+,b */
        t = *(volatile int *)0x63;                              /* maca 0x63,b (T = Smem) */
        b += (long)t * (long)(short)((a >> 16) & 0xFFFFL);     /* (B += T x A-high) */
        a = (long)*ar3-- * (long)*ar5;                          /* mpy *ar3-,*ar5,a */
        b += (long)*ar3++ * (long)*ar5++;                       /* mac *ar3+,*ar5+,b */
        t = *(volatile int *)0x63;                              /* maca 0x63,b */
        b += (long)t * (long)(short)((a >> 16) & 0xFFFFL);
        b += (long)*ar2++ * (long)*ar5++;                       /* mac *ar2+,*ar5+,b */
        b += (long)*ar2++ * (long)*ar5++;                       /* mac *ar2+,*ar5+,b */
        b += (long)*ar2++ * (long)*ar5;                         /* mac *ar2+,*ar5,b */
        b = b << 3;                                             /* sfta b,3 (OVM flagged) */
        *ar4 = (int)((b >> 16) & 0xFFFFL);                      /* sth b,*ar4 (ASM dark) */
        a = (b - (long)*ar4++) << 16;                           /* sub *ar4+,16,b,a */
        *ar4 = (int)(((a << 15) >> 16) & 0xFFFFL);              /* sth a,15,*ar4 */
        b -= (long)*(volatile int *)0x62 << 16;                 /* sub 0x62,b */
        *ar6++ = (int)((b >> 16) & 0xFFFFL);                    /* sth b,*ar6+ */
        b = (long)*ar2-- * (long)*ar5--;                        /* mpy *ar2-,*ar5-,b */
        b += (long)*ar2-- * (long)*ar5--;                       /* mac *ar2-,*ar5-,b */
        b += (long)*ar2++ * (long)*ar5--;                       /* mac *ar2+,*ar5-,b */
        a = (long)*ar4-- * (long)*ar5;                          /* mpy *ar4-,*ar5,a */
        b += (long)*ar4++ * (long)*ar5--;                       /* mac *ar4+,*ar5-,b */
        t = *(volatile int *)0x63;                              /* maca 0x63,b */
        b += (long)t * (long)(short)((a >> 16) & 0xFFFFL);
        a = (long)*ar3-- * (long)*ar5;                          /* mpy *ar3-,*ar5,a */
        b += (long)*ar3 * (long)*ar5;                           /* mac *ar3,*ar5,b */
        t = *(volatile int *)0x63;                              /* maca 0x63,b */
        b += (long)t * (long)(short)((a >> 16) & 0xFFFFL);
        b = b << 3;                                             /* sfta b,3 */
        *ar3 = (int)((b >> 16) & 0xFFFFL);                      /* sth b,*ar3 */
        a = (b - (long)*ar3++) << 16;                           /* sub *ar3+,16,b,a */
        *ar3 = (int)(((a << 15) >> 16) & 0xFFFFL);              /* sth a,15,*ar3 */
        b -= (long)*(volatile int *)0x62 << 16;                 /* sub 0x62,b */
        *ar6++ = (int)((b >> 16) & 0xFFFFL);                    /* sth b,*ar6+ */
    }
    /* ret */
    (void)t;
}
