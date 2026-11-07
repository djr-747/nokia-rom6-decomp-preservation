/* ROM6 0x44B2 FRAG_44B2 -- 11w.
 * Verified encoding: src/rom6/kernel/44b2_frag_44b2.asm (recombine MATCH).
 * ORIGIN 0x44B2
 * EXPECT: F074 0594 F074 2E2F 10F8 2F00 F030 00FF 80F8 054D FC00
 *
 * Intent: Dispatcher plus byte extract. Runs helpers 0x594 and the 0x2E2F dispatcher entry, takes the low byte of cell 0x2F00 into cell 0x54D, returns it.
 */
extern void helper_0594(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void dispatcher_entry_2E2F(void);

int frag_44B2(void)
{
    int a;
    helper_0594();                               /* call 0x594 */
    dispatcher_entry_2E2F();                    /* call 0x2e2f */
    a = *(volatile int *)0x2F00 & 255;       /* ld, and #255 */
    *(volatile int *)0x54D = a;              /* stl */
    return a;                                    /* ret */
}
