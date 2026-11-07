/* ROM6 0x4C3B FRAG_4C3B -- 6w.
 * Verified encoding: src/rom6/kernel/4c3b_frag_4c3b.asm (recombine MATCH).
 * ORIGIN 0x4C3B
 * EXPECT: F110 00DB F84C 4C41 F073 0706
 *
 * Intent: Compare rung 219. A-live-in - 219 nonzero to FRAG_4C41 (bc bneq: has .asm, no C yet, forward extern), equal to dark 0x706 (b, forward extern). Bound 4C3B-4C40.
 */
extern void frag_4C41(void);
extern void frag_0706(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void frag_4C3B(int a_live)
{
    if (a_live - 219 != 0) {                     /* sub; bc bneq */
        frag_4C41();                             /* next rung */
        return;
    }
    frag_0706();                                 /* b 0x706 tail */
}
