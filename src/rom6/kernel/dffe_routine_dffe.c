/* ROM6 0xDFFE ROUTINE_DFFE -- 2w flag set, one EXPECT.
 * Verified encoding: src/rom6/kernel/dffe_routine_dffe.asm (recombine MATCH).
 * ORIGIN 0xDFFE
 * EXPECT: 7663 0001
 *
 * Intent: *(0x63) = 1 (st #1,DP+0x63; DP live-in, transcribed absolute
 * with DP = 0 assumed -- thin post-RET entry, trace-confirmable). Then
 * falls into FIR_KERNEL_A head (abut, per .asm header: entered via call
 * @DFF6). Bound DFFE-DFFF, no own exit.
 */
void routine_DFFE(void)
{
    *(volatile int *)0x63 = 1;               /* st #1,DP+0x63 */
    /* falls into FIR_KERNEL_A exterior */
}
