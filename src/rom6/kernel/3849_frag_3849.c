/* ROM6 0x3849 FRAG_3849 -- 7w.
 * Verified encoding: src/rom6/kernel/3849_frag_3849.asm (recombine MATCH).
 * ORIGIN 0x3849
 * EXPECT: 76F8 2202 0C1C F074 C851 F073 3850
 *
 * Intent: Cell preset 2 plus state step. Writes 3100 to cell 0x2202, runs STATE_WORKER 0xC851 (has .asm, no C yet, forward extern), tail-enters FRAG_3850 (b, forward extern). Bound 3849-384F.
 */
extern void state_worker_C851(void);
extern void frag_3850(void);

void frag_3849(void)
{
    *(volatile int *)0x2202 = 3100;          /* st #3100 */
    state_worker_C851();                              /* call 0xc851 */
    frag_3850();                                 /* b 0x3850 tail */
}
