/* ROM6 0x4450 FRAG_4450 -- 3w.
 * Verified encoding: src/rom6/kernel/4450_frag_4450.asm (recombine MATCH).
 * ORIGIN 0x4450
 * EXPECT: 7D94 4500 FC00
 *
 * Intent: Overlay patch point. Post-RET head: writes *AR4++ into program cell 0x4500 (mvdp data-to-program move), then returns.
 */
void frag_4450(int *par4)
{
    *(volatile int *)0x4500 = *par4++;     /* mvdp *ar4+,0x4500 */
    /* ret */
}
