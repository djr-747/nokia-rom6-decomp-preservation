/* ROM6 0x45FA FRAG_45FA -- 5w.
 * Verified encoding: src/rom6/kernel/45fa_frag_45fa.asm (recombine MATCH).
 * ORIGIN 0x45FA
 * EXPECT: F074 06F4 F074 2E2F FC00
 *
 * Intent: Dispatcher-entry wrapper. Runs helper 0x6F4, then the 0x2E2F dispatcher entry, returns.
 */
extern void helper_06F4(void);
extern void dispatcher_entry_2E2F(void);

void frag_45FA(void)
{
    helper_06F4();                               /* call 0x6f4 */
    dispatcher_entry_2E2F();                    /* call 0x2e2f */
    /* ret */
}
