/* ROM6 0xCFAE FRAG_CFAE -- 15w.
 * Verified encoding: src/rom6/kernel/cfae_frag_cfae.asm (recombine MATCH).
 * ORIGIN 0xCFAE
 * EXPECT: EC2B 7092 0F10 7712 0C62 7713 0C6C EC09 7092 0F7E EC09 7093 0F7E 8A07 FC00
 *
 * Intent: Triple table fill plus status restore. 44 copies (rpt #43) of cell 0xF10 through live-in AR2 (mvkd); AR2 = 3170, AR3 = 3180; 10 copies (rpt #9) of cell 0xF7E through each (mvkd); ST1 restored (popm st1, hardware state, no C form); return.
 */
void frag_CFAE(int **ppar2)
{
    int i;
    int *ar2 = *ppar2;
    int *ar3;
    for (i = 0; i < 44; i++)                     /* rpt #43 */
        *ar2++ = *(volatile int *)0xF10;      /* mvkd 0xf10,*ar2+ */
    ar2 = (int *)3170;                           /* stm #3170,ar2 */
    ar3 = (int *)3180;                           /* stm #3180,ar3 */
    for (i = 0; i < 10; i++)                     /* rpt #9 */
        *ar2++ = *(volatile int *)0xF7E;      /* mvkd */
    for (i = 0; i < 10; i++)                     /* rpt #9 */
        *ar3++ = *(volatile int *)0xF7E;      /* mvkd */
    /* popm st1: ST1 restore (hardware state, no C form) */
    *ppar2 = ar2;
    /* ret */
}
