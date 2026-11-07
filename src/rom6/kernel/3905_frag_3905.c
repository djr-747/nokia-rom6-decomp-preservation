/* ROM6 0x3906 FRAG_3905 -- 1w (overlap-corrected wave-12).
 * Verified encoding: src/rom6/kernel/3905_frag_3905.asm (recombine MATCH).
 * ORIGIN 0x3906
 * EXPECT: FC00
 *
 * Intent: Fall-through return of FRAG_38FB (its A live-out passes
 * through the return to the cc caller). Former leading bare word
 * 0x3905 re-homed to FRAG_38FB as the or #0,a operand.
 */
void frag_3905(void)
{
    /* ret */
}
