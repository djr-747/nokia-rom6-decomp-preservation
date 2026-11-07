/* ROM6 0x7C9E COUNTER_STEP_7C9E -- 7w.
 * Verified encoding: src/rom6/kernel/7c9e_counter_step_7c9e.asm (recombine MATCH).
 * ORIGIN 0x7C9E
 * EXPECT: 1082 F000 0001 F030 0003 8082 FC00
 *
 * Intent: Mod-4 counter step. Loads *AR2 (live-in pointer), adds 1, masks to 2 bits, stores back, returns the new value.
 */
int counter_step_7C9E(int *par2)
{
    int a = (*par2 + 1) & 3;                 /* ld, add #1, and #3 */
    *par2 = a;                                   /* stl a,*ar2 */
    return a;                                    /* ret */
}
