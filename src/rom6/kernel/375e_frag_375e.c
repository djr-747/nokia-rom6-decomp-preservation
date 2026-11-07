/* ROM6 0x375E FRAG_375E -- 23w.
 * Verified encoding: src/rom6/kernel/375e_frag_375e.asm (recombine MATCH).
 * ORIGIN 0x375E
 * EXPECT: 60F8 0008 0014 F820 3775 F074 2E2F 7713 27E9 7714 009E 7715 0004 7693 0015 7693 0012 7713 27E9 F074 2C88 F073 2E64
 *
 * Intent: Dispatcher-clause arm 2. AL != 20 tail-enters FRAG_3775 (bc 0x3775,ntc: has .asm, no C yet, forward extern). Else calls dispatcher_entry_2E2F, writes cells 10217 = 21 and 10218 = 18 (stm/st pair, AR3 reloaded after), calls ROUTINE_2C88 (no C binding yet, forward extern), tail-enters DISPATCH_MATCH_LOOP (b 0x2e64, forward extern). Bound 375E-3774.
 */
extern void frag_3775(void);
extern void dispatcher_entry_2E2F(void);
extern void routine_2C88(void); /* joins 2c88_ring_report_gate; see docs/evidence/extern-triage.md */
extern void dispatch_match_loop(void);

void frag_375E(void)
{
    if (*(volatile int *)0x8 != 20) {            /* cmpm, bc ntc */
        frag_3775();                             /* tail, unbound C */
        return;
    }
    dispatcher_entry_2E2F();                     /* call 0x2e2f */
    /* stm #10217,ar3; stm #158,ar4; stm #4,ar5 (ar4/ar5 unused) */
    *(volatile int *)10217 = 21;             /* st #21,*ar3+ */
    *(volatile int *)10218 = 18;             /* st #18,*ar3+ */
    /* stm #10217,ar3 (reload, unused) */
    routine_2C88();                              /* call 0x2c88 */
    dispatch_match_loop();                       /* b 0x2e64 tail */
}
