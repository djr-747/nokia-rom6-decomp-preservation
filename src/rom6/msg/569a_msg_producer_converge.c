/* ROM6 0x569A MSG_PRODUCER_CONVERGE_569A -- 4w.
 * Verified encoding: src/rom6/msg/569a_msg_producer_converge.asm (recombine MATCH).
 * ORIGIN 0x569A
 * EXPECT: F040 0004 F040 0020
 *
 * Intent: Flag-OR pair with fall-through. A-live-in |= 4 then |= 32 (or pair); A returned (no exit in span, falls into the next convergence head with A live). 4w per .asm header (no yaml bound entry; recombine MATCH).
 */
int frag_569A(int a_live)
{
    int a = a_live | 4;                          /* or #4,a */
    a |= 32;                                     /* or #32,a */
    return a;                                    /* falls through, A live-out */
}
