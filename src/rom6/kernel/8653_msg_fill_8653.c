/* ROM6 0x8653 SUB_8653 -- 2w.
 * Verified encoding: src/rom6/kernel/8653_msg_fill_8653.asm (recombine MATCH).
 * ORIGIN 0x8653
 * EXPECT: F074 0592
 *
 * Intent: MSG_FILL_8653 entry-call stub (2w). Head-calls dark SUB_0592. No in-tree callers yet.
 */
extern void sub_0592(void);

void sub_8653(void)
{
    sub_0592();                                    /* call 0x592 */
}
