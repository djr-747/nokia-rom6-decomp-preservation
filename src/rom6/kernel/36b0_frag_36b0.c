/* ROM6 0x36B0 FRAG_36B0 -- 18w.
 * Verified encoding: src/rom6/kernel/36b0_frag_36b0.asm (recombine MATCH).
 * ORIGIN 0x36B0
 * EXPECT: 7713 27E9 7693 000B 7693 0001 7714 009E 7713 27E9 7715 0004 F074 2C88 F074 2E2F F073 2E64
 *
 * Intent: Cell pair plus report. Writes cells 10217 = 11 and 10218 = 1 (stm/st pair, AR3 reloaded after); presets AR4/AR5 dead after (noted); calls ROUTINE_2C88 (dark, no .asm span, forward extern) then dispatcher_entry_2E2F; tail-enters DISPATCH_MATCH_LOOP (b 0x2e64, forward extern). Bound 36B0-36C1.
 */
extern void routine_2C88(void);
extern void dispatcher_entry_2E2F(void);
extern void dispatch_match_loop(void);

void frag_36B0(void)
{
    /* stm #10217,ar3 */
    *(volatile int *)10217 = 11;             /* st #11,*ar3+ */
    *(volatile int *)10218 = 1;              /* st #1,*ar3+ */
    /* stm #158,ar4; stm #10217,ar3; stm #4,ar5 (dead presets) */
    routine_2C88();                              /* call 0x2c88 */
    dispatcher_entry_2E2F();                     /* call 0x2e2f */
    dispatch_match_loop();                       /* b 0x2e64 tail */
}
