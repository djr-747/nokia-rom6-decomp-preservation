/* ROM6 0xDACF FRAG_DACF -- 3w.
 * Verified encoding: src/rom6/kernel/dacf_frag_dacf.asm (recombine MATCH).
 * ORIGIN 0xDACF
 * EXPECT: FE00 6B5E FFFF
 *
 * Intent: FRAG_DACF delayed-return decrement (3w, ROM slice verified: no listing row). Cell 0x5E decremented by 1 in the retd delay slot (always runs), then return.
 */
void frag_DACF(void)
{
    *(volatile int *)0x5E -= 1;                /* retd delay slot */
    /* retd: return */
}
