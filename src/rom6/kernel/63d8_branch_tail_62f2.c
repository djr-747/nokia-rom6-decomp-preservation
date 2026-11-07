/* ROM6 0x63D8 BRANCH_TAIL_62F2 -- 2w.
 * Verified encoding: src/rom6/kernel/63d8_branch_tail_62f2.asm (recombine MATCH).
 * ORIGIN 0x63D8
 * EXPECT: 8097 8087
 *
 * Intent: Double store with fall-through. Stores A-live-in to *AR7-live-in post-incremented, then to *AR7 again (stl pair); no exit in span, falls into the next head. Bound per .asm header 2w (no yaml bound entry; recombine MATCH).
 */
void branch_tail_62F2(int a_live, int **ppar7)
{
    int *ar7 = *ppar7;
    *ar7++ = a_live;                             /* stl a,*ar7+ */
    *ar7 = a_live;                               /* stl a,*ar7 */
    *ppar7 = ar7;
    /* falls through (no exit in span) */
}
