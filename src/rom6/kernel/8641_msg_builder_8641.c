/* ROM6 0x8641 SUB_8641 -- 2w.
 * Verified encoding: src/rom6/kernel/8641_msg_builder_8641.asm (recombine MATCH).
 * ORIGIN 0x8641
 * EXPECT: F074 0592
 *
 * Intent: MSG_BUILDER_8641 entry-call stub (2w). Head-calls dark SUB_0592. Defines SUB_8641 for the 5420-lane caller.
 */
extern void sub_0592(void);

void sub_8641(void)
{
    sub_0592();                                    /* call 0x592 */
}
