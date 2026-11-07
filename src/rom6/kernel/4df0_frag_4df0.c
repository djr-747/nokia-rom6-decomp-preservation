/* ROM6 0x4DF0 FRAG_4DF0 -- 6w.
 * Verified encoding: src/rom6/kernel/4df0_frag_4df0.asm (recombine MATCH).
 * ORIGIN 0x4DF0
 * EXPECT: 7719 0016 F273 4E00 7711 0016
 *
 * Intent: Delayed-branch preset. BK = 22 (circular-buffer size, hardware state, cited not bound per 9233); branches to dark 0x4E00 (bd 0x4e00, forward extern) with AR1 = 22 set in the delay slot (always runs, dead after, noted). Bound 4DF0-4DF5.
 */
extern void frag_4E00(void);

void frag_4DF0(void)
{
    /* stm #22,bk (BK circular size, hardware state) */
    /* stm #22,ar1 (bd delay slot: always runs, dead after) */
    frag_4E00();                                 /* bd 0x4e00 */
}
