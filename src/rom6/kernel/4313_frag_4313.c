/* ROM6 0x4313 FRAG_4313 -- 2w.
 * Verified encoding: src/rom6/kernel/4313_frag_4313.asm (recombine MATCH).
 * ORIGIN 0x4313
 * EXPECT: E800 FC00
 *
 * Intent: return constant 0 (ld #0,a / ret). Leaf used where a zero
 * accumulator result feeds the caller.
 */
int frag_4313_zero(void)
{
    return 0;                             /* ld #0,a / ret */
}
