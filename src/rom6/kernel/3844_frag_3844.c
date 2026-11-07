/* ROM6 0x3844 FRAG_3844 -- 5w.
 * Verified encoding: src/rom6/kernel/3844_frag_3844.asm (recombine MATCH).
 * ORIGIN 0x3844
 * EXPECT: 76F8 2202 081C F073 3850
 *
 * Intent: Cell preset 1. Writes 2076 to cell 0x2202, tail-enters FRAG_3850 (b, forward extern). Bound 3844-3848.
 */
extern void frag_3850(void);

void frag_3844(void)
{
    *(volatile int *)0x2202 = 2076;          /* st #2076 */
    frag_3850();                                 /* b 0x3850 tail */
}
