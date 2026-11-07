/* ROM6 0xBA2A FRAG_BA2A -- 8w.
 * Verified encoding: src/rom6/kernel/ba2a_frag_ba2a.asm (recombine MATCH).
 * ORIGIN 0xBA2A
 * EXPECT: 6B04 0001 76F8 2ADC 0000 FE00 6881 0003
 *
 * Intent: FRAG_BA2A cell-bump delayed return (8w, ROM slice verified: no listing row). Cell 0x04 += 1; cell 0x2ADC = 0; *AR1-entry &= 3 in the retd delay slot (always runs); returns. A untouched, void.
 */
void frag_BA2A(int *par1)
{
    *(volatile int *)0x04 += 1;                /* addm */
    *(volatile int *)0x2ADC = 0;               /* st */
    *par1 &= 3;                                    /* retd delay slot */
    /* retd: return */
}
