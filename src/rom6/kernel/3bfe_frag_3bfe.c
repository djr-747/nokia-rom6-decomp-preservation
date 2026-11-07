/* ROM6 0x3BFE FRAG_3BFE -- 2w.
 * Verified encoding: src/rom6/kernel/3bfe_frag_3bfe.asm (recombine MATCH).
 * ORIGIN 0x3BFE
 * EXPECT: F5BC FC00
 *
 * Intent: TC preset. Five branch entries from CMPM_GATE_CHAIN; sets TC=1, returns.
 */
void frag_3BFE(void)
{
    /* ssbx st0,tc: TC set (hardware state, no C form); ret */
}
