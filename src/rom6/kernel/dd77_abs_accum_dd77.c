/* ROM6 0xDD77 ABS_ACCUM_DD77 -- 34w abs-accumulate lane.
 * Verified encoding: src/rom6/kernel/dd77_abs_accum_dd77.asm (recombine MATCH).
 * ORIGIN 0xDD77
 * EXPECT: 7712 0062 7713 FBA6 7714 0063 7715 0064 9802 A209 F485 8284 771A 000E 7685 000F A209 F272 DD90 F485 4184 9D3B 9E2B A209 F485 4184 E80F 0885 8085 F000 FBA6 8812 4485 FE00
 *
 * Intent: Absolute-difference accumulator with conditional
 * stores. AR2 = 98; AR3 = -1114; AR4 = 99; AR5 = 100;
 * *(AR2) = (A << 2) & 0xFFFF (entry A dark, flagged);
 * A = ((*AR2) - (*AR3+)) << 16 (SUB dual MOD0); A = |A|;
 * MSW(A) to *AR4; BRC = 14; cell *AR5 = 15; A = next
 * (*AR2 - *AR3+) difference. RPTBD block DD8A-DD90 x15:
 * A = |A|; B = (*AR4 << 16) - A (4-op SUB); SRCCD
 * *AR5,BLT (if B < 0: *AR5 = BRC -- Store Repeat Counter
 * with Condition Delayed -- per oracle op_srccd_xmem_cond;
 * 2 delay words); SACCD A,*AR4,BLT (if B < 0: *AR4 =
 * low16(A << (ASM-16)), SXM-gated fill, per oracle
 * op_saccd_xmem_cond; ASM/SXM dark, flagged; same
 * 2-delay-word rule -- the saccd+sub words serve as the
 * SRCCD delays and the sub+abs words as the SACCD
 * delays; conditions evaluated at issue, commits after
 * their delays, in issue order); A = next difference;
 * A = |A|; B = (*AR4 << 16) - A (reads the maybe-written
 * *AR4). Tail: A = 15; A -= cell *AR5 << 16; cell *AR5 =
 * AL; A += -1114; AR2 = AL; A = cell *AR5 << 16; return
 * with the DD99-DD9A words running as the RETD delays
 * (next span owns them, per asm header). In AR2/AR5
 * cells + entry A (dark); out cells/AR2.
 * (Wave-13: SRCCD/SACCD are conditional stores, not
 * arithmetic -- oracle store leaves; delayed-commit
 * order modeled; EXPECT from the image.)
 */
void abs_accum_DD77(void)
{
    long a;  /* live-in (dark, flagged) */
    long b;
    int *ar2;
    int *ar3;  /* live-in (dark, flagged) */
    int *ar4;
    int *ar5;
    int take1;
    int take2;
    int i;

    ar2 = (int *)98;                                           /* stm #98,ar2 */
    ar3 = (int *)-1114;                                        /* stm #-1114,ar3 */
    ar4 = (int *)99;                                           /* stm #99,ar4 */
    ar5 = (int *)100;                                          /* stm #100,ar5 */
    *ar2 = (int)(((a << 2)) & 0xFFFFL);                        /* stl a,2,*ar2 */
    a = ((long)*ar2 - (long)*ar3++) << 16;                     /* sub *ar2,*ar3+,a (dual) */
    if (a < 0)                                                 /* abs a */
        a = -a;
    *ar4 = (int)((a >> 16) & 0xFFFFL);                         /* sth a,*ar4 */
    /* stm #14,brc */
    *ar5 = 15;                                                 /* st #15,*ar5 */
    a = ((long)*ar2 - (long)*ar3++) << 16;                     /* sub *ar2,*ar3+,a */
    for (i = 0; i < 15; i++) {                                 /* rptbd 0xdd90 */
        if (a < 0)                                             /* abs a */
            a = -a;
        b = ((long)*ar4 << 16) - a;                            /* sub *ar4,16,a,b (4-op) */
        take1 = (b < 0); /* srccd *ar5,blt (condition at issue) */
        take2 = (b < 0); /* saccd a,*ar4,blt (condition at issue; SRCCD delay 1) */
        a = ((long)*ar2 - (long)*ar3++) << 16;                 /* sub *ar2,*ar3+,a (SRCCD delay 2 / SACCD delay 1) */
        if (a < 0)                                             /* abs a (SACCD delay 2) */
            a = -a;
        if (take2)                                             /* (SACCD commits) */
            *ar4 = (int)(a & 0xFFFFL); /* *AR4 = low16(A << (ASM-16)); ASM/SXM dark, flagged */
        if (take1)                                             /* (SRCCD commits) */
            *ar5 = 14; /* *AR5 = BRC (block count 14) */
        b = ((long)*ar4 << 16) - a;                            /* sub *ar4,16,a,b */
    }
    a = 15;                                                    /* ld #15,a */
    a -= (long)*ar5 << 16;                                     /* sub *ar5,a */
    *ar5 = (int)(a & 0xFFFFL);                                 /* stl a,*ar5 */
    a += -1114;                                                /* add #-1114,a */
    ar2 = (int)(a & 0xFFFFL);                                  /* stlm a,ar2 */
    a = (long)*ar5 << 16;                                      /* ld *ar5,16,a */
    /* retd (delays DD99-DD9A run, then return; next span owns them) */
    /* retd */
    (void)b;
}
