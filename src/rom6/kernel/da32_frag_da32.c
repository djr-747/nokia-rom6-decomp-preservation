/* ROM6 0xDA32 FRAG_DA32 -- 3w.
 * Verified encoding: src/rom6/kernel/da32_frag_da32.asm (recombine MATCH).
 * ORIGIN 0xDA32
 * EXPECT: FE00 765A 0010
 *
 * Intent: FRAG_DA32 delayed-return store (3w, ROM slice verified: no listing row). Cell 0x5A = 16 in the retd delay slot (always runs), then return.
 */
void frag_DA32(void)
{
    *(volatile int *)0x5A = 16;                /* retd delay slot */
    /* retd: return */
}
