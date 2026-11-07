/* ROM6 0xD8E3 SUB_D8E3 -- 17w.
 * Verified encoding: src/rom6/kernel/d8e3_sub_d8e3.asm (recombine MATCH).
 * ORIGIN 0xD8E3
 * EXPECT: 7669 3214 7712 0B6A F071 0099 8092 7712 0C0E EC09 8092 7712 0C04 EC09 7092 FB9C FE00
 *
 * Intent: Three-range clear plus copy. Cell 0x69 = 12820 (st, direct);
 * 154 zeroes at AR2 = 2922 (RPTZ zeroes A, RC = 153, 8A45 precedent);
 * 10 zeroes at 3086 (rpt #9); 10 copies of cell 0xFB9C at 3076
 * (rpt #9 + MVDD... MVKD source-absolute, 457f precedent for RPT +
 * multiword). A stays 0 throughout. The retd has no in-span delays;
 * the next span holds them (9B6F pattern, flagged). Bound D8E3-D8F3.
 */
void sub_D8E3(void)
{
    int *ar2;
    int i;
    *(volatile int *)0x69 = 12820;                   /* st #12820,0x69 */
    ar2 = (int *)2922;                               /* stm #2922,ar2 */
    for (i = 0; i < 154; i++)                        /* rptz a,#153 (A=0) */
        *ar2++ = 0;                                  /* stl a,*ar2+ */
    ar2 = (int *)3086;                               /* stm #3086,ar2 */
    for (i = 0; i < 10; i++)                         /* rpt #9 */
        *ar2++ = 0;                                  /* stl a,*ar2+ */
    ar2 = (int *)3076;                               /* stm #3076,ar2 */
    for (i = 0; i < 10; i++)                         /* rpt #9 */
        *ar2++ = *(volatile int *)0xFB9C;            /* mvdk 0xfb9c,*ar2+ */
    /* retd (delays in next span, always run there) */
}
