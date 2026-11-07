/* ROM6 0x8507 SUB_8501 tail -- 7w.
 * Verified encoding: src/rom6/kernel/8508_lane_8508.asm (recombine MATCH).
 * ORIGIN 0x8507
 * EXPECT: FC00 7712 B74F 7715 30DC F074 8611
 *
 * Intent: second fanout launcher. The leading ret closes the
 * 0x8501 fall-through (exit word owned by 8501; ret-twin asm deleted
 * wave-12, full lane in 8508_lane_8508.asm); this routine's own body
 * points AR2/AR5 at the high buffers 0xB74F/0x30DC and runs the
 * 0x8611 32-bit XOR combine (lane tail calld 8555 + ret live in the
 * 8508 span, beyond this EXPECT).
 */
extern void copy14_8611(int *p2, int *p5);

void sub_8507_tail(void)
{
    /* FC00: ret closes the 0x8501 fall-through, not this body. */
    int *ar2 = (int *)0xB74F;                 /* stm #-18609,ar2 */
    int *ar5 = (int *)12508;                  /* stm #12508,ar5 */
    copy14_8611(ar2, ar5);                     /* call 0x8611 */
    /* ret */
}
