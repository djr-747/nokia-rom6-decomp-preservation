/* ROM6 0x87C3 FRAG_87C3 -- 4w.
 * Verified encoding: src/rom6/kernel/87c3_frag_87c3.asm (recombine MATCH).
 * ORIGIN 0x87C3
 * EXPECT: 76F8 3082 0001 FC00
 *
 * Intent: Cell preset. Six-way bc cond fan-in; sets cell 0x3082 = 1, returns.
 */
void frag_87C3(void)
{
    *(volatile int *)0x3082 = 1;             /* st #1,*(0x3082) */
    /* ret */
}
