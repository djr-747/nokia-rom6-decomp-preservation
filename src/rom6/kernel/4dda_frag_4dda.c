/* ROM6 0x4DDA FRAG_4DDA -- 8w BK/AR1-preset chain link, one EXPECT.
 * Verified encoding: src/rom6/kernel/4dda_frag_4dda.asm (recombine MATCH).
 * ORIGIN 0x4DDA
 * EXPECT: 7719 0008 7711 0006 F273 4E00 6DF3 0002
 *
 * Intent: BK = 8, AR1 = 6 (stm pair); AR3 = (AR3 + 2) circular mod BK
 * (mar *+ar3(0x2)% in the bd delay slot -- always executes;
 * single-subtract wrap, buffer base 0 assumed, flagged); unconditional
 * delayed branch to FRAG_4E00 (bd 0x4e00; exterior forward extern
 * carrying live AR3/BK/AR1). Post-baccd head, chain-link 1/5 (per
 * header). Bound 4DDA-4DE1.
 */
extern void frag_4E00(int ar3_live, int bk_live, int ar1_live); /* joins 4dfa_frag_4dfa interior @+0x6; see docs/evidence/extern-triage.md */

void frag_4DDA(int ar3_live)
{
    int bk = 8;                                       /* stm #8,bk */
    int ar1 = 6;                                      /* stm #6,ar1 */
    int ar3 = ar3_live + 2;               /* bd delay: mar *+ar3(0x2)% */

    if (ar3 >= bk)
        ar3 -= bk;
    frag_4E00(ar3, bk, ar1);                           /* bd 0x4e00 */
}
