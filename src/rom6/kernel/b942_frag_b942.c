/* ROM6 0xB942 FRAG_B942 -- 6w.
 * Verified encoding: src/rom6/kernel/b942_frag_b942.asm (recombine MATCH).
 * ORIGIN 0xB942
 * EXPECT: F274 B743 7713 2FAE F073 B8B0
 *
 * Intent: FRAG_B942 delayed-call tail (6w, ROM slice verified: no listing row). Delayed-call into unbound FIR_WORKER_B743 (calld, forward extern void; delay stm #12206,ar3 preset dead in C, noted); tail-enters dark 0xB8B0 (b, forward extern).
 */
extern void sub_B743(void);
extern void frag_B8B0(void);

void frag_B942(void)
{
    /* stm #12206,ar3 (calld delay slot, dead preset, noted) */
    sub_B743();                                    /* calld 0xb743 */
    frag_B8B0();                                   /* b 0xb8b0 tail */
}
