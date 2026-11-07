/* ROM6 0x4C29 FRAG_4C29 -- 6w.
 * Verified encoding: src/rom6/kernel/4c29_frag_4c29.asm (recombine MATCH).
 * ORIGIN 0x4C29
 * EXPECT: F110 00D5 F84C 4C2F F073 0700
 *
 * Intent: Compare rung 213. B = A-live-in - 213 (sub #213,a,b per op_sub: dst = src minus operand); nonzero jumps to FRAG_4C2F (bc 0x4c2f,bneq: has .asm, no C yet, forward extern); equal tail-enters dark 0x700 (b, forward extern). B dead after (noted). Bound 4C29-4C2E.
 */
extern void frag_4C2F(void);
extern void frag_0700(void);

void frag_4C29(int a_live)
{
    /* sub #213,a,b (B dead after) */
    if (a_live - 213 != 0) {                     /* bc 0x4c2f,bneq */
        frag_4C2F();                             /* next rung */
        return;
    }
    frag_0700();                                 /* b 0x700 tail */
}
