/* ROM6 0x2000 BRINGUP_INIT_2000 -- 136w.
 * Verified encoding: src/rom6/boot/2000_bringup_init_2000.asm (recombine MATCH).
 * ORIGIN 0x2000
 * EXPECT: F074 0598 61F8 058F 000F F820 200D 76F8 2453 0000 E801 F981 AA1D 69F8 058F 0080 E904 F074 B4A8 F274 2282 7712 0004 F830 202D 68F8 0537 FD9F F274 2282 7712 0008 F830 2029 68F8 0537 FFF7 F074 2262 F074 226C F274 2262 7712 0003 61F8 3EB5 0200 F820 2035 76F8 0586 0000 F7BB 68F8 0552 E800 76F8 0553 01F8 F020 2F00 F274 207E F120 347D F020 2456 F274 207E F120 2666 F020 0912 F274 207E F120 0925 76F8 2654 0004 F020 FFFF 80F8 2636 80F8 253F 80F8 2576 7712 051D 6182 0800 6882 FFDF FF30 6982 0020 7710 0524 EC02 7090 BB78 E800 68F8 051C FFFC 68F8 051F E7FF 80F8 0566 80F8 050B 68F8 051D F8BF F074 3EF3 69F8 0000 0001 F074 77EE F073 2088 F6B8 F520 891A 8813 E800 F072 2085 8093 F7B8 FC00
 *
 * Intent: Low-ROM bring-up init with dispatcher tail. Runs RAM-resident SUB_0598 (forward extern);
 * cell 0x58F low-nibble clear skips the 0x2453 clear (bc ntc). A = 1; far call into uploaded page
 * far_1AA1D (fcall, permanently extern); cell 0x58F bit 7 set (orm). B = 4; runs dark SUB_B4A8
 * (forward extern, asm-only). Two calld-2282 lanes (delay stm AR2 = 4/8 runs first): TC dark-callee-live
 * (unbound, flagged) taken joins 202D/2029, else andm cell 0x537. Runs SUB_2262/SUB_226C (forward externs,
 * C-bound below); third calld-2262 lane (delay AR2 = 3). TC = cell 0x3EB5 bit 9 (bitf); clear joins 2035
 * (bc ntc); else cell 0x586 cleared. INTM guard (ssbx, hardware); cells 0x552/0x553 staged. Three
 * frag_207E fill calls with (A,B) presets ((12032,13437), (9302,9830), (2322,2341); delay ld B runs first).
 * Cell 0x2654 = 4; A = -1 (ld); cells 0x2636/0x253F/0x2576 = 0xFFFF (stl). AR2 = 1309; TC = bit 11;
 * cell &= -33 (andm); TC taken sets bit 5 (xc/orm). AR0 = 1316; 3x mvkd *0xBB78 fill (rpt #2). A = 0;
 * cells andm/cleared; port_config_3EF3(); cell 0 bit 0 set (orm); zerofill_retd(); tail-joins frag_2088
 * (b; next span). Subroutine frag_207E(A,B): SXM guards (hardware comments); B -= A (sub); BRC = B-low;
 * AR3 = A-low; A = 0; (BRC+1)x zero stores (rptb); return. AR2 presets before calld-2282 lanes die in-span
 * (2282 never reads AR2, flagged). Entry: tail-branch b @0x303D (PROM). No caller-live regs.
 */
extern void sub_0598(void);
extern void far_1AA1D(void);
extern void sub_B4A8(void);
extern void sub_2282(void);
extern void sub_2262(void);
extern void sub_226C(void);
extern void port_config_3EF3(void);
extern void zerofill_retd(void);
extern void frag_2088(void);

void frag_207E(long a_live, long b_live)
{
    long a;
    long b;
    int *ar3;
    int brc;
    int i;

    a = a_live;
    b = b_live;
    /* rsbx st1,sxm (hardware, no C form) */
    b = b - a;                                               /* sub a,b */
    brc = (int)(b & 0xFFFF);                                /* stlm b,brc */
    ar3 = (int *)(long)(a & 0xFFFF);                        /* stlm a,ar3 */
    a = 0;                                                   /* ld #0,a */
    for (i = 0; i <= brc; i++)                              /* rptb 0x2085 */
        *ar3++ = (int)(a & 0xFFFF);                         /* stl a,*ar3+ */
    /* ssbx st1,sxm (hardware, no C form) */
    /* ret @2087 */
}

void frag_2000(void)
{
    long a;
    long b;
    int *ar2;
    int *ar0loc;
    int taken;
    int tc_dark;  /* TC dark-callee-live (unbound, flagged) */
    int i;

    sub_0598();                                            /* call 0x598 (RAM) */
    if ((*(volatile int *)0x58F & 15) == 0)                 /* bitf; bc 0x200d,ntc */
        goto l200d;
    *(volatile int *)0x2453 = 0;                           /* st #0,*(0x2453) */
l200d:
    a = 1;                                                 /* ld #1,a */
    far_1AA1D();                                           /* fcall 0x1aa1d (uploaded) */
    *(volatile int *)0x58F |= 128;                         /* orm #128 */
    b = 4;                                                 /* ld #4,b */
    sub_B4A8();                                            /* call 0xb4a8 (dark) */
    ar2 = (int *)4;                                        /* calld delay: stm (runs first) */
    sub_2282();                                            /* calld 0x2282 */
    taken = tc_dark;                                       /* bc 0x202d,tc (unbound) */
    if (taken)
        goto l202d;
    *(volatile int *)0x537 &= -609;                         /* andm #-609 */
    ar2 = (int *)8;                                        /* calld delay: stm */
    sub_2282();                                            /* calld 0x2282 */
    taken = tc_dark;                                       /* bc 0x2029,tc (unbound) */
    if (taken)
        goto l2029;
    *(volatile int *)0x537 &= -9;                           /* andm #-9 */
    sub_2262();                                            /* call 0x2262 */
    sub_226C();                                            /* call 0x226c */
l2029:
    ar2 = (int *)3;                                        /* calld delay: stm */
    sub_2262();                                            /* calld 0x2262 */
l202d:
    taken = (*(volatile int *)0x3EB5 & 512) != 0;          /* bitf *(0x3eb5),#512 */
    if (!taken)                                            /* bc 0x2035,ntc */
        goto l2035;
    *(volatile int *)0x586 = 0;                             /* st #0,*(0x586) */
l2035:
    /* ssbx st1,intm (hardware, no C form) */
    *(volatile int *)0x552 &= -6144;                        /* andm #-6144 */
    *(volatile int *)0x553 = 504;                           /* st #504,*(0x553) */
    frag_207E(12032L, 13437L);                             /* ld; calld (delay ld B first) */
    frag_207E(9302L, 9830L);                               /* ld; calld */
    frag_207E(2322L, 2341L);                               /* ld; calld */
    *(volatile int *)0x2654 = 4;                            /* st #4,*(0x2654) */
    a = -1;                                                /* ld #-1,a */
    *(volatile int *)0x2636 = (int)(a & 0xFFFF);           /* stl a (0xFFFF) */
    *(volatile int *)0x253F = (int)(a & 0xFFFF);           /* stl a */
    *(volatile int *)0x2576 = (int)(a & 0xFFFF);           /* stl a */
    ar2 = (int *)1309;                                     /* stm #1309,ar2 */
    taken = (*ar2 & 2048) != 0;                            /* bitf *ar2,#2048 */
    *ar2 &= -33;                                            /* andm (always runs) */
    if (taken)                                             /* xc 2,tc */
        *ar2 |= 32;                                        /* orm #32,*ar2 */
    ar0loc = (int *)1316;                                  /* stm #1316,ar0 */
    for (i = 0; i < 3; i++)                                /* rpt #2 */
        *ar0loc++ = *(volatile int *)0xBB78;                /* mvkd 0xbb78,*ar0+ */
    a = 0;                                                 /* ld #0,a */
    *(volatile int *)0x51C &= -4;                           /* andm #-4 */
    *(volatile int *)0x51F &= -6145;                        /* andm #-6145 */
    *(volatile int *)0x566 = (int)(a & 0xFFFF);            /* stl a (A = 0) */
    *(volatile int *)0x50B = (int)(a & 0xFFFF);            /* stl a */
    *(volatile int *)0x51D &= -1857;                       /* andm #-1857 */
    port_config_3EF3();                                    /* call 0x3ef3 */
    *(volatile int *)0x0 |= 1;                              /* orm #1,*(0x0) */
    zerofill_retd();                                       /* call 0x77ee */
    frag_2088();                                           /* b 0x2088 (tail) */
    (void)ar2; (void)tc_dark;
}
