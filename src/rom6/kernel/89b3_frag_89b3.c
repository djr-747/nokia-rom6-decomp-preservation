/* ROM6 0x89B3 FRAG_89B3 -- 17w.
 * Verified encoding: src/rom6/kernel/89b3_frag_89b3.asm (recombine MATCH).
 * ORIGIN 0x89B3
 * EXPECT: 76F8 055A 0006 7712 3090 EC18 7092 B373 771A 0002 F072 89C1 EC10 7092 B37B F073 8894
 *
 * Intent: Table-copy fanout with nested repeat. Cell 0x55A = 6;
 * AR2 = 12432; 25 copies of cell 0xB373 (rpt #24 + MVKD, 457f
 * precedent for RPT + multiword MVKD); then 3 outer passes (BRC = 2,
 * rptb 0x89C1, RSA = PC + 2 non-delayed form) each copying cell
 * 0xB37B 17 times (inner rpt #16; RPT-inside-RPTB modeled per TI
 * repeat semantics, flagged). AR2 advances 76 total. Tail-branches to
 * 0x8894 (frag_8894: has .asm, no C yet; AR2 live-in unbound, flagged).
 * Bound 89B3-89C3.
 */
extern void frag_8894(void); /* joins 8894_frag_8894; see docs/evidence/extern-triage.md */

void frag_89B3(void)
{
    int *ar2;
    int i;
    int j;
    *(volatile int *)0x55A = 6;                      /* st #6,*(0x55a) */
    ar2 = (int *)12432;                              /* stm #12432,ar2 */
    for (i = 0; i < 25; i++)                         /* rpt #24 */
        *ar2++ = *(volatile int *)0xB373;            /* mvdk 0xb373,*ar2+ */
    for (i = 0; i < 3; i++)                          /* stm #2,brc; rptb 0x89c1 */
        for (j = 0; j < 17; j++)                     /* rpt #16 */
            *ar2++ = *(volatile int *)0xB37B;        /* mvdk 0xb37b,*ar2+ */
    /* AR2 = 12432 + 76 live into 0x8894 (no C binding yet, flagged) */
    frag_8894();                                      /* b 0x8894 */
}
