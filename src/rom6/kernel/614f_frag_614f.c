/* ROM6 0x614F FRAG_614F -- 6w.
 * Verified encoding: src/rom6/kernel/614f_frag_614f.asm (recombine MATCH).
 * ORIGIN 0x614F
 * EXPECT: 6181 0001 FC20 FE00 7685 0040
 *
 * Intent: Flag-gated delayed store. Bit 0 of *AR1-live-in clear returns (rc ntc); else stores 64 through live-in AR5 in the retd delay slot (always runs before the return completes) and returns. NOTE: retd has two delay slots but only one is in-span; the second slot executes the next head word at runtime (boundary spill, flagged for decomp review). Bound 614F-6154.
 */
void frag_614F(int *par1, int *par5)
{
    if ((*par1 & 1) == 0)                        /* bitf, rc ntc */
        return;
    /* retd delay (always runs): st #64,*ar5 */
    *par5 = 64;
    /* retd (2nd delay slot = next head word, unmodeled, flagged) */
}
