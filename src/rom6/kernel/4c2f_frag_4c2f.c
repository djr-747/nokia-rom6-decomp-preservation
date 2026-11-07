/* ROM6 0x4C2F FRAG_4C2F -- 6w.
 * Verified encoding: src/rom6/kernel/4c2f_frag_4c2f.asm (recombine MATCH).
 * ORIGIN 0x4C2F
 * EXPECT: F110 00D3 F84C 4C35 F073 0702
 *
 * Intent: Compare rung 211. Same shape: A-live-in - 211 nonzero to FRAG_4C35 (forward extern), equal to dark 0x702. Bound 4C2F-4C34.
 */
extern void frag_4C35(void);
extern void frag_0702(void);

void frag_4C2F(int a_live)
{
    if (a_live - 211 != 0) {                     /* sub; bc bneq */
        frag_4C35();                             /* next rung */
        return;
    }
    frag_0702();                                 /* b 0x702 tail */
}
