/* ROM6 0xE59D LEAF_E59D -- 29w divide + dual-MAC lattice lane.
 * Verified encoding: src/rom6/kernel/e59d_leaf_e59d.asm (recombine MATCH).
 * ORIGIN 0xE59D
 * EXPECT: E735 8293 4808 9A9F F062 3FFF EC0E 1E82 8083 A518 208A 3562 F684 5066 3193 4808 9A1F 2093 3562 838B 490B 9B9F A55B 208D 3562 A493 FE00 3562 F642
 *
 * Intent: Nonrestoring divide (A = 16383 << 16, 15x SUBC
 * *AR2 via subc_step32) feeding a dual-MAC lattice tail.
 * AR5 snapshots AR3; shifted MSW stores bracket the divide
 * (sth a / sth a,15 -- store (A<<15)[31:16]); quotient AL
 * stored to *AR3; then the correlation chain: dual products
 * (mpy Xmem,Ymem per the e0a2 convention: dst = X*Y, no T,
 * no shift), T-form singles (dst = T*Smem), MACA folds of
 * *(0x62) per leg (B += T*mem; round per MACA flagged),
 * NEG + DADD (A += (mem(0x66) << 16) + AL: Xmem:src-lo
 * 32-bit addend per DADD syntax-1, flagged) + MPYA taps
 * with AL/MSW round-trip stores; tail re-fetches B from BL
 * with a <<15 store; final dual pair; return with MACA +
 * A = B << 2 in the delay slots. In AR2/AR3 (dark), A
 * live-in (dark); out A/B.
 * (Wave-13: converted to the established raw-deref style;
 * DADD/MACA notes per the oracle leaves.)
 */
extern long subc_step32(long b, int divisor);        /* SUBC placeholder (4348 precedent) */

void leaf_E59D(void)
{
    long a;  /* live-in (dark, flagged) */
    long b;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;  /* live-in (dark, flagged) */
    int *ar5;
    int t;  /* T live-in (dark, flagged) */
    int i;

    ar5 = ar3;                                                 /* mvmm ar3,ar5 */
    *ar3++ = (int)((a >> 16) & 0xFFFFL);                       /* sth a,*ar3+ */
    a &= 0xFFFFL;                                              /* ldm al,a */
    *ar3++ = (int)(((a << 15) >> 16) & 0xFFFFL);               /* sth a,15,*ar3+ */
    a = (long)16383 << 16;                                     /* ld #16383,16,a */
    for (i = 0; i < 15; i++)                                   /* rpt #14 */
        a = subc_step32(a, *ar2);                              /* subc *ar2,a */
    *ar3 = (int)(a & 0xFFFFL);                                 /* stl a,*ar3 */
    b = (long)*ar3 * (long)*ar2++;                            /* mpy *ar3,*ar2+,b (dual) */
    a = (long)t * (long)*ar2--;                               /* mpy *ar2-,a (T-form) */
    b += (long)t * (long)*(volatile int *)0x62;               /* maca 0x62,b (round flagged) */
    a = -b;                                                    /* neg b,a */
    a += ((long)*(volatile int *)0x66 << 16) + (a & 0xFFFFL); /* dadd 0x66,a (flagged) */
    a = (long)t * (long)*ar3++;                               /* mpya *ar3+ */
    a &= 0xFFFFL;                                              /* ldm al,a */
    *ar3 = (int)(((a << 15) >> 16) & 0xFFFFL);                 /* sth a,15,*ar3 */
    a = (long)t * (long)*ar3++;                               /* mpy *ar3+,a (T-form) */
    b += (long)t * (long)*(volatile int *)0x62;               /* maca 0x62,b */
    *ar3-- = (int)((b >> 16) & 0xFFFFL);                       /* sth b,*ar3- */
    b &= 0xFFFFL;                                              /* ldm bl,b */
    *ar3++ = (int)(((b << 15) >> 16) & 0xFFFFL);               /* sth b,15,*ar3+ */
    b = (long)*ar3-- * (long)*ar5++;                          /* mpy *ar3-,*ar5+,b (dual) */
    a = (long)t * (long)*ar5--;                               /* mpy *ar5-,a (T-form) */
    b += (long)t * (long)*(volatile int *)0x62;               /* maca 0x62,b */
    a = (long)*ar3++ * (long)*ar5;                            /* mpy *ar3+,*ar5,a (dual) */
    /* retd (delay words run, then return): */
    b += (long)t * (long)*(volatile int *)0x62;               /* maca 0x62,b */
    a = b << 2;                                                /* ld b,2,a */
    /* retd */
    (void)ar5;
}
