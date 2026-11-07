/* ROM6 0x8655 TABLE_INIT_8655 -- 32w.
 * Verified encoding: src/rom6/kernel/8655_table_init_8655.asm (recombine MATCH).
 * ORIGIN 0x8655
 * EXPECT: 68F8 051E FFF8 7712 3025 EC18 7092 B373 771A 0002 F072 8663 EC10 7092 B37B 7712 119C EC07 7092 B373 F071 0003 8092 80F8 055A 7713 3025 F274 86E3 7714 118B FC00
 *
 * Intent: Table-init fill with nested repeat. Cell 0x51E &= -8 (andm); AR2 = 12325; 25x mvkd 0xB373
 * (rpt #24); BRC = 2; 3x rptb block of 17x mvkd 0xB37B (rpt #16); AR2 = 4508; 8x mvkd 0xB373 (rpt #7);
 * A = 0, 4x stl 0 (rptz a,#3); cell 0x55A = 0 (stl); AR3 = 12325; AR4 = 4491 (calld delay, runs first);
 * runs dark 0x86E3 (forward extern); return. Post-call head (prev 8653 call 592); no exterior callers,
 * entry unconfirmed, flagged.
 */
extern void sub_86E3(void); /* joins 86e3_sub_86e3; see docs/evidence/extern-triage.md */

void sub_8655(void)
{
    long a;
    int *ar2;
    int *ar3;
    int *ar4;
    int i;
    int j;


    *(volatile int *)0x51E &= -8;                          /* andm #-8,*(0x51e) */
    ar2 = (int *)12325;                                    /* stm #12325,ar2 */
    for (i = 0; i < 25; i++)                               /* rpt #24 */
        *ar2++ = 0xB373;                                    /* mvkd */
    /* stm #2,brc; rptb 0x8663 (3 iters) */
    for (i = 0; i < 3; i++)
        for (j = 0; j < 17; j++)                           /* rpt #16 */
            *ar2++ = 0xB37B;                                /* mvkd */
    ar2 = (int *)4508;                                     /* stm #4508,ar2 */
    for (i = 0; i < 8; i++)                                /* rpt #7 */
        *ar2++ = 0xB373;                                    /* mvkd */
    a = 0;                                                 /* rptz a,#3 */
    for (i = 0; i < 4; i++)
        *ar2++ = (int)a;                                   /* stl a,*ar2+ */
    *(volatile int *)0x55A = (int)a;                       /* stl a,*(0x55a) */
    ar3 = (int *)12325;                                    /* stm #12325,ar3 */
    ar4 = (int *)4491;                                     /* calld delay: stm (runs first) */
    sub_86E3();                                            /* calld 0x86e3 (dark) */
    /* ret @8674 */
    (void)ar3; (void)ar4;
}
