/* ROM6 0x86CF ROUTINE_86CF -- 22w.
 * Verified encoding: src/rom6/kernel/86cf_routine_86cf.asm (recombine MATCH).
 * ORIGIN 0x86CF
 * EXPECT: F071 004B 7308 3090 7712 11A8 EC07 7192 3090 1082 7712 309B 7710 0011 EC03 80B2 68F8 051E FEFF FC00
 *
 * Intent: Zero-fill plus strided store. A = 0 with 76 stores (rptz a,#75) to fixed cell 0x3099... 0x3090 (mvmd al); AR2 = 4520; 8 copies (rpt #7) of *AR2++ to cell 0x3090 (mvdk, last wins); A = *(4528); AR2 = 12443, AR0 = 17; 4 stores (rpt #3) of A stepping AR2 by AR0 (stl a,*ar2+0: AR0-step post-increment, distinct encoding from *ar2+; ti-c54x lookup inconclusive, flagged by-convention); clears bit 8 of cell 0x51E (andm -257); return.
 */
void routine_86CF(void)
{
    int i;
    int a = 0;
    int *ar2;
    for (i = 0; i < 76; i++)                     /* rptz a,#75 */
        *(volatile int *)0x3090 = a;         /* mvmd al,0x3090 */
    ar2 = (int *)4520;                           /* stm #4520,ar2 */
    for (i = 0; i < 8; i++)                      /* rpt #7 */
        *(volatile int *)0x3090 = *ar2++;     /* mvdk *ar2+,0x3090 */
    a = *ar2;                                    /* ld *ar2,a */
    ar2 = (int *)12443;                          /* stm #12443,ar2 */
    for (i = 0; i < 4; i++) {                    /* stm #17,ar0; rpt #3 */
        *ar2 = a;                                /* stl a,*ar2+0 */
        ar2 += 17;                               /* +0 = AR0 step */
    }
    *(volatile int *)0x51E &= -257;          /* andm #-257 */
    /* ret */
}
