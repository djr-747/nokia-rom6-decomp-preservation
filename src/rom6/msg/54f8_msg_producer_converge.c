/* ROM6 0x54F8 MSG_PRODUCER_CONVERGE_54F8 -- 11w.
 * Verified encoding: src/rom6/msg/54f8_msg_producer_converge.asm (recombine MATCH).
 * ORIGIN 0x54F8
 * EXPECT: 1082 F040 0100 61F8 2512 0100 F830 5502 F030 FEFF 8083
 *
 * Intent: Masked merge with live-A tail. A = *AR2-live-in OR 256; bit 8 of cell 0x2512 set tail-enters dark 0x5502 with A live (bc 0x5502,tc, forward extern with A arg per B-threading precedent). Else A &= -257 (clears bit 8), stored through live-in AR3; falls into the next convergence head. 11w per .asm header (no yaml bound entry; recombine MATCH).
 */
extern void frag_5502(int a_live);

void frag_54F8(int *par2, int *par3)
{
    int a = *par2 | 256;                        /* ld; or #256,a */
    if ((*(volatile int *)0x2512 & 256) != 0) {  /* bitf, bc tc */
        frag_5502(a);                            /* tail, dark (A live) */
        return;
    }
    a &= -257;                                   /* and #-257,a */
    *par3 = a;                                   /* stl a,*ar3 */
    /* falls through (no exit in span) */
}
