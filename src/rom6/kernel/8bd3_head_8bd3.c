/* ROM6 0x8BD3 HEAD_8BD3 -- 2w.
 * Verified encoding: src/rom6/kernel/8bd3_head_8bd3.asm (recombine MATCH).
 * ORIGIN 0x8BD3
 * EXPECT: F074 05B2
 *
 * Intent: Post-retd call head (follows 8b9d's retd delays; entry
 * unconfirmed, no known callers, flagged). Head-calls SUB_05B2
 * (forward extern, 36fb precedent).
 */
extern void sub_05B2(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void sub_8BD3(void)
{
    sub_05B2();                                        /* call 0x5b2 */
}
