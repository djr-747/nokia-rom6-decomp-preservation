/* ROM6 0x89EB FRAG_89EB -- 9w.
 * Verified encoding: src/rom6/kernel/89eb_frag_89eb.asm (recombine MATCH).
 * ORIGIN 0x89EB
 * EXPECT: 4913 F84C 89CE 7713 0001 F273 89D2 770E 0078
 *
 * Intent: FRAG_89EB register-gated delayed branch (9w). B = AR3-entry value (ldm, threaded as param); nonzero runs dark 0x89CE (bc bneq, forward extern). Else AR3 = 1 (local; entry value consumed by the test); delayed-branch to dark 0x89D2 inside ROUTINE_89C4 (bd, forward extern) with T = 120 in the slot (always runs, dead, noted). Bound 89EB-89F3.
 */
extern void frag_89CE(void); /* joins 89c4_routine_89c4 interior @+0xA; see docs/evidence/extern-triage.md */
extern void frag_89D2(void); /* joins 89c4_routine_89c4 interior @+0xE; see docs/evidence/extern-triage.md */

void frag_89EB(int *par3)
{
    int b = (int)(long)par3;                      /* ldm ar3,b */
    int *ar3;
    if (b != 0) {                                  /* bc 0x89ce,bneq */
        frag_89CE();                               /* away, dark */
        return;
    }
    ar3 = (int *)(long)1;                         /* stm #1,ar3 */
    (void)ar3;
    /* stm #120,t (bd delay slot, dead, noted) */
    frag_89D2();                                   /* bd 0x89d2 tail */
}
