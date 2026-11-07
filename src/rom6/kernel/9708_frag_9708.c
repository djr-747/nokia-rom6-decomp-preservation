/* ROM6 0x9708 FRAG_9708 -- 3w.
 * Verified encoding: src/rom6/kernel/9708_frag_9708.asm (recombine MATCH).
 * ORIGIN 0x9708
 * EXPECT: FE00 6984 0800
 *
 * Intent: Delayed-return bit set. Sets bit 11 through live-in AR4 (orm #2048,*ar4); the orm is retd's single delay slot (always runs before the return completes, effect identical to a plain set). Bound 9708-970A.
 */
void frag_9708(int *par4)
{
    *par4 |= 2048;                               /* retd delay: orm #2048,*ar4 */
    /* retd */
}
