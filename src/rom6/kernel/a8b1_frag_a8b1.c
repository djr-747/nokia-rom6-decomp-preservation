/* ROM6 0xA8B1 FRAG_A8B1 -- 8w.
 * Verified encoding: src/rom6/kernel/a8b1_frag_a8b1.asm (recombine MATCH).
 * ORIGIN 0xA8B1
 * EXPECT: 10F8 051C F030 0001 FC45 10F8 3082 FC45
 *
 * Intent: Twin test with fall-through into A8B9. A = cell 0x51C AND 1; zero skips the 0x3082 load (rc aeq); A = 0 skips A8B9's first insn (rc aeq: the stm #9593,ar2) so AR2 stays live-in, else AR2 = 9593. Falls through (no exit in span) into A8B9's 9-fill, inlined here with the same bounds (duplicates frag_a8b9_zero's body, cited; C has no cross-function entry). Bound A8B1-A8B8, post-word FC00 per .asm header.
 */
void frag_A8B1(int **ppar2)
{
    int i;
    int a = *(volatile int *)0x51C & 1;         /* ld, and */
    int *ar2;
    if (a != 0)                                  /* rc aeq */
        a = *(volatile int *)0x3082;         /* ld */
    /* rc aeq: nonzero A runs A8B9's stm, zero skips it */
    ar2 = (a != 0) ? (int *)9593 : *ppar2;
    for (i = 0; i < 9; i++)                      /* A8B9 tail: rpt #8 */
        *ar2++ = 0;                              /* stl a,*ar2+ */
    *ppar2 = ar2;
    /* falls through (no ret in span) */
}
