/* ROM6 0x2EC6 FRAG_2EC6 -- 7w.
 * Verified encoding: src/rom6/boot/2ec6_frag_2ec6.asm (recombine MATCH).
 * ORIGIN 0x2EC6
 * EXPECT: E909 F074 2E2F F074 4590 F073 2E64
 *
 * Intent: Constant-B call chain. B = 9 threaded through dispatcher_entry_2E2F into routine_4590 (C: routine_4590(int), B preserved across the dispatcher call per callee-preservation assumption, documented); tail-enters DISPATCH_MATCH_LOOP (b 0x2e64, forward extern). Bound 2EC6-2ECC.
 */
extern void dispatcher_entry_2E2F(void);
extern void routine_4590(int b_in);
extern void dispatch_match_loop(void);

void frag_2EC6(void)
{
    int b = 9;                                   /* ld #9,b */
    dispatcher_entry_2E2F();                     /* call 0x2e2f */
    routine_4590(b);                             /* call 0x4590 (B live) */
    dispatch_match_loop();                       /* b 0x2e64 tail */
}
