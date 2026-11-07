/* ROM6 0xB110 FRAG_B110 -- 12w.
 * Verified encoding: src/rom6/kernel/b110_frag_b110.asm (recombine MATCH).
 * ORIGIN 0xB110
 * EXPECT: 0984 F330 0003 F500 8912 FE45 F310 0005 FC4C 7712 0001 FC00
 *
 * Intent: fold live-in A/B plus *AR4 into a 2-bit index
 * (B = (B - *AR4) & 3 + A), post AR2 = B. Delayed conditional
 * return on zero (rcd aeq, exact skip semantics in the .asm):
 * the sub #5 delay slot always executes, then zero returns.
 * Surviving nonzero path: second gate (rc bneq on the post-sub
 * value) skips the AR2 = 1 preset, else sets it. Return.
 */
int frag_B110(int a_in, int b_in, int *par4, int **ppar2)
{
    int b = ((b_in - *par4) & 3) + a_in;       /* sub, and #3, add a,b */
    int b_pre = b;
    *ppar2 = (int *)b;                           /* stlm b,ar2 */
    b -= 5;                                      /* rcd delay slot: always */
    if (b_pre == 0)                              /* rcd aeq taken */
        return b;
    if (b != 0)                                  /* rc bneq */
        return b;
    *ppar2 = (int *)1;                           /* stm #1,ar2 */
    return b;                                    /* ret */
}
