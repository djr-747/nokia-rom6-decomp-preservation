/* ROM6 0xC660 FRAG_C660 -- 31w FRCT-guarded call wrapper.
 * Verified encoding: src/rom6/kernel/c660_frag_c660.asm (recombine MATCH).
 * ORIGIN 0xC660
 * EXPECT: 4A10 7710 0012 F070 000A 4B90 F7B6 ED00 7712 1265 8082 7713 2212 7714 1264 7715 1268 F274 0696 771A 0000 F6B6 7710 001C F070 000A 8B88 8A10 10F8 1265 FC00
 *
 * Intent: 11-word stack-frame save/restore around a
 * fractional-mode call. Push AR0, seed AR0 = 18, long RPT
 * #10 (F070 hand-forced: gas picks ECxx short, ROM uses
 * F070) + PSHD *AR0+ pushes *(18..28) (11 words); FRCT on
 * (ssbx, no C form -- fractional mode, flagged); ASM = 0
 * (ld #0,asm, no C form, flagged); AL parked at 4709; AR3
 * = 8722; AR4 = 4708; AR5 = 4712; deferred call 0x696
 * (low-region: zero in mask dump; provisional link name
 * sub_0696) with BRC = 0 in the delay slots; FRCT off at
 * the return address (rsbx); AR0 = 28, RPT #10 + POPD
 * *AR0- restores the 11 words in reverse; popm AR0; return
 * A = *(0x1265) (plain LD, SXM-dark, flagged). Pushes and
 * pops match; no residue.
 */
extern void sub_0696(void); /* low-region: zero in mask dump (verified); see docs/evidence/extern-triage.md */

void frag_C660(void)
{
    long a;  /* entry AL parked to 4709 (dark, flagged) */
    int *ar0;
    int *ar2;
    int *ar3;
    int *ar4;
    int *ar5;
    int sk[11];
    int i;

    /* pshm ar0 (entry AR0 saved, restored before return) */
    ar0 = (int *)18;                                           /* stm #18,ar0 */
    for (i = 0; i < 11; i++)                                   /* rpt #10 (long form F070) */
        sk[i] = *ar0++;                                        /* pshd *ar0+ (pushes *(18..28)) */
    /* ssbx st1,frct (FRCT on, no C form, flagged) */
    /* ld #0,asm (ASM = 0, no C form, flagged) */
    ar2 = (int *)4709;                                         /* stm #4709,ar2 */
    *ar2 = (int)(a & 0xFFFFL);                                 /* stl a,*ar2 (park entry AL) */
    ar3 = (int *)8722;                                         /* stm #8722,ar3 */
    ar4 = (int *)4708;                                         /* stm #4708,ar4 */
    ar5 = (int *)4712;                                         /* stm #4712,ar5 */
    /* stm #0,brc (calld delay: fills both delay words) */
    sub_0696();                                                /* calld 0x696 */
    /* rsbx st1,frct (return address: FRCT off) */
    ar0 = (int *)28;                                           /* stm #28,ar0 */
    for (i = 0; i < 11; i++)                                   /* rpt #10 (long form F070) */
        *ar0-- = sk[10 - i];                                   /* popd *ar0- (restores *(28..18)) */
    /* popm ar0 */
    a = (long)*(volatile int *)0x1265;                         /* ld *(0x1265),a (SXM-dark, flagged) */
    /* ret */
    (void)ar3; (void)ar4; (void)ar5;
}
