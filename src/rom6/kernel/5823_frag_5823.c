/* ROM6 0x5823 FRAG_5823 -- 2w.
 * Verified encoding: src/rom6/kernel/5823_frag_5823.asm (recombine MATCH).
 * ORIGIN 0x5823
 * EXPECT: F5BC FC00
 *
 * Intent: TC preset residual ahead of SUB_5825 head. Sets TC=1, returns; HYPOTHESIS fragment.
 */
void frag_5823(void)
{
    /* ssbx st0,tc: TC set (hardware state, no C form); ret */
}
