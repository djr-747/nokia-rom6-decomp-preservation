/* ROM6 0x8F97 ROUTINE_8F97 -- 23w (E5BA twin).
 * Verified encoding: src/rom6/kernel/8f97_routine_8f97.asm (recombine MATCH).
 * ORIGIN 0x8F97
 * EXPECT: E807 7711 09DA EC5B 8291 7691 6000 7691 C000 7691 1000 EC0B 8291 8091 7691 0014 7691 7A12 7691 0028 FE00 7691 FFFF
 *
 * Intent: Preset table writer, second copy. A = 7; AR1 = 2522;
 * 92 stores of A-high (= 0, A small, exact); stores 24576,
 * -16384, 4096; 12 stores of 0; store A-low (7); stores 20,
 * 31250, 40; the retd delay stores -1 at *(AR1 + 1) (ST #lk,*+AR1:
 * AR1 update dead at return, store address exact, flagged);
 * return. E5BA twin with different constants. Bound 8F97-8FAD.
 */
void routine_8F97(void)
{
    int *ar1;
    long a = 7;
    int i;
    ar1 = (int *)2522;                               /* stm #2522,ar1 */
    for (i = 0; i < 92; i++)                         /* rpt #91 */
        *ar1++ = 0;                                  /* sth a,*ar1+ (A-high=0) */
    *ar1++ = 24576;                                  /* st #24576,*ar1+ */
    *ar1++ = -16384;                                 /* st #-16384,*ar1+ */
    *ar1++ = 4096;                                   /* st #4096,*ar1+ */
    for (i = 0; i < 12; i++)                         /* rpt #11 */
        *ar1++ = 0;                                  /* sth a,*ar1+ */
    *ar1++ = (int)(a & 0xFFFF);                      /* stl a,*ar1+ */
    *ar1++ = 20;                                     /* st #20,*ar1+ */
    *ar1++ = 31250;                                  /* st #31250,*ar1+ */
    *ar1++ = 40;                                     /* st #40,*ar1+ */
    *(ar1 + 1) = -1;                                 /* retd delay: st #-1,*+ar1 */
    /* retd */
}
