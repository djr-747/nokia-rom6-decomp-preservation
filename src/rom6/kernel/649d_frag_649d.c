/* ROM6 0x649D FRAG_649D -- 3w.
 * Verified encoding: src/rom6/kernel/649d_frag_649d.asm (recombine MATCH).
 * ORIGIN 0x649D
 * EXPECT: 8185 F073 676A
 *
 * Intent: B store plus join. Stores B-live-in through live-in AR5; tail-enters 0x676A (b: BRANCH_TAIL_676A head, has .asm, no C yet, forward extern). EXPECT includes the shared branch-operand word at 0x649F (shared with the next head per 8AA5 precedent; single-word boundary overlap allowed). Bound 649D-649E per yaml (operand shared).
 */
extern void frag_676A(void);

void frag_649D(int b_live, int *par5)
{
    *par5 = b_live;                              /* stl b,*ar5 */
    frag_676A();                                 /* b 0x676a tail */
}
