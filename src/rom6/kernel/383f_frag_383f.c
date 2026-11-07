/* ROM6 0x383F FRAG_383F -- 5w.
 * Verified encoding: src/rom6/kernel/383f_frag_383f.asm (recombine MATCH).
 * ORIGIN 0x383F
 * EXPECT: 76F8 2202 0800 F073 3850
 *
 * Intent: Cell preset 0. Writes 2048 to cell 0x2202, tail-enters FRAG_3850 (b 0x3850: has .asm, no C yet, forward extern). Bound 383F-3843.
 */
extern void frag_3850(void);

void frag_383F(void)
{
    *(volatile int *)0x2202 = 2048;          /* st #2048 */
    frag_3850();                                 /* b 0x3850 tail */
}
