/* ROM6 0x2D8B FRAG_2D8B -- 4w.
 * Verified encoding: src/rom6/boot/2d8b_frag_2d8b.asm (recombine MATCH).
 * ORIGIN 0x2D8B
 * EXPECT: E911 F074 4590 FC00
 *
 * Intent: ISR-tail call wrapper. Abuts ISR_2D5E tail; passes B = 17 to 0x4590, returns.
 */
extern void routine_4590(int b);

void frag_2D8B(void)
{
    routine_4590(17);                            /* ld #17,b; call 0x4590 */
    /* ret */
}
