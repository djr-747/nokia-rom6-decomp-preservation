/* ROM6 0x72E3 ROUTINE_72E3 -- 44w compare-swap sweep.
 * Verified encoding: src/rom6/kernel/72e3_routine_72e3.asm (recombine MATCH).
 * ORIGIN 0x72E3
 * EXPECT: F074 0596 4A16 F020 2F0D F600 8815 F010 0001 8814 7710 2F0E 1085 0880 F842 730D 7315 0017 F310 0002 891A 8916 F072 730C A232 F842 7301 1085 E523 8084 6E8E 72FB 6D8C 6D8D 7317 0015 7317 0014 6D8C F310 0001 8916 8A16 FC00
 *
 * Intent: Calls sub_0596 (low-zone unsourced, flagged); saves
 * AR6 (pshm, balanced); A = 12045 + B-entry (B dark,
 * flagged); AR5 = A-low; A -= 1; AR4 = A-low; AR0 = 12046;
 * A = *(AR5) - *(AR0); A >= 0 exits to popm/ret (bc ageq).
 * Else *(0x17) = AR5 (mvmd); B -= 2; BRC = AR6 = B-low; RPTB
 * block (exact BRC+1 incl. wrap; B/BRC/AR6 dark, flagged):
 * A = *(AR5) - *(AR4) (sub dual); A >= 0 skips the swap
 * (bc ageq to the banzd); else swap *(AR5)<->*(AR4)
 * (ld/mvdd/stl triple). Inner BANZD loop back to the sub
 * (delays mar *ar4-/mar *ar5- run every pass incl. the
 * fall-through; exact shoot-first do-while): per inner
 * pass AR4--/AR5-- with the compare-swap at the new pair.
 * Then *(0x15) = *(0x14) = AR7-entry (dark, flagged),
 * AR4--, B--, AR6 = B-low reloaded; repeat. Tail pops AR6,
 * return. COUNT CAVEAT (flagged): AR6 is not reset per
 * outer pass, so the final outer pass with AR6 = 0 runs
 * 65536 inner iters; B dark decides. AR5/AR4/AR0/B/AR6
 * computed; out cells/ARs.
 * EXPECT from the image.
 */
void routine_72E3(void)
{
    long a;
    long b;  /* live-in (dark, flagged) */
    int *ar0;
    int *ar4;
    int *ar5;
    int *ar6;
    int *ar7;  /* live-in (dark, flagged) */
    int tmp;
    int brc;  /* (dark: B-derived, flagged) */
    int i;

    sub_0596();                                              /* call 0x596 (low-zone, flagged) */
    /* pshm ar6 (balanced by popm; comment only) */
    a = 12045;                                               /* ld #12045,a */
    a += b;                                                  /* add b,a */
    ar5 = (int *)(a & 0xFFFFL);                              /* stlm a,ar5 */
    a -= 1;                                                  /* sub #1,a */
    ar4 = (int *)(a & 0xFFFFL);                              /* stlm a,ar4 */
    ar0 = (int *)12046;                                      /* stm #12046,ar0 */
    a = (long)*ar5;                                          /* ld *ar5,a (SXM dark, flagged) */
    a -= (long)*ar0;                                         /* sub *ar0,a */
    if (a >= 0) {                                            /* bc 0x730d,ageq */
        /* popm ar6 */
        return;
    }
    *(volatile int *)0x17 = (int)(long)ar5;                  /* mvmd ar5,0x17 */
    b -= 2;                                                  /* sub #2,b */
    brc = (int)(b & 0xFFFFL);                                /* stlm b,brc */
    ar6 = (int *)(b & 0xFFFFL);                              /* stlm b,ar6 */
    /* rptb 0x730c */
    for (i = 0; i <= (unsigned)brc; i++) {                   /* (BRC+1 incl. wrap; dark) */
        do {
            a = (long)*ar5 - (long)*ar4;                     /* sub *ar5,*ar4,a @72fb */
            if (a < 0) {                                     /* bc 0x7301,ageq */
                tmp = *ar5;                                  /* ld *ar5,a */
                *ar5 = *ar4;                                 /* mvdd *ar4,*ar5 */
                *ar4 = tmp;                                  /* stl a,*ar4 */
            }
            ar4--;                                           /* banzd delays (run always) */
            ar5--;                                           /* mar *ar5- */
            ar6--;                                           /* banzd 0x72fb,*ar6- */
        } while (ar6 != 0);
        *(volatile int *)0x15 = (int)(long)ar7;              /* mvmd ar7,0x15 (AR7 dark) */
        *(volatile int *)0x14 = (int)(long)ar7;              /* mvmd ar7,0x14 */
        ar4--;                                               /* mar *ar4- */
        b -= 1;                                              /* sub #1,b */
        ar6 = (int *)(b & 0xFFFFL);                          /* stlm b,ar6 */
    }
    /* popm ar6 (balanced; comment only) */
    /* ret */
}
