/* ROM6 0x82FE LEAF43_82D4 -- 54w bit-serial shuffle, abutted head.
 * Verified encoding: src/rom6/kernel/82fe_leaf43_82d4.asm (recombine MATCH).
 * ORIGIN 0x82FE
 * EXPECT: FC00 F6BE EA00 7715 0006 E900 6F86 0C4D F00D 0001 8214 E801 008E F030 0007 F000 0008 F484 800E 6DB4 1484 F490 F591 F761 1B81 8189 E900 771A 0007 F072 832E 6F86 0C4D F00D 0001 8214 E801 008E F030 0007 F000 0008 F484 800E 6DB4 1484 F490 F591 F761 6E8D 8318 1B81 8189 F7BE
 *
 * Intent: Post-RET head: the leading ret belongs to
 * the fall-through exit of the previous span (abut,
 * not modeled). CPL = 0 (rsbx, hardware); DP = 0
 * (ld #0,dp, hardware -- directs below are
 * DP:page-0 absolute). AR5 = 6; B = 0; one head
 * pass of the dance, then a 6-pass outer loop
 * (banzd 0x8318,*ar5-) around an 8-pass RPTB block
 * (brc = 7, block 831C-832E). Each pass: A =
 * *(AR6) << 13 (SXM dark, flagged); A += 1 << 13
 * (add #1,13,a); *(0x14) = A-high (sth, ASM dark,
 * flagged); A = 1; A += *(AR6--) zero-extended
 * (add Smem, SXM flagged); A &= 7; A += 8; A = -A
 * (neg); *(0x0E) = A-low; AR4 += AR0 (mar *ar4+0,
 * AR0 dark, flagged); A = *(AR4) << T (ld ts, T
 * dark, flagged); ROR A then ROL B (low32 rotate
 * through C, extension cleared, oracle op_rotate;
 * C live-in dark, flagged); SFTA B,1 (B <<= 1,
 * OVM saturation flagged) inside the RPTB block
 * only; the head pass and the banzd delay both run
 * OR *(AR1) into B (or *ar1,b, Smem zero-ext) then
 * *(AR1--) = B-low. Tail ssbx st1,cpl (hardware,
 * no C form). AR1/AR2/AR4/AR6/T/C/AR0/SXM/ASM
 * caller-live dark, flagged; A/B/C clobbered.
 * In ARs/cells; out moved cells/ARs/CPL.
 * EXPECT from the image.
 */
void leaf43_82D4(void)
{
    long a;  /* clobbered (entry dark) */
    long b;
    int *ar1;  /* live-in (dark, flagged) */
    int *ar2;  /* live-in (dark, flagged) */
    int *ar4;  /* live-in (dark, flagged) */
    int *ar6;  /* live-in (dark, flagged) */
    int *ar5;
    int ar0;  /* live-in (dark, flagged) */
    int t;  /* T live-in (dark, flagged) */
    int c;  /* C live-in (dark, flagged) */
    int nc;
    int i;

    /* ret (previous span's exit, abut -- not modeled) */
    /* rsbx st1,cpl (hardware, no C form) */
    /* ld #0,dp (hardware; directs absolute below) */
    ar5 = (int *)6;                                          /* stm #6,ar5 */
    b = 0;                                                   /* ld #0,b */
    a = (long)*ar6 << 13;                                    /* ld *ar6,13,a (SXM dark, flagged) */
    a += 1L << 13;                                           /* add #1,13,a */
    *(volatile int *)0x14 = (int)((a >> 16) & 0xFFFFL);       /* sth a,0x14 (ASM dark, flagged) */
    a = 1;                                                   /* ld #1,a */
    a += (long)*(ar6--);                                     /* add *ar6-,a (SXM flagged) */
    a &= 7L;                                                 /* and #7,a */
    a += 8L;                                                 /* add #8,a */
    a = -a;                                                  /* neg a */
    *(volatile int *)0x0E = (int)(a & 0xFFFFL);               /* stl a,0x0e */
    ar4 += ar0;                                              /* mar *ar4+0 (AR0 dark, flagged) */
    a = (long)*ar4 << t;                                     /* ld *ar4,ts,a (T dark, flagged) */
    nc = (int)(a & 1L);                                      /* ror a (oracle op_rotate) */
    a = (long)(((unsigned long)a >> 1) | ((unsigned long)c << 31));
    c = nc;
    nc = (int)((b >> 31) & 1L);                              /* rol b */
    b = (long)(((unsigned long)b << 1) | (unsigned long)c);
    c = nc;
    b <<= 1;                                                 /* sfta b,1 (OVM flagged) */
    b |= (long)(unsigned)*ar1;                               /* or *ar1,b (zero-ext) */
    *ar1-- = (int)(b & 0xFFFFL);                             /* stl b,*ar1- */
    do {
        b = 0;                                               /* ld #0,b @8318 (banzd target) */
        /* stm #7,brc; rptb 0x832e */
        for (i = 0; i < 8; i++) {                            /* rptb block x (BRC+1) */
            a = (long)*ar6 << 13;                            /* ld *ar6,13,a */
            a += 1L << 13;                                   /* add #1,13,a */
            *(volatile int *)0x14 = (int)((a >> 16) & 0xFFFFL); /* sth a,0x14 */
            a = 1;                                           /* ld #1,a */
            a += (long)*(ar6--);                             /* add *ar6-,a */
            a &= 7L;                                         /* and #7,a */
            a += 8L;                                         /* add #8,a */
            a = -a;                                          /* neg a */
            *(volatile int *)0x0E = (int)(a & 0xFFFFL);       /* stl a,0x0e */
            ar4 += ar0;                                      /* mar *ar4+0 */
            a = (long)*ar4 << t;                             /* ld *ar4,ts,a */
            nc = (int)(a & 1L);                              /* ror a */
            a = (long)(((unsigned long)a >> 1) | ((unsigned long)c << 31));
            c = nc;
            nc = (int)((b >> 31) & 1L);                      /* rol b */
            b = (long)(((unsigned long)b << 1) | (unsigned long)c);
            c = nc;
            b <<= 1;                                         /* sfta b,1 (OVM flagged) */
        }
        b |= (long)(unsigned)*ar1;                           /* banzd delay: or *ar1,b */
        ar5--;                                               /* banzd 0x8318,*ar5- */
    } while (ar5 != 0);
    *ar1-- = (int)(b & 0xFFFFL);                             /* stl b,*ar1- */
    /* ssbx st1,cpl (hardware, no C form) */
}
