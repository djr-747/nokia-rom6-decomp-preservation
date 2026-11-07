/* ROM6 0x43CD FRAG_43CD -- 6w.
 * Verified encoding: src/rom6/kernel/43cd_frag_43cd.asm (recombine MATCH).
 * ORIGIN 0x43CD
 * EXPECT: F074 2E2F E908 F074 4590 FC00
 *
 * Intent: Dispatcher plus call wrapper. Runs the 0x2E2F dispatcher entry, passes B = 8 to 0x4590, returns.
 */
extern void dispatcher_entry_2E2F(void);
extern void routine_4590(int b);

void frag_43CD(void)
{
    dispatcher_entry_2E2F();                    /* call 0x2e2f */
    routine_4590(8);                                 /* ld #8,b; call 0x4590 */
    /* ret */
}
