/* ROM6 0x3D3B FRAG_3D3B -- 2w.
 * Verified encoding: src/rom6/kernel/3d3b_frag_3d3b.asm (recombine MATCH).
 * ORIGIN 0x3D3B
 * EXPECT: F074 063A
 *
 * Intent: FRAG_3D3B entry-call stub (2w). Head-calls dark SUB_063A. Remainder dark.
 */
extern void sub_063A(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void frag_3D3B(void)
{
    sub_063A();                                    /* call 0x63a */
}
