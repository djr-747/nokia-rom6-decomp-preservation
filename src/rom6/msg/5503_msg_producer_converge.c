/* ROM6 0x5503 MSG_PRODUCER_CONVERGE -- 174w.
 * Verified encoding: src/rom6/msg/5503_msg_producer_converge.asm (recombine MATCH).
 * ORIGIN 0x5503
 * EXPECT: 7712 254A 7713 2513 EC07 E589 61F8 054F 0010 F820 551C 71F8 2576 253F 60F8 250F 0022 F820 5519 71F8 34CB 34CA 68F8 054F FFEF 61F8 054F 0200 F820 5529 7712 2577 7713 2540 E501 68F8 054F FDFF 7712 2552 7713 251B EC1F E589 61F8 3EC8 0040 F495 F495 FF30 EC03 E589 10F8 056D 74F8 000B 0038 F340 0010 F844 5542 F330 FFEF F495 75F8 000B 0038 68F8 2627 6170 68F8 2512 FF7B 10F8 2477 F074 56DE F074 56FC 7711 2627 1181 F330 BFFF 60F8 2476 0003 F820 5561 68F8 054F FFFB F340 4000 8181 10F8 250F F130 00F0 F210 0020 76F8 0573 A249 F844 55EF F074 06E6 60F8 250F 002F F820 5577 76F8 0573 AF57 10F8 250F F030 00FE 60F8 0008 0020 F820 5583 76F8 0573 AFAB 60F8 250F 0022 F820 558B 76F8 0573 B16C 60F8 2547 00C3 F820 5596 76F8 0573 B11C 76F8 2510 00C1 76F8 056F 00B0 69F8 2512 0080 7711 250D 60F8 250F 0022 F820 55B1 76F8 2652 0019 76F8 2653 000C 76F8 2651 0000 76F8 2640 000C F073 5683
 *
 * Intent: RF-tune converge chain. Copies 8 words 0x254A to 0x2513 (rpt/mvdd loop); bit 4 of cell 0x54F clear rejoins at 0x551C (bc ntc). Else moves cell 0x2576 to 0x253F (mvdk, dmad is destination); cell 0x250F != 34 rejoins at 0x5519 (cmpm ntc); else moves cell 0x34CB to 0x34CA; rejoins and clears bit 4 of 0x54F. Bit 9 of 0x54F clear rejoins at 0x5529; else single-word copy 0x2577 to 0x2540 and clears bit 9. Copies 32 words 0x2552 to 0x251B (rpt/mvdd loop). TC = bit 6 of cell 0x3EC8 (bitf, two settle nops); TC set also copies 4 more words (xc 2,tc over rpt/mvdd: exact skip per 4EBC precedent). A = cell 0x56D; B = port 56 (BL alias) OR 16; A != 0 rejoins at 0x5542 (bc aneq); else B &= -17, out to port 56; rejoins. AND-masks cells 0x2627/0x2512. A = cell 0x2477 into C PORTXACT_ENTRY_56DE (call, C-bound); dark SUB_56FC. B = cell 0x2627 AND -16385; cell 0x2476 != 3 rejoins at 0x5561; else clears bit 2 of 0x54F and sets B bit 14; stores B low to 0x2627. A = (cell 0x250F AND 240); A -= 32 (SUB #lk form: A = B - (lk << 0) per ti-c54x op_sub_lk); stores -23991 to 0x573; A != 0 runs unbound FRAG_55EF with B live (bc aneq, forward extern; B = A AND 240 per its entry SUB). Else dark SUB_06E6, then a masked-compare ladder over cells 0x250F/0x8/0x2547 storing tune keys (-20649/-20565/-20116/-20196) to 0x573, or rejoins at each mismatch (0x5577/0x5583/0x558B/0x5596 in-span). Then cell 0x2510 = 193, 0x56F = 176, bit 7 of 0x2512 set, AR1 = 0x250D; cell 0x250F != 34 runs C FRAG_55B1 with AR1 (bc ntc, C-bound); else cells 0x2652/0x2653/0x2651/0x2640 = 25/12/0/12, tail-enters C FRAG_5683 (b, C-bound). Port 56 direct-mapped. Bound 5503-55B0.
 */
extern int port_read_56(void);
extern void port_write_56(int v);
extern void portxact_entry_56DE(int a_in);
extern void sub_56FC(void);
extern void sub_06E6(void);
extern void frag_55B1(int *par1);
extern void frag_55EF(int b_live);
extern void frag_5683(void);

void frag_5503(void)
{
    int a, b, i;
    int *ar1, *ar2, *ar3;
    ar2 = (int *)(long)0x254A;                     /* stm */
    ar3 = (int *)(long)0x2513;                     /* stm */
    for (i = 0; i < 8; i++) {                      /* rpt #7 */
        *ar3++ = *ar2++;                           /* mvdd *ar2+,*ar3+ */
    }
    if ((*(volatile int *)0x54F & 16) == 0) {  /* bitf, bc ntc */
        goto l551c;
    }
    *(volatile int *)0x253F = *(volatile int *)0x2576; /* mvdk */
    if (*(volatile int *)0x250F != 34) {        /* cmpm, bc ntc */
        goto l5519;
    }
    *(volatile int *)0x34CA = *(volatile int *)0x34CB; /* mvdk */
l5519:
    *(volatile int *)0x54F &= -17;             /* andm */
l551c:
    if ((*(volatile int *)0x54F & 512) == 0) { /* bitf, bc ntc */
        goto l5529;
    }
    ar2 = (int *)(long)0x2577;
    ar3 = (int *)(long)0x2540;
    *ar3 = *ar2;                                   /* mvdd single */
    *(volatile int *)0x54F &= -513;            /* andm */
l5529:
    ar2 = (int *)(long)0x2552;
    ar3 = (int *)(long)0x251B;
    for (i = 0; i < 32; i++) {                     /* rpt #31 */
        *ar3++ = *ar2++;                           /* mvdd *ar2+,*ar3+ */
    }
    {
        int tc = (*(volatile int *)0x3EC8 & 64) != 0; /* bitf */
        /* nop; nop */
        if (tc) {                                  /* xc 2,tc */
            for (i = 0; i < 4; i++) {              /* rpt #3 */
                *ar3++ = *ar2++;                   /* mvdd */
            }
        }
    }
    a = *(volatile int *)0x56D;                /* ld */
    b = port_read_56();                            /* portr 56,*(0xb) */
    *(volatile int *)0xB = b;                  /* BL alias write */
    b |= 16;                                       /* or #16,b */
    if (a == 0) {                                  /* bc 0x5542,aneq skips */
        b &= -17;                                  /* and #-17,b */
        /* nop */
        port_write_56(b);                          /* portw *(0xb),56 */
    }
/* l5542: nop rejoin */
    *(volatile int *)0x2627 &= 24944;          /* andm */
    *(volatile int *)0x2512 &= -133;           /* andm */
    a = *(volatile int *)0x2477;               /* ld */
    portxact_entry_56DE(a);                        /* call 0x56de */
    sub_56FC();                                    /* call 0x56fc */
    ar1 = (int *)(long)0x2627;                     /* stm #9767,ar1 */
    b = *ar1;                                      /* ld *ar1,b */
    b &= -16385;                                   /* and #-16385,b */
    if (*(volatile int *)0x2476 != 3) {        /* cmpm, bc ntc */
        goto l5561;
    }
    *(volatile int *)0x54F &= -5;             /* andm */
    b |= 16384;                                    /* or #16384,b */
l5561:
    *ar1 = b;                                      /* stl b,*ar1 */
    a = *(volatile int *)0x250F;               /* ld */
    b = a & 240;                                   /* and #240,a,b */
    a = b - 32;                                    /* sub #32,b,a (SHFT 0) */
    *(volatile int *)0x573 = -23991;           /* st */
    if (a != 0) {                                  /* bc 0x55ef,aneq */
        frag_55EF(b);                              /* away, B live */
        return;
    }
    sub_06E6();                                    /* call 0x6e6 */
    if (*(volatile int *)0x250F != 47) {       /* cmpm, bc ntc */
        goto l5577;
    }
    *(volatile int *)0x573 = -20649;           /* st */
l5577:
    a = *(volatile int *)0x250F;               /* ld */
    a &= 254;                                      /* and #254,a */
    if (*(volatile int *)0x8 != 32) {          /* cmpm *(0x8), bc ntc */
        goto l5583;                                /* *(0x8): port-56 AL residue */
    }
    *(volatile int *)0x573 = -20565;           /* st */
l5583:
    if (*(volatile int *)0x250F != 34) {       /* cmpm, bc ntc */
        goto l558b;
    }
    *(volatile int *)0x573 = -20116;           /* st */
l558b:
    if (*(volatile int *)0x2547 != 195) {      /* cmpm, bc ntc */
        goto l5596;
    }
    *(volatile int *)0x573 = -20196;           /* st */
l5596:
    *(volatile int *)0x2510 = 193;             /* st */
    *(volatile int *)0x56F = 176;              /* st */
    *(volatile int *)0x2512 |= 128;            /* orm */
    ar1 = (int *)(long)0x250D;                     /* stm #9485,ar1 */
    if (*(volatile int *)0x250F != 34) {       /* cmpm, bc ntc */
        frag_55B1(ar1);                            /* away, C-bound */
        return;
    }
    *(volatile int *)0x2652 = 25;              /* st */
    *(volatile int *)0x2653 = 12;              /* st */
    *(volatile int *)0x2651 = 0;               /* st */
    *(volatile int *)0x2640 = 12;              /* st */
    frag_5683();                                   /* b 0x5683 tail */
}
