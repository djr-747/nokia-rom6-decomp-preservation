/* ROM6 0xE5BA LEAF_E5BA -- 23w.
 * Verified encoding: src/rom6/kernel/e5ba_leaf_e5ba.asm (recombine MATCH).
 * ORIGIN 0xE5BA
 * EXPECT: E807 7711 09DA EC5B 8291 7691 6000 EC0D 8291 8091 7691 0014 7691 69CB 76F8 0A4A 0012 76F8 0A4B 0001 FE00 7699 FFFF
 *
 * Intent: Preset table writer. A = 7; AR1 = 2522; 92 stores of
 * A-high (= 0, A small, exact); store 24576; 14 stores of 0;
 * store A-low (7); stores 20, 27083; cells 0xA4A = 18, 0xA4B = 1;
 * the retd delay stores -1 at *(AR1 + 1) (ST #lk,*+AR1: AR1 update
 * dead at return, store address exact, flagged); return. All
 * words model straight-line stores (ST/STL/STH with small A,
 * exact). Bound E5BA-E5D0.
 */
void leaf_E5BA(void)
{
    int *ar1;
    long a = 7;
    int i;
    ar1 = (int *)2522;                               /* stm #2522,ar1 */
    for (i = 0; i < 92; i++)                         /* rpt #91 */
        *ar1++ = 0;                                  /* sth a,*ar1+ (A-high=0) */
    *ar1++ = 24576;                                  /* st #24576,*ar1+ */
    for (i = 0; i < 14; i++)                         /* rpt #13 */
        *ar1++ = 0;                                  /* sth a,*ar1+ */
    *ar1++ = (int)(a & 0xFFFF);                      /* stl a,*ar1+ */
    *ar1++ = 20;                                     /* st #20,*ar1+ */
    *ar1++ = 27083;                                  /* st #27083,*ar1+ */
    *(volatile int *)0xA4A = 18;                     /* st #18,*(0xa4a) */
    *(volatile int *)0xA4B = 1;                      /* st #1,*(0xa4b) */
    *(ar1 + 1) = -1;                                 /* retd delay: st #-1,*+ar1 */
    /* retd */
}
