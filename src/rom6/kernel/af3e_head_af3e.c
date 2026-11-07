/* ROM6 0xAF3E HEAD_AF3E -- 2w.
 * Verified encoding: src/rom6/kernel/af3e_head_af3e.asm (recombine MATCH).
 * ORIGIN 0xAF3E
 * EXPECT: F074 059A
 *
 * Intent: Post-ret call head (follows af16 ret @AF3D; entry
 * unconfirmed, no known callers, flagged). Head-calls dark 0x59A
 * (forward extern). Shape-twin of HEAD_AF14.
 */
extern void sub_059A(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void sub_AF3E(void)
{
    sub_059A();                                        /* call 0x59a */
}
