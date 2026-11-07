/* ROM6 0x3EF3 PORT_CONFIG_3EF3 -- 209w port-init ladder, one EXPECT.
 * Verified encoding: src/rom6/kernel/3ef3_port_config_3ef3.asm (recombine MATCH).
 * ORIGIN 0x3EF3
 * EXPECT: F074 0640 F7BB 7712 0060 7482 0002 6882 FFE7 6982 1804 F495 7582 0002 7682 1387 F495 7582 000E EC12 F495 7182 036A 7682 3A98 F495 7582 000F EC16 F495 F495 7582 0004 EC16 F495 F495 7582 0009 EC16 F495 F495 7582 0005 EC16 F495 F495 7582 0007 EC16 F495 F495 7582 000A EC16 F495 F495 7582 002F EC14 F495 7682 0000 F495 7582 000D EC16 F495 F495 7582 000B EC16 F495 F495 7582 0008 EC16 F495 7482 0000 6982 000D 6882 FE1F F495 7582 0000 EC14 F495 7682 F8FC F495 7582 0001 EC13 F495 F6BB 7682 0000 F495 7582 0020 7692 0482 7682 1482 F495 7582 0021 F495 F495 758A 0021 F495 F495 7582 0021 7713 3E91 F495 7583 002A 7682 00BB F495 7582 0030 7682 0000 F495 7582 0003 EC0E F495 61F8 3EC8 0020 F830 3FC4 60F8 3E7E 0002 10F8 3EB5 F030 0400 7682 02A8 FF30 7682 0280 FF44 7682 06A0 F495 7582 002B 1082 E90B 61F8 3EB5 0400 F495 F495 FF30 F020 06A0 F074 4007 E800 E90D F074 4007 E800 E90E F074 4007 F020 0200 E903 F074 4007 7713 3E8E F495 7583 0025 7713 3E8F F495 7583 0026 7682 01FE F495 7582 0011 EC10 F495 E800 E900 F074 4007 F062 0001 7708 0000 F074 3FFA FC00
 *
 * Intent: RF port power-on ladder plus mode-select writes. Post-RET head
 * after FC00@3EF2 (thin: only a data read `sub *(0x3ef3),a` at A40A
 * references this span, reading its first word as a number). Runs dark
 * SUB_0640 (call; no A/B live after, void). INTM = 1 (hardware; restored
 * mid-span). AR2 window opens at 0x60: *(0x60) = port 2 masked
 * ((port & -25) | 6148: andm/orm) and written back to port 2; then the
 * timed ladder, each rung = store cell + settle nops (rpt counts in
 * comments, 19/23/24/21/20/15/17): port 14 = 4999 with *(0x36A) snapshotted
 * (mvdk *ar2,0x36a); port 15/4/9/5/7/10/47 = 15000; port 13/11/8 = 0;
 * port 0 = (port0 & -481) | 13; port 1 = -1796. INTM = 0. Port 32 = 0;
 * *(0x60)/ *(0x61) = 1154/5250 with an AR2 +1/-1 walk writing port 33 =
 * 5250, 5250, 1154. Port 42 = *(0x3E91) (AR3 = 16017); port 48 = 187;
 * port 3 = 0. Bit 5 of cell 0x3EC8 set exits to exterior FRAG_3FC4
 * (bitf + bc tc: *(0x60) = 640, port 43 = 640, continues exterior --
 * forward extern, 3-word head transcribed in its note). Else mode lane:
 * value = bit10-of-0x3EB5-set ? 1696 : (cell 0x3E7E == 2 ? 680 : 640)
 * (cmpm TC + and-mask A, xc-skipped stores; XC skips WORDS per op_xc;
 * TC reads survive ld/and/st per op_cmpm/memory rules); port 43 = value.
 * Four SUB_4007 transactions with (A, 11/13/14/3) = (value-or-1696, 0, 0,
 * 512) (call, C: sub_4007 per 3FC4). Port 37/38 = *(0x3E8E)/ *(0x3E8F)
 * (AR3 pair). Port 17 = 510. SUB_4007(0, 0). A = 0x10000 (ld #1,16,a;
 * stm #0,al is a no-op: A-low already 0); runs ROUTINE_3FFA (call, C:
 * routine_3FFA: AH = 1, AL = 0). RET @3FC3. Ports direct-mapped
 * (extern ops per 2ACC). Bound 3EF3-3FC3.
 */
extern void sub_0640(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern int sub_4007(int a_in, int b_in); /* joins 4007_port0_txn; see docs/evidence/extern-triage.md */
extern void routine_3FFA(int a_live);
extern void frag_3FC4(void);
extern int port_read_2(void);                                         /* HW port 2 (FRAME sample combine per 27EB span); no ROM definition */
extern int port_read_0(void);                                         /* HW port 0 (codec/RF control per 938c homology); no ROM definition */
extern void port_write_2(int v);                                      /* HW port 2 (supervisor per 2875 precedent); no ROM definition */
extern void port_write_14(int v);                                     /* HW port 14 (RF per 3EE1 span, 4999 preset); no ROM definition */
extern void port_write_15(int v);
extern void port_write_4(int v);                                      /* HW port 4 (RF per 3cd2 port4850 seq); no ROM definition */
extern void port_write_9(int v);                                      /* HW port 9 (RF per 389c/3d79 spans); no ROM definition */
extern void port_write_5(int v);                                      /* HW port 5 (RF sweep per 3EE1 span); no ROM definition */
extern void port_write_7(int v);                                      /* HW port 7 (RF sweep per 3EE1 span); no ROM definition */
extern void port_write_10(int v);                                     /* HW port 10 (RF per 3d79/3EE1 spans); no ROM definition */
extern void port_write_47(int v);                                     /* HW port 47 (RF per 3EE1/4a19 spans); no ROM definition */
extern void port_write_13(int v);                                     /* HW port 13 (RF per 3EE1/44af spans); no ROM definition */
extern void port_write_11(int v);                                     /* HW port 11 (RF per 3e53 sweep + 3ef3 config spans); no ROM definition */
extern void port_write_8(int v);                                      /* HW port 8 (RF per 389c/3EE1 spans); no ROM definition */
extern void port_write_0(int v);                                      /* HW port 0 (codec/RF control per 938c homology); no ROM definition */
extern void port_write_1(int v);                                      /* HW port 1 (RF/codec per 3EE1 sweep); no ROM definition */
extern void port_write_32(int v);                                     /* HW port 32 (RF per 3ef3 span); no ROM definition */
extern void port_write_33(int v);                                     /* HW port 33 (SAMPLE handshake per 22F3 span); no ROM definition */
extern void port_write_42(int v);                                     /* HW port 42 (RF per 3EE1 span); no ROM definition */
extern void port_write_48(int v);                                     /* HW port 48 (RF per 22F3/3cd2 spans); no ROM definition */
extern void port_write_3(int v);                                      /* HW port 3 (supervisor cell per 2088 span); no ROM definition */
extern void port_write_43(int v);                                     /* HW port 43 (RF per 3e53 sweep); no ROM definition */
extern void port_write_37(int v);                                     /* HW port 37 (RF per 3ef3 span); no ROM definition */
extern void port_write_38(int v);                                     /* HW port 38 (RF per 3ef3 span); no ROM definition */
extern void port_write_17(int v);                                     /* HW port 17 (RF per 3ef3 span); no ROM definition */

void port_config_3EF3(void)
{
    long a;
    long b;
    int tc;
    int value;
    int *par2w = (int *)96;                      /* stm #96,ar2 */
    int *par3;

    sub_0640();                                        /* call 0x640 */
    /* ssbx intm (hardware, no C form) */
    *par2w = port_read_2();                       /* portr pa2,*ar2 */
    *par2w &= -25;                            /* andm #-25,*ar2 */
    *par2w |= 6148;                            /* orm #6148,*ar2 */
    /* nop */
    port_write_2(*par2w);                          /* portw *ar2,pa2 */
    *par2w = 4999;                            /* st #4999,*ar2 */
    /* nop */
    port_write_14(*par2w);                        /* portw *ar2,pa14 */
    /* rpt #18 nop: 19 settle cycles */
    *(volatile int *)0x36A = *par2w;         /* mvdk *ar2,0x36a */
    *par2w = 15000;                          /* st #15000,*ar2 */
    /* nop */
    port_write_15(*par2w);                        /* portw *ar2,pa15 */
    /* rpt #22 + nop: 24 settle cycles */
    port_write_4(*par2w);                          /* portw *ar2,pa4 */
    /* 24 settle cycles */
    port_write_9(*par2w);                          /* portw *ar2,pa9 */
    /* 24 settle cycles */
    port_write_5(*par2w);                          /* portw *ar2,pa5 */
    /* 24 settle cycles */
    port_write_7(*par2w);                          /* portw *ar2,pa7 */
    /* 24 settle cycles */
    port_write_10(*par2w);                        /* portw *ar2,pa10 */
    /* 24 settle cycles */
    port_write_47(*par2w);                        /* portw *ar2,pa47 */
    /* rpt #20 nop: 21 settle cycles */
    *par2w = 0;                                    /* st #0,*ar2 */
    /* nop */
    port_write_13(*par2w);                        /* portw *ar2,pa13 */
    /* 24 settle cycles */
    port_write_11(*par2w);                        /* portw *ar2,pa11 */
    /* 24 settle cycles */
    port_write_8(*par2w);                          /* portw *ar2,pa8 */
    /* rpt #22 nop: 23 settle cycles */
    *par2w = port_read_0();                       /* portr pa0,*ar2 */
    *par2w |= 13;                              /* orm #13,*ar2 */
    *par2w &= -481;                           /* andm #-481,*ar2 */
    /* nop */
    port_write_0(*par2w);                          /* portw *ar2,pa0 */
    /* rpt #20 nop: 21 settle cycles */
    *par2w = -1796;                           /* st #-1796,*ar2 */
    /* nop */
    port_write_1(*par2w);                          /* portw *ar2,pa1 */
    /* rpt #19 nop: 20 settle cycles */
    /* rsbx intm (hardware, no C form) */
    *par2w = 0;                                    /* st #0,*ar2 */
    /* nop */
    port_write_32(*par2w);                        /* portw *ar2,pa32 */
    *par2w++ = 1154;                          /* st #1154,*ar2+ */
    *par2w = 5250;                            /* st #5250,*ar2 (=0x61) */
    /* nop */
    port_write_33(*par2w);                        /* portw *ar2,pa33 */
    /* nop; nop */
    port_write_33(*par2w);                      /* portw *ar2-,pa33 */
    par2w--;                                           /* AR2 -> 0x60 */
    /* nop; nop */
    port_write_33(*par2w);                        /* portw *ar2,pa33 */
    par3 = (int *)16017;                      /* stm #16017,ar3 */
    /* nop */
    port_write_42(*par3);                         /* portw *ar3,pa42 */
    *par2w = 187;                               /* st #187,*ar2 */
    /* nop */
    port_write_48(*par2w);                        /* portw *ar2,pa48 */
    *par2w = 0;                                    /* st #0,*ar2 */
    /* nop */
    port_write_3(*par2w);                          /* portw *ar2,pa3 */
    /* rpt #14 nop: 15 settle cycles */
    tc = (*(volatile int *)0x3EC8 & 32) != 0;          /* bitf */
    if (tc) {                                          /* bc 0x3fc4,tc */
        frag_3FC4();
        return;
    }
    tc = (*(volatile int *)0x3E7E == 2);               /* cmpm */
    a = (long)*(volatile int *)0x3EB5;                 /* ld */
    a &= 1024;                                         /* and #1024,a */
    *par2w = 680;                               /* st #680,*ar2 */
    if (!tc)                                           /* xc 2,tc */
        *par2w = 640;                           /* st #640,*ar2 */
    if (a != 0)                                        /* xc 2,aneq */
        *par2w = 1696;                          /* st #1696,*ar2 */
    value = *par2w;
    /* nop */
    port_write_43(value);                       /* portw *ar2,pa43 */
    a = (long)*par2w;                                    /* ld *ar2,a */
    b = 11;                                              /* ld #11,b */
    tc = (*(volatile int *)0x3EB5 & 1024) != 0;          /* bitf */
    /* nop; nop */
    if (!tc)                                           /* xc 2,tc */
        a = 1696;                                      /* ld #1696,a */
    sub_4007((int)a, (int)b);                          /* call 0x4007 */
    sub_4007(0, 13);                                   /* call 0x4007 */
    sub_4007(0, 14);                                   /* call 0x4007 */
    sub_4007(512, 3);                                  /* call 0x4007 */
    par3 = (int *)16014;                      /* stm #16014,ar3 */
    /* nop */
    port_write_37(*par3);                         /* portw *ar3,pa37 */
    par3 = (int *)16015;                      /* stm #16015,ar3 */
    /* nop */
    port_write_38(*par3);                         /* portw *ar3,pa38 */
    *par2w = 510;                               /* st #510,*ar2 */
    /* nop */
    port_write_17(*par2w);                        /* portw *ar2,pa17 */
    /* rpt #16 nop: 17 settle cycles */
    sub_4007(0, 0);                                    /* call 0x4007 */
    a = 1L << 16;                                      /* ld #1,16,a */
    /* stm #0,al (A-low already 0, no-op) */
    routine_3FFA((int)a);                        /* call 0x3ffa */
    /* ret @0x3fc3 */
}
