/* ROM6 0x4DEA FRAG_4DEA -- 6w BK-preset chain link, one EXPECT.
 * Verified encoding: src/rom6/kernel/4dea_frag_4dea.asm (recombine MATCH).
 * ORIGIN 0x4DEA
 * EXPECT: 7719 0016 F273 4E00 6DF3 000E
 *
 * Intent: BK = 22 (stm); AR3 = (AR3 + 14) circular mod BK (mar
 * *+ar3(0xe)% in the bd delay slot -- always executes; single-subtract
 * wrap, buffer base 0 assumed, flagged); unconditional delayed branch
 * to FRAG_4E00 (bd 0x4e00; 4E00 is asm-absent exterior, so the entry is
 * a forward extern carrying live AR3/BK/AR1). Chain-link 3/5 (per
 * header); AR1 rides entry-live. Bound 4DEA-4DEF.
 */
extern void frag_4E00(int ar3_live, int bk_live, int ar1_live); /* joins 4dfa_frag_4dfa interior @+0x6; see docs/evidence/extern-triage.md */

void frag_4DEA(int ar3_live, int ar1_live)
{
    int bk = 22;                                     /* stm #22,bk */
    int ar3 = ar3_live + 14;              /* bd delay: mar *+ar3(0xe)% */

    if (ar3 >= bk)
        ar3 -= bk;
    frag_4E00(ar3, bk, ar1_live);                     /* bd 0x4e00 */
}
