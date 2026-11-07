/* ROM6 0x4238 FRAG_4238 -- 3w.
 * Verified encoding: src/rom6/kernel/4238_frag_4238.asm (recombine MATCH).
 * ORIGIN 0x4238
 * EXPECT: FE00 E554 E510
 *
 * Intent: Delayed-return double move. Both mvdd moves are retd delay slots (always run before the return completes): *AR2-- = *AR3-- then *AR2 = *AR3; AR2/AR3 modeled in-out; return. Bound 4238-423A.
 */
void frag_4238(int **ppar2, int **ppar3)
{
    int *ar2 = *ppar2;
    int *ar3 = *ppar3;
    /* retd delay slots (always run): */
    *ar2-- = *ar3--;                             /* mvdd *ar3-,*ar2- */
    *ar2 = *ar3;                                 /* mvdd *ar3,*ar2 */
    *ppar2 = ar2;
    *ppar3 = ar3;
    /* retd */
}
