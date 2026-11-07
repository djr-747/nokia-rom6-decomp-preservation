/* ROM6 0x864E SUB_864E -- 2w.
 * Verified encoding: src/rom6/kernel/864e_msg_builder_864e.asm (recombine MATCH).
 * ORIGIN 0x864E
 * EXPECT: F074 0592
 *
 * Intent: MSG_BUILDER_864E entry-call stub (2w). Head-calls dark SUB_0592. Defines SUB_864E for the 5420-lane caller.
 */
extern void sub_0592(void);

void sub_864E(void)
{
    sub_0592();                                    /* call 0x592 */
}
