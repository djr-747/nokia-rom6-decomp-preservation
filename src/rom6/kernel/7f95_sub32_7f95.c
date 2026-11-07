/* ROM6 0x7F95 SUB32_7F95 -- 30w rotate-merge loop.
 * Verified encoding: src/rom6/kernel/7f95_sub32_7f95.asm (recombine MATCH).
 * ORIGIN 0x7F95
 * EXPECT: F074 059E 7715 0006 E900 7196 0013 6DB3 1483 F490 F591 F761 1B81 8189 E900 771A 0007 F072 7FAE 7196 0013 6DB3 1483 F490 F591 F761 6E8D 7FA3 1B81 8189
 *
 * Intent: Rotate-merge loop, sibling of the 7F75 lane (AR2
 * sink there, carrying an extra SFTL step) and of the 7E88
 * rotor. Head (once): call 0x59E (RAM: zero in mask dump);
 * AR5 = 6; B = 0; cell 0x13 = *AR6+ (table cursor, plain
 * cell per tree convention); A = *AR3 << TS (T
 * caller-preset, dark -- TS = T & 31, flagged); ROR A /
 * ROL B through a shared carry (initial carry dark,
 * flagged); B <<= 1; fold *AR1 in; store BL to *AR1-.
 * Main loop (BANZD on AR5, 6 passes, no reload -- terminates
 * cleanly, unlike the dark-counter loops): each pass
 * re-arms B = 0, BRC = 7 at the 7FA3 target, runs RPTB block
 * 7FA8-7FAE x8 {reload cell 0x13, shift in *AR3, ROR/ROL
 * ring with B <<= 1}, then the BANZD delay words fold/store
 * to *AR1- (or *ar1,b; stl b,*ar1-) and AR5-- decides the
 * re-arm. Span ends 7FB2 (tail-merges to 7FB3 per header).
 * Out: merged stream at *AR1-.
 * (Wave-13: RPTB block = 7 words through REA 7FAE; or/stl
 * are the BANZD delay slots inside the AR5 loop, not a
 * once-per-RPTB tail; BANZD target 7FA3 = the B=0/BRC=7
 * re-arm.)
 */
extern void sub_059E(void); /* low-region: zero in mask dump; see docs/evidence/extern-triage.md */

void sub32_7F95(void)
{
    long a;
    long b;
    int *ar1;  /* live-in (dark, flagged) */
    int *ar3;  /* live-in (dark, flagged) */
    int *ar5;
    int *ar6;  /* table cursor, live-in (dark, flagged) */
    int t;  /* T live-in for TS shifts (dark, flagged) */
    int ts;
    int carry = 0;  /* C54x carry in (dark, flagged) */
    int i;

    sub_059E();                                                /* call 0x59e (RAM) */
    ar5 = (int *)6;                                            /* stm #6,ar5 */
    b = 0;                                                     /* ld #0,b */
    *(volatile int *)0x13 = *ar6++;                            /* mvdk *ar6+,0x13 */
    /* mar *ar3+0 */
    ts = t & 31;
    a = (long)*ar3 << ts;                                      /* ld *ar3,ts,a */
    { int nc = (int)(a & 1L); a = ((a >> 1) & 0x7FFFFFFFL) | ((long)carry << 31); carry = nc; } /* ror a */
    { int nc = (int)((b >> 31) & 1L); b = (b << 1) | carry; carry = nc; } /* rol b */
    b <<= 1;                                                   /* sfta b,1 */
    b |= (long)(*ar1 & 0xFFFF);                                           /* or *ar1,b */
    *ar1-- = (int)(b & 0xFFFFL);                               /* stl b,*ar1- */
    b = 0;                                                     /* ld #0,b */
    /* stm #7,brc */
    do {                                                       /* main loop (BANZD on AR5) */
        b = 0;                                                 /* 7fa3 re-arm: ld #0,b */
        /* stm #7,brc (re-arm) */
        for (i = 0; i < 8; i++) {                              /* rptbd 0x7fae */
            *(volatile int *)0x13 = *ar6++;                    /* mvdk *ar6+,0x13 */
            /* mar *ar3+0 */
            a = (long)*ar3 << ts;                              /* ld *ar3,ts,a */
            { int nc = (int)(a & 1L); a = ((a >> 1) & 0x7FFFFFFFL) | ((long)carry << 31); carry = nc; } /* ror a */
            { int nc = (int)((b >> 31) & 1L); b = (b << 1) | carry; carry = nc; } /* rol b */
            b <<= 1;                                           /* sfta b,1 */
        }
        b |= (long)(*ar1 & 0xFFFF);                                       /* banzd delay 1: or *ar1,b */
        *ar1-- = (int)(b & 0xFFFFL);                           /* banzd delay 2: stl b,*ar1- */
        ar5--;                                                 /* banzd 0x7fa3,*ar5- */
    } while (ar5 != (int *)0);
    /* (span ends 7FB2; tail-merges to 7FB3) */
    (void)a; (void)b;
}
