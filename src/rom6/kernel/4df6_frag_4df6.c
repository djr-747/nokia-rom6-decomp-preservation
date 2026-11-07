/* ROM6 0x4DF6 FRAG_4DF6 -- 4w.
 * Verified encoding: src/rom6/kernel/4df6_frag_4df6.asm (recombine MATCH).
 * ORIGIN 0x4DF6
 * EXPECT: F273 4E00 7719 0008
 *
 * Intent: Delayed-branch BK preset. Branches to dark 0x4E00 (bd, forward extern) with BK = 8 set in the delay slot (always runs; circular size, hardware state). Bound 4DF6-4DF9.
 */
extern void frag_4E00(void);

void frag_4DF6(void)
{
    /* stm #8,bk (bd delay slot: always runs; hardware state) */
    frag_4E00();                                 /* bd 0x4e00 */
}
