/* ROM6 0x7140 FRAG_7140 -- 2w.
 * Verified encoding: src/rom6/kernel/7140_frag_7140.asm (recombine MATCH).
 * ORIGIN 0x7140
 * EXPECT: F4BC FC00
 *
 * Intent: TC clear. Branch entry from FLAG_GATE_712D interior; clears TC=0, returns.
 */
void frag_7140(void)
{
    /* rsbx st0,tc: TC clear (hardware state, no C form); ret */
}
