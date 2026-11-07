/* ROM6 0xDD99 ABS_ACCUM_DD77 -- 2w shifted accumulate, one EXPECT.
 * Verified encoding: src/rom6/kernel/dd99_abs_accum_dd77.asm (recombine MATCH).
 * ORIGIN 0xDD99
 * EXPECT: 6F82 0C1E
 *
 * Intent: A += *(AR2) >> 2 (add *ar2,-2,a: ADD Xmem with signed SHIFT
 * -2 = SXM-ruled right shift by 2, same family as op_add_xmem; SXM = 1
 * assumed, flagged). A and AR2 ride in from entry; A-out is the sum.
 * Called via F074 @D183 (per .asm header). Bound DD99-DD9A (the span is
 * the RETD @DD98 delay pair; A-out continues into DC43... DD9B
 * exterior).
 */
long abs_accum_DD77(int *par2, long a_live)
{
    return a_live + ((long)*par2 >> 2);   /* add *ar2,-2,a (SXM?) */
}
