/* ROM6 0x5905 FRAG_5905 -- 142w mode gate with twin 0x58E0 calls.
 * Verified encoding: src/rom6/kernel/5905_frag_5905.asm (recombine MATCH).
 * ORIGIN 0x5905
 * EXPECT: F074 059C 60F8 250F 0021 F820 591D 60F8 2510 00C0 F830 5916 60F8 2510 00B1 F820 591D 10F8 0060 F845 591D 76F8 264D 0002 10F8 0060 F845 5931 7710 2510 6080 00D3 F830 5931 1080 F030 00F0 F010 00D0 F844 5931 76F8 24F4 0070 62F8 261F 0039 60F8 250F 0022 F820 593D 7210 352D F073 593F 7710 02C2 F274 58E0 7714 0160 E804 00F8 261F 62F8 0008 0039 60F8 250F 0022 F820 5952 7210 352D F073 5954 7710 02C2 F274 58E0 7714 0161 7710 261F E801 0080 F110 0003 61F8 3EB5 0200 F820 596C 61F8 0586 0002 FD4E E800 F820 596C F300 0002 7711 2F02 FF4F 7681 0000 61F8 3EB5 0200 F830 5978 FD4E E800 8080 10F8 250F F030 00F0 60F8 0008 0020 F830 5991 61F8 3EB5 0200 F820 598C 61F8 0586 0002 F830 5991 7715 2627 FF4E 6885 FDFF E800 FC00
 *
 * Intent: Runs dark SUB_059C (call, void per 4EE0/4FF6). Every bc/xc
 * target is an in-span join and the span has a single ret, so the C is a
 * straight if-nest. Cell 0x250F == 33 with cell 0x2510 == 192 or == 177
 * (cmpm pair) arms the store: A = cell 0x60 nonzero stores 2 to cell
 * 0x264D (st); all paths rejoin at 0x591D. There A = cell 0x60; nonzero
 * with *AR0 (9488, local) != 211 (cmpm) and (*AR0 & 240) - 208 == 0
 * stores 112 to cell 0x24F4. At 0x5931: A = cell 0x261F times 57 (mpy
 * Smem,#lk,adst per ti-c54x op_mpy_smem_lk: signed 16x16; T clobbered,
 * noted). AR0 = cell 0x250F != 34 ? 706 : cell 0x352D (mvdm; bc ntc
 * rejoins at 0x593F either way). Runs opaque SUB_58E0 with A-live (calld;
 * has .asm with rptbd, forward extern void sub_58E0(int a_live); delay
 * stm AR4 = 352/353 dead presets, noted). A = 4 + cell 0x261F (ld, add
 * Smem sign-extended); A = cell(DP 8) times 57 (mpy). Same AR0 select
 * rejoins at 0x5954; runs SUB_58E0 with A-live again. AR0 = 9759 (stm,
 * local); A = 1 + *AR0 (ld, add); B = A - 3 (sub). Bit 9 of cell 0x3EB5
 * set with bit 1 of cell 0x586 set zeroes A when B > 0 (bitf pair, xc
 * 1,bgt over ld #0,a) and adds 2 to B; any clear bit rejoins 0x596C
 * without the add. There AR1 = 12034 (stm, local); B <= 0 zeroes *AR1
 * (xc 2,bleq over the st). Bit 9 of cell 0x3EB5 set, else B > 0 zeroes A
 * (xc 1,bgt), both rejoin 0x5978. There *AR0 = A-low (stl; AR0 still
 * 9759). A = cell 0x250F & 240 (ld, and); cell(DP 8) != 32 with (bit 9
 * clear or bit 1 of 0x586 clear) clears bit 9 of cell 9767 (AR5 = 9767
 * local; xc 2,bgt over andm #-513). A = 0, returns. A/B internal;
 * AR0/AR1/AR5 cursor locals. Bound 5905-5992 (exit FC00@5992).
 */
extern void sub_059C(void);
extern void sub_58E0(int a_live);

void frag_5905(void)
{
    long a;
    long b;
    int *par0;

    sub_059C();                                        /* call 0x59c */
    if (*(volatile int *)0x250F == 33 &&               /* cmpm; bc ntc */
        (*(volatile int *)0x2510 == 192 ||             /* cmpm; bc tc */
         *(volatile int *)0x2510 == 177)) {           /* cmpm; bc ntc */
        /* 0x5916 arm (falls into 0x591d) */
        a = (long)*(volatile int *)0x60;               /* ld *(0x60),a */
        if (a != 0)                                    /* bc 0x591d,aeq */
            *(volatile int *)0x264D = 2;               /* st #2 */
    }
    /* 0x591d join (universal) */
    a = (long)*(volatile int *)0x60;                   /* ld *(0x60),a */
    if (a != 0) {                                      /* bc 0x5931,aeq */
        par0 = (int *)9488;                            /* stm #9488,ar0 */
        if (*par0 != 211) {                            /* cmpm; bc tc */
            a = (long)(*par0 & 240);                   /* ld/and #240 */
            a -= 208L;                                 /* sub #208,a */
            if (a == 0)                                /* bc 0x5931,aneq */
                *(volatile int *)0x24F4 = 112;         /* st #112 */
        }
    }
    /* 0x5931 join (universal) */
    a = (long)*(volatile int *)0x261F * 57L;           /* mpy Smem,#57,a */
    if (*(volatile int *)0x250F != 34)                 /* cmpm; bc ntc */
        par0 = (int *)706;                             /* 0x593d */
    else
        par0 = (int *)(long)*(volatile int *)0x352D;   /* mvdm 0x352d */
    /* 0x593f join */
    /* calld 0x58e0 (delay AR4 = 352 dead preset, noted) */
    sub_58E0((int)a);
    a = 4L + (long)*(volatile int *)0x261F;           /* ld/add Smem */
    a = (long)*(volatile int *)0x8 * 57L;              /* mpy *(0x8),#57 */
    if (*(volatile int *)0x250F != 34)                 /* cmpm; bc ntc */
        par0 = (int *)706;                             /* 0x5952 */
    else
        par0 = (int *)(long)*(volatile int *)0x352D;   /* mvdm 0x352d */
    /* 0x5954 join */
    /* calld 0x58e0 (delay AR4 = 353 dead preset, noted) */
    sub_58E0((int)a);
    par0 = (int *)9759;                                /* stm #9759,ar0 */
    a = 1L + (long)*par0;                              /* ld #1; add */
    b = a - 3L;                                        /* sub #3,a,b */
    if ((*(volatile int *)0x3EB5 & 512) &&             /* bitf; bc ntc */
        (*(volatile int *)0x586 & 2)) {                /* bitf; bc ntc */
        if (b > 0)                                     /* xc 1,bgt */
            a = 0;                                     /* ld #0,a */
        b += 2L;                                       /* add #2,b */
    }
    /* 0x596c join (universal) */
    {
        int *par1 = (int *)12034;                      /* stm #12034,ar1 */
        if (b <= 0)                                    /* xc 2,bleq */
            *par1 = 0;                                 /* st #0,*ar1 */
    }
    if ((*(volatile int *)0x3EB5 & 512) == 0) {        /* bitf; bc tc */
        if (b > 0)                                     /* xc 1,bgt */
            a = 0;                                     /* ld #0,a */
    }
    /* 0x5978 join (universal) */
    *par0 = (int)(a & 0xFFFF);                         /* stl a,*ar0 */
    a = (long)*(volatile int *)0x250F;                 /* ld *(0x250f),a */
    a &= 240L;                                         /* and #240,a */
    if (*(volatile int *)0x8 != 32 &&                   /* cmpm; bc tc */
        ((*(volatile int *)0x3EB5 & 512) == 0 ||       /* bitf; bc ntc */
         (*(volatile int *)0x586 & 2) == 0)) {          /* bitf; bc tc */
        /* 0x598c */
        int *par5 = (int *)9767;                       /* stm #9767,ar5 */
        if (b > 0)                                     /* xc 2,bgt */
            *par5 &= -513;                             /* andm #-513 */
    }
    /* 0x5991 join (universal) */
    a = 0;                                             /* ld #0,a */
    (void)a; (void)b;
    /* ret */
}
