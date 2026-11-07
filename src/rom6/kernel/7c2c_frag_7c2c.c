/* ROM6 0x7C2C FRAG_7C2C -- 3w.
 * Verified encoding: src/rom6/kernel/7c2c_frag_7c2c.asm (recombine MATCH).
 * ORIGIN 0x7C2C
 * EXPECT: E801 F073 7BEE
 *
 * Intent: Constant-A tail. A = 1 threaded into dark 0x7BEE (b, forward extern with A arg per 54f8 precedent). Bound 7C2C-7C2E.
 */
extern void frag_7BEE(int a_live);

void frag_7C2C(void)
{
    frag_7BEE(1);                                /* ld #1,a; b 0x7bee */
}
