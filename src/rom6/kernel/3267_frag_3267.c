/* ROM6 0x3267 FRAG_3267 -- 12w port-txn trampoline, one EXPECT.
 * Verified encoding: src/rom6/kernel/3267_frag_3267.asm (recombine MATCH).
 * ORIGIN 0x3267
 * EXPECT: 12D2 E90C F074 4007 80F8 0581 80F8 0582 F074 2E2F F073 2E64
 *
 * Intent: Unsigned-load port transaction into the dispatch loop.
 * Post-RET head after WORKER_3199 (thin: AR2 = source, AR4 rides entry).
 * A = *(AR2) unsigned (ldu *ar2+%: LDU zero-extends, no SXM; the
 * bit-reversed AR2 post-increment is unmodelable addressing -- AR2 is
 * dead after the load, so nothing is lost); B = 12; A = SUB_4007(A, 12)
 * (call 0x4007, C: sub_4007 per 3FC4; callee-A-out modeled, preserved-A
 * alternative trace-confirmable); cells 0x581/0x582 = A-low (stl pair);
 * runs DISPATCHER_ENTRY_2E2F (call 0x2e2f); tail-enters
 * DISPATCH_MATCH_LOOP (b 0x2e64, bare extern per 361C: B/AR2/AR4 ride
 * unmodeled). Bound 3267-3272.
 */
extern int sub_4007(int a_in, int b_in);
extern void dispatcher_entry_2E2F(void);
extern void dispatch_match_loop(void);

void frag_3267(int *par2)
{
    long a = (unsigned long)(unsigned)*par2;   /* ldu (bitrev+ unmod.) */

    a = (long)sub_4007((int)a, 12);                    /* call 0x4007 */
    *(volatile int *)0x581 = (int)(a & 0xFFFF);        /* stl a */
    *(volatile int *)0x582 = (int)(a & 0xFFFF);        /* stl a */
    dispatcher_entry_2E2F();                           /* call 0x2e2f */
    dispatch_match_loop();                             /* b 0x2e64 */
}
