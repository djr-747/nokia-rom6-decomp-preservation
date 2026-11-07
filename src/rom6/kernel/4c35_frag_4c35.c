/* ROM6 0x4C35 FRAG_4C35 -- 6w.
 * Verified encoding: src/rom6/kernel/4c35_frag_4c35.asm (recombine MATCH).
 * ORIGIN 0x4C35
 * EXPECT: F110 00D9 F84C 4C3B F073 0704
 *
 * Intent: Compare rung 217. A-live-in - 217 nonzero to FRAG_4C3B (forward extern), equal to dark 0x704. Bound 4C35-4C3A.
 */
extern void frag_4C3B(void);
extern void frag_0704(void);

void frag_4C35(int a_live)
{
    if (a_live - 217 != 0) {                     /* sub; bc bneq */
        frag_4C3B();                             /* next rung */
        return;
    }
    frag_0704();                                 /* b 0x704 tail */
}
