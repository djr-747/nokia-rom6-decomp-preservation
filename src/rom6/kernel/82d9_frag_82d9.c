/* ROM6 0x82D9 FRAG_82D9 -- 37w bit-serial shuffle, RPTB in BANZD.
 * Verified encoding: src/rom6/kernel/82d9_frag_82d9.asm (recombine MATCH).
 * ORIGIN 0x82D9
 * EXPECT: 7715 0006 E900 6F86 0C4D 8214 E807 188E F484 800E 6DB4 1484 F490 F591 818A E900 771A 0007 F072 82F8 6F86 0C4D 8214 E807 188E F484 800E 6DB4 1484 F490 F591 F761 6E8D 82E8 F3FF 818A F7BE
 *
 * Intent: AR5 = 6; B = 0; one head pass of the dance, then a
 * 6-pass outer loop (banzd 0x82e8,*ar5-) around an 8-pass
 * RPTB block (brc = 7, block 0x82EF-0x82F8, delays = the ld
 * word-pair which runs once). Each pass: A = *(AR6) << 13
 * (SXM dark, flagged); *(0x14) = A-high (sth, ASM dark,
 * flagged); A = 7; A &= *(AR6--) zero-extended (oracle
 * op_and_smem, C/TC preserved); A = -A; *(0x0E) = A-low;
 * AR4 += AR0 (mar *ar4+0, AR0 dark, flagged); A = *(AR4) << T
 * (ld ts, T dark, flagged); ROR A then ROL B (low32 rotate
 * through C, extension cleared, oracle op_rotate; C
 * live-in dark, flagged); SFTA B,1 (B <<= 1, OVM saturation
 * flagged) inside the RPTB block only; BANZD delays run each
 * pass: SFTL B,-1 (B = low32(B) >> 1 logical, C = B0, oracle
 * op_shift -- the 2c8a <<1 form is not followed here, oracle
 * wins) then *(AR2--) = B-low. Tail ssbx st1,cpl (hardware,
 * comment only) sets CPL = 1 which propagates into the
 * abutted LEAF43_82D4 head. AR2/AR4/AR6/T/C/AR0/SXM/ASM
 * caller-live dark, flagged; A/B/C clobbered. In ARs/cells;
 * out moved cells/ARs/CPL.
 * EXPECT from the image.
 */
void frag_82D9(void)
{
    long a;  /* clobbered (entry dark) */
    long b;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar4;  /* live-in (dark, flagged) */
    int *ar6;  /* live-in (dark, flagged) */
    int *ar5;
    int ar0;  /* live-in (dark, flagged) */
    int t;  /* T live-in (dark, flagged) */
    int c;  /* C live-in (dark, flagged) */
    int nc;
    int i;

    ar5 = (int *)6;                                          /* stm #6,ar5 */
    b = 0;                                                   /* ld #0,b */
    a = (long)*ar6 << 13;                                    /* ld *ar6,13,a (SXM dark, flagged) */
    *(volatile int *)0x14 = (int)((a >> 16) & 0xFFFFL);       /* sth a,0x14 (ASM dark, flagged) */
    a = 7;                                                   /* ld #7,a */
    a &= (unsigned int)*(ar6--);                             /* and *ar6-,a (zero-extend, oracle) */
    a = -a;                                                  /* neg a */
    *(volatile int *)0x0E = (int)(a & 0xFFFFL);              /* stl a,0x0e */
    ar4 += ar0;                                              /* mar *ar4+0 (AR0 dark, flagged) */
    a = (long)*ar4 << t;                                     /* ld *ar4,ts,a (T dark, flagged) */
    nc = (int)(a & 1L);                                      /* ror a (oracle op_rotate) */
    a = (long)(((unsigned long)a >> 1) | ((unsigned long)c << 31));
    c = nc;
    nc = (int)((b >> 31) & 1L);                              /* rol b */
    b = (long)(((unsigned long)b << 1) | (unsigned long)c);
    c = nc;
    *ar2-- = (int)(b & 0xFFFFL);                             /* stl b,*ar2- */
    do {
        b = 0;                                               /* ld #0,b @82e8 (banzd target) */
        /* stm #7,brc; rptb 0x82f8 */
        a = (long)*ar6 << 13;                                /* rptbd delay ld (runs once) */
        for (i = 0; i < 8; i++) {                            /* rptb block x (BRC+1) */
            *(volatile int *)0x14 = (int)((a >> 16) & 0xFFFFL); /* sth a,0x14 */
            a = 7;                                           /* ld #7,a */
            a &= (unsigned int)*(ar6--);                     /* and *ar6-,a */
            a = -a;                                          /* neg a */
            *(volatile int *)0x0E = (int)(a & 0xFFFFL);      /* stl a,0x0e */
            ar4 += ar0;                                      /* mar *ar4+0 */
            a = (long)*ar4 << t;                             /* ld *ar4,ts,a */
            nc = (int)(a & 1L);                              /* ror a */
            a = (long)(((unsigned long)a >> 1) | ((unsigned long)c << 31));
            c = nc;
            nc = (int)((b >> 31) & 1L);                      /* rol b */
            b = (long)(((unsigned long)b << 1) | (unsigned long)c);
            c = nc;
            b = b << 1;                                      /* sfta b,1 (OVM saturation flagged) */
        }
        nc = (int)(b & 1L);                                  /* banzd delays (run each pass) */
        b = (long)((unsigned long)b >> 1);                   /* sftl b,-1 (oracle op_shift) */
        c = nc;
        *ar2-- = (int)(b & 0xFFFFL);                         /* stl b,*ar2- */
        ar5--;                                               /* banzd 0x82e8,*ar5- */
    } while (ar5 != 0);
    /* ssbx st1,cpl (hardware, no C form; CPL = 1 into LEAF43_82D4) */
    /* abuts LEAF43_82D4 (no own exit) */
}
