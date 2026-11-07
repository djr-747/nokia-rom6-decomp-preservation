/* ROM6 0x3753 FRAG_3753 -- 11w.
 * Verified encoding: src/rom6/kernel/3753_frag_3753.asm (recombine MATCH).
 * ORIGIN 0x3753
 * EXPECT: 60F8 0008 000A F820 375E F981 AA2C F074 2E2F F073 2E64
 *
 * Intent: Dispatcher-clause arm 3. AL (cell 0x8 alias) != 10 tail-enters FRAG_375E (bc 0x375e,ntc, C: frag_375E). Else far call 0x1AA2C (extended address, modeled extern per b036), call dispatcher_entry_2E2F, tail-enter DISPATCH_MATCH_LOOP (b 0x2e64, forward extern). Same shape as FRAG_36F0 with #10. Bound 3753-375D.
 */
extern void frag_375E(void);
extern void far_1AA2C(void); /* XPC page, off-image; see docs/evidence/extern-triage.md */
extern void dispatcher_entry_2E2F(void);
extern void dispatch_match_loop(void);

void frag_3753(void)
{
    if (*(volatile int *)0x8 != 10) {            /* cmpm, bc ntc */
        frag_375E();                             /* tail call */
        return;
    }
    far_1AA2C();                                 /* fcall 0x1aa2c */
    dispatcher_entry_2E2F();                     /* call 0x2e2f */
    dispatch_match_loop();                       /* b 0x2e64 tail */
}
