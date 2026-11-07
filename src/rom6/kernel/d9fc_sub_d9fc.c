/* ROM6 0xD9FC SUB_D9FC -- 26w.
 * Verified encoding: src/rom6/kernel/d9fc_sub_d9fc.asm (recombine MATCH).
 * ORIGIN 0xD9FC
 * EXPECT: 7712 0A5E E807 8092 7692 7FFF 7692 0001 7692 0017 8292 8292 7692 7081 7692 6958 771A 0006 F272 DA14 7712 0ACE EC09 7C92 D9C9 FE00
 *
 * Intent: Constant fill plus ROM-constant blast. AR2 = 2654;
 * A = 7; stores 7, 32767, 1, 23, A-high (= 0, exact), A-high,
 * 28801, 26968 with post-inc; BRC = 6; the rptbd delay slot
 * AR2 = 2766 runs once; 7 passes of rpt #9 + MVPD program-word
 * 0xD9C9 to *(AR2++) (block [RSA = PC + 4 = 0xDA12, REA = 0xDA14];
 * RPTBD execution stays deferred, flagged). The MVPD source is
 * the fixed immediate: single-RPT re-executes identical
 * instruction words, so the immediate pmad cannot step (only the
 * AR dest steps) -- 70 copies of PROM[0xD9C9] via prom_read_word
 * (44bd precedent); if the silicon latches pmad this is a
 * streaming copy instead (flagged). retd with delays in the DA16
 * span (9B6F pattern, C: da16; flagged). AR2 dead at return.
 * Bound D9FC-DA15.
 */
extern int prom_read_word(int prog_addr);

void sub_D9FC(void)
{
    int *ar2;
    long a;
    int w;
    int i;
    int j;
    ar2 = (int *)2654;                               /* stm #2654,ar2 */
    a = 7;                                           /* ld #7,a */
    *ar2++ = 7;                                      /* stl a,*ar2+ */
    *ar2++ = 32767;                                  /* st #32767,*ar2+ */
    *ar2++ = 1;                                      /* st #1,*ar2+ */
    *ar2++ = 23;                                     /* st #23,*ar2+ */
    *ar2++ = 0;                                      /* sth a,*ar2+ (A-high=0) */
    *ar2++ = 0;                                      /* sth a,*ar2+ */
    *ar2++ = 28801;                                  /* st #28801,*ar2+ */
    *ar2++ = 26968;                                  /* st #26968,*ar2+ */
    /* stm #6,brc */
    ar2 = (int *)2766;                               /* rptbd delay: stm (once) */
    w = prom_read_word(0xD9C9);                      /* mvpd source (fixed, flagged) */
    for (i = 0; i < 7; i++)                          /* rptbd 0xda14 */
        for (j = 0; j < 10; j++)                     /* rpt #9 */
            *ar2++ = w;                              /* mvpd 0xd9c9,*ar2+ */
    /* retd (delays in DA16 span, always run there) */
    (void)a;                                         /* A dead at return (flagged) */
}
