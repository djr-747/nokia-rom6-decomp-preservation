/* ROM6 0x54BB MSG_PRODUCER_CONVERGE -- 2w STUB.
 * Verified encoding: src/rom6/kernel/54bb_msg_producer_converge.asm (recombine MATCH).
 * ORIGIN 0x54BB
 * EXPECT: F074 06E6
 *
 * Intent: Entry-call stub (the .asm captures only the head call; the J1+J convergence body per the header evidence has no .asm and stays dark). Head-calls dark SUB_06E6. Defines FRAG_54BB for the P-lane tails (5395/53BA/53D9/5420/544A/5489/5503).
 */
extern void sub_06E6(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void frag_54BB(void)
{
    sub_06E6();                                    /* call 0x6e6 */
}
