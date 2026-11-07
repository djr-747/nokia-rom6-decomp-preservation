/* ROM6 0x3EE1 PORT13_STABLE_READ -- 2w head + abutting body.
 * Verified encoding: src/rom6/kernel/3ee1_port13_stable_read.asm (recombine MATCH).
 * ORIGIN 0x3EE1
 * EXPECT: F074 063E
 *
 * Intent: Entry-call head (the .asm captures only the head call).
 * Head-calls dark SUB_063E, then falls into STABLE_READ_3EE3 (abut
 * 3EE1+2 = 3EE3, modeled as tail call per 66C5; C: stable_read_3EE3):
 * A-out is the stable 14-bit port-13 reading, B-out is 0 -- PROVEN by
 * the loop shape (both accumulators unconditionally rewritten, so
 * callee-preservation is impossible). Every caller reading A/B after
 * call 0x3EE1 gets reading/0, never live-ins. Defines
 * PORT13_STABLE_READ for the 2983/A7B7/4474/A2C3 callers. Body modules:
 * 3ee3_stable_read_3ee3 (loop), 3ef3_port_config_3ef3 (config ladder).
 */
extern void sub_063E(void);
extern int stable_read_3EE3(void);

int port13_stable_read(void)
{
    sub_063E();                                    /* call 0x63e */
    return stable_read_3EE3();         /* fall into 3EE3 (abut tail) */
}
