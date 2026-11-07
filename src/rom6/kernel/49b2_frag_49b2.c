/* ROM6 0x49B2 FRAG_49B2 -- 4w.
 * Verified encoding: src/rom6/kernel/49b2_frag_49b2.asm (recombine MATCH).
 * ORIGIN 0x49B2
 * EXPECT: 81F8 2656 F073 4AD8
 *
 * Intent: B store plus join. Stores B-live-in to cell 0x2656; tail-enters FRAG_4AD8 (b 0x4ad8: has .asm with calad computed call, no C yet, forward extern). Bound 49B2-49B5.
 */
extern void frag_4AD8(void); /* joins 4ad8_frag_4ad8; see docs/evidence/extern-triage.md */

void frag_49B2(int b_live)
{
    *(volatile int *)0x2656 = b_live;        /* stl b,*(0x2656) */
    frag_4AD8();                                 /* b 0x4ad8 tail */
}
