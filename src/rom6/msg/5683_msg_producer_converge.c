/* ROM6 0x5683 MSG_PRODUCER_CONVERGE_5683 -- 23w.
 * Verified encoding: src/rom6/msg/5683_msg_producer_converge.asm (recombine MATCH).
 * ORIGIN 0x5683
 * EXPECT: 69F8 2628 0001 10F8 264E F040 0001 F030 FFFB 60F8 2476 0006 F830 569A 60F8 2476 0007 F830 569C F040 0010 F073 569E
 *
 * Intent: Masked merge with three A-tails. Sets bit 0 of cell 0x2628; A = (cell 0x264E OR 1) AND -5 (or plus and); cell 0x2476 == 6 tail-enters 0x569A with A live (bc tc, C: frag_569A). Cell == 7 tail-enters dark 0x569C with A live (bc tc, forward extern with A arg). Else A |= 16, tail-enters 0x569E with A live (b, C: frag_569E). CMPM TC-on-equal per op_cmpm; BITF any-bit TC per op_bitf. 23w per .asm header (recombine MATCH).
 */
extern int frag_569A(int a_live);
extern void frag_569C(int a_live); /* joins 569a_msg_producer_converge interior @+0x2; see docs/evidence/extern-triage.md */
extern void frag_569E(int a_live);

void frag_5683(void)
{
    int a;
    *(volatile int *)0x2628 |= 1;            /* orm #1 */
    a = *(volatile int *)0x264E;             /* ld *(0x264e),a */
    a |= 1;                                      /* or #1,a */
    a &= -5;                                     /* and #-5,a */
    if (*(volatile int *)0x2476 == 6) {          /* cmpm, bc tc */
        frag_569A(a);                            /* tail call (A live) */
        return;
    }
    if (*(volatile int *)0x2476 == 7) {          /* cmpm, bc tc */
        frag_569C(a);                            /* tail, dark (A live) */
        return;
    }
    a |= 16;                                     /* or #16,a */
    frag_569E(a);                                /* b 0x569e tail */
}
