/* ROM6 0x6928 FRAG_6928 -- 4w.
 * Verified encoding: src/rom6/kernel/6928_frag_6928.asm (recombine MATCH).
 * ORIGIN 0x6928
 * EXPECT: 76F8 0545 0001 FC00
 *
 * Intent: Cell preset. Three bc entries from SUB_68CA span; sets cell 0x545 = 1, returns.
 */
void frag_6928(void)
{
    *(volatile int *)0x545 = 1;              /* st #1,*(0x545) */
    /* ret */
}
