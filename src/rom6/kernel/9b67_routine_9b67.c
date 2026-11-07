/* ROM6 0x9B67 ROUTINE_9B67 -- 8w.
 * Verified encoding: src/rom6/kernel/9b67_routine_9b67.asm (recombine MATCH).
 * ORIGIN 0x9B67
 * EXPECT: 6C84 9B6F 6F82 0D58 6D94 FE00 F330 00FF
 *
 * Intent: Shift-branch leaf. BANZ to FRAG_9B6F when AR4 != 0, else
 * B = *AR2 >> 8 arithmetic, AR4++, B &= 255 (retd delay), far return.
 * BANZ Sind is *ar4 plain (MOD0 observe per ti-c54x
 * op_branch_sind_common: taken = (AR != 0), NO decrement, no writeback;
 * contrasts with the 454f *ar6- postdecrement form). LD shift -8 is
 * arithmetic per the 457f precedent (SXM = 1 assumed, flagged).
 * AR4 is tested as an address value (pointer-compare); both ARs caller-live.
 * Bound 9B67-9B6E.
 */
extern int frag_9B6F(int **ppar2, int **ppar4);

int routine_9B67(int **ppar2, int **ppar4)
{
    int b;
    if (*ppar4 != (int *)0)                          /* banz 0x9b6f,*ar4 */
        return frag_9B6F(ppar2, ppar4);
    b = (**ppar2 >> 8);                              /* ld *ar2,-8,b */
    (*ppar4)++;                                      /* mar *ar4+ */
    b &= 255;                                        /* retd delay: and (always runs) */
    return b;                                        /* retd */
}
