/* ROM6 0x4DE2 FRAG_4DE2 -- 8w BK/AR1-preset chain link, one EXPECT.
 * Verified encoding: src/rom6/kernel/4de2_frag_4de2.asm (recombine MATCH).
 * ORIGIN 0x4DE2
 * EXPECT: 7719 0008 7711 0004 F273 4E00 6DF3 0004
 *
 * Intent: BK = 8, AR1 = 4 (stm pair); AR3 = (AR3 + 4) circular mod BK
 * (mar *+ar3(0x4)% in the bd delay slot -- always executes;
 * single-subtract wrap, buffer base 0 assumed, flagged); unconditional
 * delayed branch to FRAG_4E00 (bd 0x4e00; exterior forward extern
 * carrying live AR3/BK/AR1). Gap-internal, chain-link 2/5 (per header).
 * Bound 4DE2-4DE9.
 */
extern void frag_4E00(int ar3_live, int bk_live, int ar1_live); /* joins 4dfa_frag_4dfa interior @+0x6; see docs/evidence/extern-triage.md */

void frag_4DE2(int ar3_live)
{
    int bk = 8;                                       /* stm #8,bk */
    int ar1 = 4;                                      /* stm #4,ar1 */
    int ar3 = ar3_live + 4;               /* bd delay: mar *+ar3(0x4)% */

    if (ar3 >= bk)
        ar3 -= bk;
    frag_4E00(ar3, bk, ar1);                           /* bd 0x4e00 */
}
