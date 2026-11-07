/* ROM6 0x965C FRAG_965C -- 3w.
 * Verified encoding: src/rom6/kernel/965c_frag_965c.asm (recombine MATCH).
 * ORIGIN 0x965C
 * EXPECT: E806 F073 9667
 *
 * Intent: FRAG_965C constant tail (3w). A = 6 (dead: overwritten by the callee path, noted); tail-enters unbound FRAG_9667 (b, has .asm, forward extern).
 */
extern void frag_9667(void);

void frag_965C(void)
{
    /* ld #6,a (A dead downstream, noted) */
    frag_9667();                                   /* b 0x9667 tail */
}
