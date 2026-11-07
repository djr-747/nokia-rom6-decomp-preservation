/* ROM6 0xBA32 DELAY_UPDATE_BA32 -- 36w dual delay-line shuffle.
 * Verified encoding: src/rom6/kernel/ba32_delay_update_ba32.asm (recombine MATCH).
 * ORIGIN 0xBA32
 * EXPECT: E801 00F8 2AF1 E977 F587 891A 7712 2F18 7713 2FAE 7714 2799 F272 BA43 7715 2811 E58A E59B E802 00F8 2AF1 F010 0078 FC47 F000 FFFF 881A 7714 0F88 F272 BA54 7715 0FC4 E58A E59B FC00
 *
 * Intent: Two RPTBD block moves (hypothesis FIR delay update,
 * per asm header). A = 1 + (*(0x2AF1)<<16); B = min(A,119)
 * (min b, signed full-width per oracle op_compare); BRC =
 * low16(B); first block copies BRC+1 pairs *AR4++ = *AR2++
 * (12056 to 10137) and *AR5++ = *AR3++ (12206 to 10257).
 * Then A = 2 + (*(0x2AF1)<<16) - 120; if A <= 0 return
 * (rc aleq, immediate); else BRC = low16(A - 1) and the
 * second block copies BRC+1 pairs *AR4++ = *AR2++ (continued
 * AR2 to 3976) and *AR5++ = *AR3++ (continued AR3 to 4036).
 * RPTBD delays (the stm words) run once before each loop;
 * mvdd second operand is the destination (25F2 precedent);
 * ADD Smem shifts left 16 (no SXM dependence); STLM stores
 * low 16; cell 0x2AF1 image/RAM (dark, flagged). In
 * *(0x2AF1) (dark); out moved cells/ARs/BRC.
 * EXPECT from the image.
 */
void delay_update_BA32(void)
{
    long a;
    long b;
    int *ar2;
    int *ar3;
    int *ar4;
    int *ar5;
    int n;
    int i;

    a = 1;                                                   /* ld #1,a */
    a += (long)*(volatile int *)0x2AF1 << 16;                /* add *(0x2af1),a */
    b = 119;                                                 /* ld #119,b */
    if (a < b)                                               /* min b (oracle op_compare) */
        b = a;
    n = (int)(b & 0xFFFFL);                                  /* stlm b,brc */
    ar2 = (int *)12056;                                      /* stm #12056,ar2 */
    ar3 = (int *)12206;                                      /* stm #12206,ar3 */
    ar4 = (int *)10137;                                      /* stm #10137,ar4 */
    /* rptbd 0xba43: stm delay runs once, block runs n+1 times */
    ar5 = (int *)10257;                                      /* stm #10257,ar5 (delay) */
    for (i = 0; i < n + 1; i++) {
        *ar4++ = *ar2++;                                     /* mvdd *ar2+,*ar4+ */
        *ar5++ = *ar3++;                                     /* mvdd *ar3+,*ar5+ */
    }
    a = 2;                                                   /* ld #2,a */
    a += (long)*(volatile int *)0x2AF1 << 16;                /* add *(0x2af1),a */
    a -= 120;                                                /* sub #120,a */
    if (a <= 0)                                              /* rc aleq (immediate) */
        return;
    a += -1;                                                 /* add #-1,a */
    n = (int)(a & 0xFFFFL);                                  /* stlm a,brc */
    ar4 = (int *)3976;                                       /* stm #3976,ar4 */
    /* rptbd 0xba54: stm delay runs once, block runs n+1 times */
    ar5 = (int *)4036;                                       /* stm #4036,ar5 (delay) */
    for (i = 0; i < n + 1; i++) {
        *ar4++ = *ar2++;                                     /* mvdd *ar2+,*ar4+ */
        *ar5++ = *ar3++;                                     /* mvdd *ar3+,*ar5+ */
    }
    /* ret */
}
