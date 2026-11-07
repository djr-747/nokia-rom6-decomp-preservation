/* ROM6 0x8507 SUB_8501 tail -- 1w.
 * Verified encoding: src/rom6/kernel/8501_sub_8501.asm (recombine MATCH).
 * ORIGIN 0x8507
 * EXPECT: FC00
 *
 * Intent: Second fanout launcher's ret word closes the 0x8501 fall-through
 * (exit word owned by the 8501 span; ret-first twin asm deleted wave-12).
 * Launcher body lives in the 8508 span (see 8508_lane_8508.asm; full-lane
 * intent in lane_8508).
 */
void sub_8507_tail(void)
{
    /* FC00: ret closes the 0x8501 fall-through. Launcher body: see lane_8508. */
}
