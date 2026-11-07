/* ROM6 0x3879 FRAG_3879 -- 19w.
 * Verified encoding: src/rom6/kernel/3879_frag_3879.asm (recombine MATCH).
 * ORIGIN 0x3879
 * EXPECT: 7713 2F00 4915 F77F 7710 0001 F84B 37DF 47F8 000B E5C9 7714 009A F274 2C88 7713 2F00 F073 37DF
 *
 * Intent: Halve-and-blit gate. AR3 = 12032; B = AR5-value >> 1
 * arithmetic (ldm + SFTA, SXM = 1 assumed flagged); AR0 = 1 (circular
 * step); B < 0 tail-enters FRAG_37DF (bc blt; void per the 381b/3850
 * precedent). Else RC = *(0xB) + 1 dual moves *(AR3++) = *AR2 with
 * AR2 += AR0 (rpt Smem + MVDD +0%, 457f precedent; modulo wrap needs
 * caller-live BK, linear modeled flagged); AR4 = 154 (live into the
 * dark call, flagged); AR3 re-armed 12032 (calld delay, redundant)
 * then dark SUB_2C88; tail-branch 0x37DF (B clobber risk via the dark
 * call, flagged). Bound 3879-388B.
 */
extern void sub_2C88(void); /* joins 2c88_ring_report_gate; see docs/evidence/extern-triage.md */
extern void frag_37DF(void); /* joins 37d8_frag_37d8 interior @+0x7; see docs/evidence/extern-triage.md */

void frag_3879(int ar5_live, int *ar2_in)
{
    int *ar2 = ar2_in;
    int *ar3;
    long b;
    int rc;
    int i;
    ar3 = (int *)12032;                              /* stm #12032,ar3 */
    b = (long)ar5_live >> 1;                         /* ldm ar5,b; sfta b,-1 */
    /* stm #1,ar0 (circular step = 1) */
    if (b < 0) {                                     /* bc 0x37df,blt */
        frag_37DF();
        return;
    }
    rc = *(volatile int *)0xB;                       /* rpt *(0xb) */
    for (i = 0; i < rc + 1; i++) {                   /* mvdd *ar2+0%,*ar3+ */
        *ar3++ = *ar2;
        ar2 += 1;                                    /* +0%: AR2 += AR0 (wrap flagged) */
    }
    /* stm #154,ar4 (live into dark call, flagged) */
    ar3 = (int *)12032;                              /* calld delay: re-arm */
    sub_2C88();                                      /* calld 0x2c88 (dark) */
    frag_37DF();                                     /* b 0x37df */
}
