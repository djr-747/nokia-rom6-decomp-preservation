/* ROM6 0x3775 FRAG_3775 -- 4w.
 * Verified encoding: src/rom6/kernel/3775_frag_3775.asm (recombine MATCH).
 * ORIGIN 0x3775
 * EXPECT: F074 2E2F F073 2E64
 *
 * Intent: Dispatcher-clause tail. Calls dispatcher_entry_2E2F, tail-enters DISPATCH_MATCH_LOOP (b 0x2e64: has .asm, no C yet, forward extern per convention). Bound 3775-3778 (micro-arm).
 */
extern void dispatcher_entry_2E2F(void);
extern void dispatch_match_loop(void);

void frag_3775(void)
{
    dispatcher_entry_2E2F();                     /* call 0x2e2f */
    dispatch_match_loop();                       /* b 0x2e64 tail */
}
