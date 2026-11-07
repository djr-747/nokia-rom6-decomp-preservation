/* ROM6 0xAF14 HEAD_AF14 -- 2w.
 * Verified encoding: src/rom6/kernel/af14_head_af14.asm (recombine MATCH).
 * ORIGIN 0xAF14
 * EXPECT: F074 059A
 *
 * Intent: Post-ret call head (follows aeec ret @AF13; entry
 * unconfirmed, no known callers, flagged). Head-calls dark 0x59A
 * (forward extern).
 */
extern void sub_059A(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void sub_AF14(void)
{
    sub_059A();                                        /* call 0x59a */
}
