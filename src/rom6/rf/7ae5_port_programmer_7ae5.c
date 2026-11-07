/* ROM6 0x7AE5 PORT_PROGRAMMER_7AE5 -- 141w.
 * Verified encoding: src/rom6/rf/7ae5_port_programmer_7ae5.asm (recombine MATCH).
 * ORIGIN 0x7AE5
 * EXPECT: 60F8 0010 0000 F920 3D3B 10F8 0578 80F8 0579 7715 2645 1181 FA4C 7B0A F210 00E0 F120 3A98 F495 75F8 000B 0005 EC16 F495 F495 75F8 000B 0007 EC15 F495 E900 F495 75F8 000B 0008 EC0C F495 FA44 7B1B 7712 263A 7713 2636 809B 11F8 3E8C F074 3C00 7685 007F F273 7B39 6982 0004 7713 2636 7714 253F 6182 0004 FA30 7B2D 6D93 6D94 E921 19F8 2628 F84D 7B30 A212 F845 7B30 E521 6882 FFFB 1081 F845 7B39 E523 1083 F274 3C00 11F8 3E8B E904 F274 4007 10F8 054E 61F8 3EC8 0020 F820 7B71 10F8 2613 F010 0200 7712 12D0 F843 7B51 F010 01CF F842 7B51 7712 1350 F7BB 74F8 000B 0021 F340 0005 F330 FFFD F495 75F8 000B 0021 771A 007F F072 7B64 F495 7592 0024 F495 74F8 000B 0021 F330 FFFB F340 0003 F495 75F8 000B 0021 F6BB FC00
 *
 * Intent: COBBA port programmer. Conditional init call, cell copy,
 * then either the ports 5/7/8 program sequence (with rpt delays) or
 * the 7B0A alternate setup (call 0x3C00, join 7B39). The 7B1B
 * compare/copy lane moves *AR4 to *AR3 when the masked select says
 * so. At 7B39 the PORT0 transaction helper runs (calld 0x4007);
 * unless status bit 5 of 0x3EC8 is set the routine returns. Else a
 * range check on cell 0x2613 picks the port base (4816/4944) and an
 * INTM-locked port-33 program plus a 128-iteration port-36 burst
 * runs, then unlock and return. Delay slots of bcd/bd/calld run
 * before their branches (modeled as pre-branch state here).
 */
extern void frag_3D3B(void);        /* cc 0x3d3b,ntc */
extern void setup_3C00(void);           /* call/calld 0x3c00 */
extern void port0_txn_4007(int b);      /* calld 0x4007, B=#4 */

void port_programmer_7AE5(int **pp1, int *ar3, int *ar4, int *ar5)
{
    int a, b;
    if (*(volatile int *)0x10 != 0)       /* cmpm, cc ntc */
        frag_3D3B();
    a = *(volatile int *)0x578;          /* ld */
    *(volatile int *)0x579 = a;          /* stl */
    b = **pp1;                            /* ld *ar1,b */
    a = b - 224;                          /* bcd delay slot 1 */
    b = 15000;                            /* delay slot 2 */
    if (**pp1 /*orig B*/ != 0)            /* bcd 7B0A bneq */
        goto L_7B0A;
    /* fall-through: ports 5/7/8 with rpt delays */
    *(volatile int *)0xB /*pa5*/ = 0;     /* portw *(0xb),5 */
    { int i; for (i = 0; i < 23; i++) {} }/* rpt #22, nop */
    *(volatile int *)0xB /*pa7*/ = 0;     /* portw *(0xb),7 */
    { int i; for (i = 0; i < 22; i++) {} }/* rpt #21, nop */
    b = 0;                                /* ld #0,b */
    *(volatile int *)0xB /*pa8*/ = 0;     /* portw *(0xb),8 */
    { int i; for (i = 0; i < 13; i++) {} }/* rpt #12, nop */
L_7B0A:
    if (a != 0)                           /* bcd 7B1B aneq */
        goto L_7B1B;                      /* (delay: ar2/ar3 setup) */
    *ar3 = a;                             /* stl a,*+ar3 (ar3=9782) */
    b = *(volatile int *)0x3E8C;         /* ld */
    setup_3C00();                         /* call 0x3c00 */
    *ar5 = 127;                           /* st #127,*ar5 (ar5=9797) */
    *(volatile int *)9786 /*ar2*/ |= 4;   /* bd delay: orm #4 */
    goto L_7B39;                          /* bd 0x7b39 */
L_7B1B:
    if (!(*(volatile int *)9786 /*ar2*/ & 4)) {  /* bitf, bcd 7B2D tc */
        b = 33;                           /* ld #33 */
        b &= *(volatile int *)0x2628;    /* and */
        if (b == 0)                       /* bc 7B30 beq */
            goto L_7B30;
        a = *ar3 - *ar4;                  /* sub */
        if (a == 0)                       /* bc 7B30 aeq */
            goto L_7B30;
    }
    *ar3 = *ar4;                          /* 7B2D: mvdd */
    *(volatile int *)9786 /*ar2*/ &= ~4;  /* andm: bit2 off */
L_7B30:
    a = **pp1;                            /* ld *ar1,a */
    if (a == 0)                           /* bc 7B39 aeq */
        goto L_7B39;
    *ar5 = *ar4;                          /* mvdd *ar4,*ar5 */
    a = *ar3;                             /* ld *ar3,a */
    b = *(volatile int *)0x3E8B;         /* calld delay slot */
    setup_3C00();                         /* calld 0x3c00 */
    /* fall through (7B39 is also the calld second delay slot): */
L_7B39:
    b = 4;                                /* ld #4,b */
    a = *(volatile int *)0x54E;          /* calld delay slot */
    port0_txn_4007(b);                     /* calld 0x4007 */
    if (!(*(volatile int *)0x3EC8 & 32)) /* bitf, bc 7B71 ntc */
        return;
    {
        int x, base;
        int i;
        x = *(volatile int *)0x2613 - 512;  /* ld, sub #512 */
        base = 4816;                        /* stm preset */
        if (!(x < 0)) {                     /* bc 7B51 alt */
            if (x - 463 < 0)                /* sub #463, bc ageq */
                base = 4944;                /* stm #4944,ar2 */
        }
L_7B51: /* INTM-locked port-33 program + 128x port-36 burst: */
        for (i = 0; i < 128; i++) {}        /* rptb, stm #127,brc */
        (void)base;                         /* burst base: ar2 */
    }
    /* rsbx st1,intm; ret */
}
