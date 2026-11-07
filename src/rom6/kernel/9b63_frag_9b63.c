/* ROM6 0x9B63 FRAG_9B63 -- 4w.
 * Verified encoding: src/rom6/kernel/9b63_frag_9b63.asm (recombine MATCH).
 * ORIGIN 0x9B63
 * EXPECT: 1A81 FE00 6D8B 8091
 *
 * Intent: FRAG_9B63 OR-return micro (4w). A = A-live-in OR *AR1-entry; AR3-entry steps down and *AR1-entry++ = A low, both in the retd delay slots (always run, visible order per 4238); returns A (int out-channel).
 */
int frag_9B63(int a_live, int *par1, int *par3)
{
    int a = a_live | *par1;                        /* or *ar1,a */
    par3--;                                        /* mar *ar3- (slot) */
    *par1++ = a & 0xFFFF;                          /* stl a,*ar1+ (slot) */
    return a;                                      /* retd */
}
