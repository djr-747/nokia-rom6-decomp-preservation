/* ROM6 0x99FF FRAG_99FF -- 18w.
 * Verified encoding: src/rom6/kernel/99ff_frag_99ff.asm (recombine MATCH).
 * ORIGIN 0x99FF
 * EXPECT: E712 6BF8 20FE FFFF 12D2 8813 12D2 13D2 8915 1382 F3F8 F330 00FF 8911 4915 F310 0001 FC00
 *
 * Intent: Cursor unpack head. AR2 = AR1-value (mvmm); cell0x20FE--;
 * three unsigned loads with AR2 += AR0-live per tap (ldu +0%,
 * circular wrap needs caller-live BK, linear modeled flagged):
 * AR3 = A-low, then A, then B = A, AR5 = B-low; B = *AR2 (no step);
 * B >>= 8 logical then &= 255 (sftl per 381b + AND imm zero-ext);
 * AR1 = B-low; B = AR5-value - 1; return. A/B/ARs all dead at
 * return (no store survives except the cell decrement, flagged).
 * Bound 99FF-9A10.
 */
void frag_99FF(int ar1_live, int ar0_live)
{
    int *ar2;
    long a;
    long b;
    int ar3;
    int ar5;
    int ar1;
    ar2 = (int *)ar1_live;                           /* mvmm ar1,ar2 */
    *(volatile int *)0x20FE -= 1;                    /* addm #-1,*(0x20fe) */
    a = (unsigned long)(unsigned)*ar2;               /* ldu *ar2+%,a */
    ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    ar3 = (int)(a & 0xFFFF);                         /* stlm a,ar3 */
    a = (unsigned long)(unsigned)*ar2;               /* ldu *ar2+%,a */
    ar2 += ar0_live;
    b = (unsigned long)(unsigned)*ar2;               /* ldu *ar2+%,b */
    ar2 += ar0_live;
    ar5 = (int)(b & 0xFFFF);                         /* stlm b,ar5 */
    b = (unsigned long)(unsigned)*ar2;               /* ldu *ar2,b */
    b = (unsigned long)b >> 8;                       /* sftl b,-8 (logical) */
    b &= 255;                                        /* and #255,b */
    ar1 = (int)(b & 0xFFFF);                         /* stlm b,ar1 */
    b = (long)ar5;                                   /* ldm ar5,b */
    b -= 1;                                          /* sub #1,b */
    /* ret (only the cell decrement persists; flagged) */
    (void)a; (void)b; (void)ar1; (void)ar3; (void)ar5;
}
