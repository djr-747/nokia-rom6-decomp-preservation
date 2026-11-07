/* ROM6 0xBAC2 ROUTINE_BAC2 -- 25w.
 * Verified encoding: src/rom6/kernel/bac2_routine_bac2.asm (recombine MATCH).
 * ORIGIN 0xBAC2
 * EXPECT: F074 06A6 61F8 0577 0008 F820 BACD E723 F071 009F 8093 7719 0278 7213 054A 771A 009F F272 BAD7 7710 0001 E58D FE00 7313 054A
 *
 * Intent: Conditional fill plus blit. Runs dark SUB_06A6; TC =
 * (cell0x577 & 8) != 0 (bitf, 32b4 precedent): set runs AR3 = AR2,
 * A = 0, 160 zero stores (rptz a,#159), else skips to the BK setup
 * (bc 0xbacd,ntc skips exactly mvmm + rptz + stl, exact). BK = 632
 * (buffer base unbound, wrap linear-modeled flagged); AR3 =
 * cell0x54A; BRC = 159; the rptbd delay slot AR0 = 1 runs once;
 * 160 passes of *(AR3) = *(AR2++) with AR3 += AR0 (block [RSA =
 * PC + 4 = 0xBAD7 = REA]; RPTBD execution stays deferred, flagged);
 * the retd delay stores AR3 to cell0x54A (always runs); return
 * (ARs dead, flagged). Bound BAC2-BADA.
 */
extern void sub_06A6(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void routine_BAC2(int *ar2_in)
{
    int *ar2 = ar2_in;
    int *ar3;
    long a;
    int tc;
    int i;
    sub_06A6();                                      /* call 0x6a6 (dark) */
    tc = (*(volatile int *)0x577 & 8) != 0;          /* bitf *(0x577),#8 */
    if (tc) {                                        /* bc 0xbacd,ntc (skips fill) */
        ar3 = ar2;                                   /* mvmm ar2,ar3 */
        a = 0;                                       /* rptz a,#159 */
        for (i = 0; i < 160; i++)
            *ar3++ = 0;                              /* stl a,*ar3+ */
    }
    /* stm #632,bk (base unbound, flagged) */
    ar3 = (int *)*(volatile int *)0x54A;             /* mvdm 0x54a,ar3 */
    /* stm #159,brc */
    /* rptbd delay: AR0 = 1 (once) */
    for (i = 0; i < 160; i++) {                      /* rptbd 0xbad7 */
        *ar3 = *ar2++;                               /* mvdd *ar2+,*ar3+0% */
        ar3 += 1;                                    /* +0%: AR3 += AR0 (wrap flagged) */
    }
    *(volatile int *)0x54A = (int)ar3;               /* retd delay: mvmd (always runs) */
    /* retd */
    (void)a;                                         /* A dead at retd (flagged) */
}
