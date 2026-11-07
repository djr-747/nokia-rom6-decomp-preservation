/* ROM6 0x22F3 SAMPLE_ISR_BODY_22F3 -- 765w.
 * Verified encoding: src/rom6/boot/22f3_sample_isr_body_22f3.asm (recombine MATCH).
 * ORIGIN 0x22F3
 * EXPECT: 4807 F030 2000 F040 4900 8807 74F8 0008 0021 F040 0C00 7212 022A 75F8 0008 0021 7713 021E 6C8A 2439 7712 022C 6082 0001 F830 2468 6082 0002 F830 257D 7711 0228 7719 0010 ED00 7715 3EBD 7710 0002 7716 0200 7714 0204 771A 0007 F272 2343 7712 01F4 74D6 0027 A43A A5BE B336 B0BE 74D6 0027 B03A B3BE B336 B0BE 74D6 0027 B03A B3BE B336 B0BE 74D6 0027 B03A B3BE B736 D6E1 6DDC 6DED FFF9 4092 5781 E210 E2E4 4F81 F074 05DC 7713 022F E801 0883 FA44 2437 F484 8083 7713 022C 6183 0008 FA20 242C 7712 022D F67D F074 4315 61F8 3EC8 0020 F820 23F2 7712 3E98 F784 3F82 61F8 263B 0004 7713 0474 FF20 7713 049C 42E3 0003 FA47 238F E801 F495 42E3 0004 FA47 238F E803 F495 42E3 0005 FA47 238F E804 F495 42E3 0006 FA47 238F E805 F495 42E3 0007 FA47 238F E806 F495 42E3 0008 FA47 238F E807 F495 E808 80F8 022D F000 3EEA 8813 F495 F495 1083 60F8 022C 0009 F820 239E F030 FFFE 7713 1276 F130 0020 FA4D 23A9 F130 8000 F540 F073 23AB F340 001F F330 FFFE 8193 7693 4680 8093 7693 4680 7713 1273 118B F300 00C0 6FF8 036A 0E20 F495 F495 FD43 F640 F064 0100 4E83 F074 3EE1 00F8 3EE7 6FF8 036A 0D20 F495 F495 FD4B F540 81F8 1271 69F8 13D0 1000 7713 1276 7712 1270 F495 7592 0030 F495 F495 7593 0031 F495 F495 7593 0032 F495 F495 7582 0004 EC0E F495 7192 058E 7712 0228 E800 4E92 76F8 022A 0005 F073 2427 F77A 770E 5555 22F8 000C F561 F500 61F8 051D 0010 7712 3E98 FD20 6D92 F684 3C82 E900 F486 45F8 3E94 61F8 051F 0080 F820 2412 61F8 263B 0004 F830 2412 45F8 3EDC F487 F274 3CD2 82F8 022D E800 4EF8 0228 7712 051D 6182 0010 76F8 022A 0002 F820 2427 F273 2437 6882 FFEF 68F8 022C FFF7 F073 2437 F67B F074 4315 7712 022B 838A 69F8 051D 0001 F074 3E53 F073 25BC 7719 0010 771A 0007 F272 244C 7714 0200 74D4 0027 F495 74D4 0027 F495 74D4 0027 F495 74D4 0027 F495 6E82 25BC 7312 022A 7712 022C 6182 0008 F820 245A E901 F073 2464 6082 0002 F820 2462 F273 2464 720B 0230 720B 022E F273 25BC 730B 022F F074 05DE 4A60 4A61 7712 00C8 E723 7719 0010 ED00 7715 3EBD 7710 0002 7716 0200 771A 0007 F272 2499 7714 0204 74D6 0027 A43A A5BE B336 B0BE 74D6 0027 B03A B3BE B336 B0BE 74D6 0027 B03A B3BE B336 B0BE 74D6 0027 B03A B3BE B736 D6E9 E4E9 6DDC 6DED FFF9 60F8 056E 0001 F830 24BB 4592 4492 3C92 4392 4392 4092 4092 7719 0048 7213 0518 3F92 82D3 83D3 4592 4492 3C92 4392 4392 4092 4092 3F82 82D3 83D3 F273 24D4 7313 0518 4592 4492 3C92 4392 4392 4092 4092 3F92 3F92 3C92 3C92 4392 4392 4092 4092 3F82 7719 0048 7213 0518 F495 82D3 83D3 7313 0518 F074 05E0 7713 01F4 771A 0003 F272 24DF E900 A249 E245 E249 F074 05E2 7719 0048 7212 051A F495 4FD2 7312 051A 7713 051D 6183 0002 FA30 2547 6883 FFFD 6983 0002 61F8 3EC8 0020 10F8 055F F820 24FD F844 2547 7713 0060 56F8 3EAA F620 FA43 252B 7712 022D F820 2513 1082 F000 0001 E908 F487 6F82 0D20 F84D 2547 F073 254B 7083 3E94 61F8 051F 0080 F820 2521 61F8 263B 0004 F830 2521 7083 3EDC A201 F845 2547 F062 0006 3C82 F273 2543 4583 F487 56F8 3EA8 F620 F846 2547 F820 253D 1082 F010 0001 E900 F486 6F82 0D20 F84D 2547 F073 254B F062 0003 4082 F484 F843 2547 F274 3CD2 82F8 022D F273 25BC 8A61 8A60 80F8 022D F000 3EEA 8813 F495 F495 4483 F063 FFFE 7708 4680 F120 0100 F495 75F8 0009 0031 F495 F495 75F8 0008 0032 F495 F495 75F8 000B 0030 F495 F074 3EE1 00F8 3EE7 6FF8 036A 0D20 F84B 2572 F640 F495 75F8 0008 0004 EC0E F495 69F8 13D0 0010 F073 2547 F074 05E4 7213 0231 7719 0010 7715 3EBD 7710 0002 ED00 7714 0204 7716 0200 771A 0007 F272 25AF 7712 01F4 74D6 0027 A43A A5BE B336 B0BE 74D6 0027 B03A B3BE B336 B0BE 74D6 0027 B03A B3BE B336 B0BE 74D6 0027 B03A B3BE B736 B43E 6DED FFF9 4092 E4E9 438A E6E9 F074 05E6 7313 0231 7712 022F 1082 F010 0001 8082 F945 3E53 74F8 0008 0021 F030 F7FF 8A19 8A1C 75F8 0008 0021 8A1B 8A1A 8A13 8A12 8A15 8A14 8A10 8A16 8A11 8A0E 8A0D 8A0C 8A0B 8A0A 8A09 8A08 8A07 8A06 F4E5 7714 0200 F071 000F 8094 FC00 F074 05E8 4A07 4A08 4A09 4A0A 4A0B 4A0C 4A0D 4A0E 4A12 4A13 4A19 4A1B 4A1C 771B 0000
 *
 * Intent: V16/INT0 SAMPLE_ISR body -- RX signal processing per roms/rom6/ivt.md.
 * ST1 mode prologue (ldm/and/or/stlm; FRCT-class set, ST1 dark); pa33 handshake
 * (portr/or/portw); dispatch on *(0x22C): ==1 -> 2468 arm, ==2 -> 257D arm (the
 * RX_REQUEST_KIND flags), else the main FIR lane (AR2 = *(0x22A) countdown skips
 * to 2439 when nonzero). Main lane: BK=16/ASM=0/BRC=7 dual-MAC FIR (coeffs
 * AR5=0x3EBD, input AR4=0x204, samples via portr pa39 into *AR6+%; AR0=2 dead,
 * flagged), rptbd block repeats BRC+1=8 (8 taps per ivt.md; RPTBD
 * idempotent-stm-first model, flagged); SQDST/DST Viterbi branch metrics
 * (A=(X-Y)<<16, B+=d*d per op_distance_dual, FRCT-doubling flagged); call-05DC
 * (RAM); BCD loop over *(0x22F); gain/AGC lane with the 238F bcd cascade and
 * the 23A2 bcd pair; pa48/49/50/4 + pa33 port writes; call-3EE1 (bound,
 * port13_stable_read) with add/sub lanes; call-4315 (bound, gain_map_4315 with
 * AR2 clobber threaded per its int** contract); calld-3CD2 / cc-3E53 (asm-only,
 * forward extern); second FIR (2468 arm, pshm *(0x60/0x61) direct-dma form per
 * gas acceptance) and third FIR (257D arm); convergence b 0x25BC into the
 * epilogue (pa33 strobe, full popm restore, FRETE@25D8 non-delayed exact 0xF4E5;
 * dead lane 25D9-25DE stm/rptz/stl zero-fill + ret, unreachable post-FRETE,
 * annotated not modeled per 5886). Sub-entry 25DF (V20 vector FFD2): STATE
 * prologue (call-05E8 + partial pshm + STM RSA, flowing to 25F0/25F2).
 * SXM-widening on all 16-bit memory operands flagged (ST1 dark); FRCT/OVM and
 * circular +%/BK wraps flagged; bcd/bd/calld/banzd = 2 delay WORDS per oracle
 * test_cpu_bd; portr is memory-only (A untouched); DST = 32-bit store
 * (MSW at address, LSW above per op_dst_smem_absolute).
 */
extern void sub_05DC(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_05DE(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_05E4(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_05E6(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_05E8(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_3CD2(void); /* joins 3cd2_port4850_seq (asm-only, Pool) */
extern void sub_3E53(void); /* joins 3e53_port_seq_sweep (asm-only, Pool) */
extern void gain_map_4315(long a_live, int *ar2_in, int **ppar2);
extern int port13_stable_read(void);
extern int port_read_39(void);                                        /* HW port 39 (SAMPLE FIR input per 22F3 span); no ROM definition */
extern int port_read_33(void);                                        /* HW port 33 (SAMPLE handshake per 22F3 span); no ROM definition */
extern void port_write_33(int v);                                     /* HW port 33 (SAMPLE handshake per 22F3 span); no ROM definition */
extern void port_write_48(int v);                                     /* HW port 48 (RF per 22F3/3cd2 spans); no ROM definition */
extern void port_write_49(int v);                                     /* HW port 49 (RF per 22F3/3cd2 spans); no ROM definition */
extern void port_write_50(int v);                                     /* HW port 50 (RF per 22F3/3cd2 spans); no ROM definition */
extern void port_write_4(int v);                                      /* HW port 4 (RF per 3cd2 port4850 seq); no ROM definition */

void sample_body_22F3(void)
{
    long a;
    long b;
    long d;
    int *ar1;
    int *ar2;
    int *ar3;
    int *ar4;
    int *ar5;
    int *ar6;
    int t;
    int al;
    int taken;
    int taken2;
    int i;

l22f3:
    /* ldm st1,a; and #8192,a; or #18688,a; stlm a,st1 (mode set, ST1 dark) */
    /* ssbx st1,intm (hardware, no C form) */
    *(volatile int *)0x8 = port_read_33();                    /* portr 33,*(0x8) */
    *(volatile int *)0x8 |= 3072;                             /* or #3072 (memory) */
    port_write_33(*(volatile int *)0x8);                       /* portw *(0x8),33 */
    ar2 = (int *)(long)*(volatile int *)0x22A;                /* mvdm 0x22a,ar2 */
    port_write_33(*(volatile int *)0x8);                       /* portw *(0x8),33 */
    ar3 = (int *)542;                                         /* stm #542,ar3 */
    taken = (ar2 != (int *)0) != 0;                           /* banz *ar2- */
    if (taken) {
        ar2--;
        goto l2439;
    }
    ar2 = (int *)556;                                         /* stm #556,ar2 */
    taken = (*(volatile int *)0x22C == 1) != 0;               /* cmpm *ar2,#1 */
    if (taken)                                                 /* bc 0x2468,tc */
        goto l2468;
    taken = (*(volatile int *)0x22C == 2) != 0;               /* cmpm *ar2,#2 */
    if (taken)                                                 /* bc 0x257d,tc */
        goto l257d;
    ar1 = (int *)552;                                         /* stm #552,ar1 */
    /* stm #16,bk; ld #0,asm; stm #16061,ar5; stm #2,ar0 (AR0 dead) */
    /* stm #512,ar6; stm #516,ar4; stm #7,brc */
    ar5 = (int *)0x3EBD;
    ar6 = (int *)512;
    ar4 = (int *)516;
    for (i = 0; i < 8; i++) {                                  /* rptbd 0x2343 */
        ar2 = (int *)500;                                      /* stm (idempotent) */
        *ar6 = port_read_39();                                 /* portr pa39 */
        ar6++;                                                 /* +% BK=16 flagged */
        t = *ar5;                                              /* tmpy *ar5,*ar4+,a */
        a = (long)*ar4 * (long)t;
        ar4++;
        t = *ar5;                                              /* tmpy *ar5+,*ar4+0%,b */
        b = (long)*ar4 * (long)t;
        ar5++;
        b += (long)*ar5 * (long)*ar4;                          /* mac *ar5,*ar4-,b */
        ar4--;
        a += (long)*ar5 * (long)*ar4;                          /* mac *ar5+,*ar4+0%,a */
        ar5++;
        *ar6 = port_read_39();
        ar6++;
        a += (long)*ar5 * (long)*ar4;
        ar4++;
        b += (long)*ar5 * (long)*ar4;
        ar5++;
        b += (long)*ar5 * (long)*ar4;
        ar4--;
        a += (long)*ar5 * (long)*ar4;
        ar5++;
        *ar6 = port_read_39();
        ar6++;
        a += (long)*ar5 * (long)*ar4;
        ar4++;
        b += (long)*ar5 * (long)*ar4;
        ar5++;
        b += (long)*ar5 * (long)*ar4;
        ar4--;
        a += (long)*ar5 * (long)*ar4;
        ar5++;
        *ar6 = port_read_39();
        ar6++;
        a += (long)*ar5 * (long)*ar4;
        ar4++;
        b += (long)*ar5 * (long)*ar4;
        ar5++;
        b += ((long)*ar5 * (long)*ar4 + 0x4000L) >> 16;       /* macr (rounded; FRCT flagged) */
        ar4--;
        *(ar3++) = (int)(b & 0xFFFFL);                         /* st b,*ar3+ */
        a += ((long)*ar4 * (long)t + 0x4000L) >> 16;          /* || macr *ar4+0%,a (T from last tmpy) */
        /* mar *ar4+0% (unchanged) */
        ar5 -= 7;                                              /* mar *+ar5(-7), circular flagged */
        a = (long)*ar2 << 16;                                  /* sub *ar2+,16,a (SXM flagged) */
        ar2++;
        b = (long)*ar1;                                        /* dld *ar1,b (SXM flagged) */
        d = (long)*ar3 - (long)*ar2;                           /* sqdst *ar3,*ar2 */
        a = d << 16;
        b += d * d;                                            /* (FRCT-doubled when FRCT=1; flagged) */
        d = (long)*ar4 - (long)*ar2;                           /* sqdst *ar4+0%,*ar2- */
        a = d << 16;
        b += d * d;
        ar2--;
        *ar1 = (int)((b >> 16) & 0xFFFFL);                     /* dst b,*ar1 */
        *(ar1 + 1) = (int)(b & 0xFFFFL);
    }
    sub_05DC();                                                /* call 0x5dc (RAM) */
    ar3 = (int *)559;                                         /* stm #559,ar3 */
    a = 1;                                                     /* ld #1,a */
    a = a - (long)*ar3;                                        /* sub *ar3,a */
    taken = (a != 0) != 0;                                     /* bcd 0x2437,aneq */
    a = -a;                                                    /* bcd delay: neg a (runs) */
    *ar3 = (int)(a & 0xFFFFL);                                 /* bcd delay: stl (runs) */
    if (taken)
        goto l2437;
    ar3 = (int *)556;                                         /* stm #556,ar3 */
    taken = (*ar3 & 8) != 0;                                   /* bitf *ar3,#8 */
    ar2 = (int *)557;                                          /* bcd delay: stm (runs) */
    if (!taken)                                                /* bcd 0x242c,ntc */
        goto l242c;
    a = b >> 5;                                                /* sfta b,-5,a */
    gain_map_4315(a, ar2, &ar2);                               /* call 0x4315 */
    taken = (*(volatile int *)0x3EC8 & 32) != 0;              /* bitf */
    if (!taken)                                                /* bc 0x23f2,ntc */
        goto l23f2;
    ar2 = (int *)0x3E98;                                      /* stm #16024,ar2 */
    b = -b;                                                    /* neg b */
    b += (long)*ar2 << 16;                                     /* add *ar2,16,b (SXM flagged) */
    taken = (*(volatile int *)0x263B & 4) != 0;               /* bitf *(0x263b),#4 */
    ar3 = (int *)1140;                                        /* stm #1140,ar3 */
    if (taken)                                                 /* xc 2,ntc (skips stm) */
        ar3 = (int *)1180;
    a = b - ((long)*(ar3 + 3) << 16);                          /* sub *ar3(0x3),16,b,a (SXM flagged) */
    taken = (a <= 0) != 0;                                     /* bcd 0x238f,aleq */
    a = 1;                                                     /* bcd delay: ld #1,a (runs) */
    if (taken)
        goto l238f;
    a = 3;                                                     /* (index skips 2; ROM-literal) */
    /* nop */
    a = b - ((long)*(ar3 + 4) << 16);                          /* sub *ar3(0x4) */
    taken = (a <= 0) != 0;
    a = 4;                                                     /* bcd delay (runs) */
    if (taken)
        goto l238f;
    /* nop */
    a = b - ((long)*(ar3 + 5) << 16);
    taken = (a <= 0) != 0;
    a = 5;
    if (taken)
        goto l238f;
    /* nop */
    a = b - ((long)*(ar3 + 6) << 16);
    taken = (a <= 0) != 0;
    a = 6;
    if (taken)
        goto l238f;
    /* nop */
    a = b - ((long)*(ar3 + 7) << 16);
    taken = (a <= 0) != 0;
    a = 7;
    if (taken)
        goto l238f;
    /* nop */
    a = b - ((long)*(ar3 + 8) << 16);
    taken = (a <= 0) != 0;
    a = 8;                                                     /* fallthrough index */
    if (taken)
        goto l238f;
l238f:
    *(volatile int *)0x22D = (int)(a & 0xFFFFL);               /* stl a,*(0x22d) */
    a += 16106;                                                /* add #16106,a */
    ar3 = (int *)(a & 0xFFFFL);                                /* stlm a,ar3 */
    /* nop; nop */
    a = (long)*ar3;                                            /* ld *ar3,a */
    taken = (*(volatile int *)0x22C == 9) != 0;               /* cmpm *(0x22c),#9 */
    if (!taken)                                                /* bc 0x239e,ntc */
        goto l239e;
    a &= -2L;                                                  /* and #-2,a */
l239e:
    ar3 = (int *)4726;                                        /* stm #4726,ar3 */
    b = a & 32L;                                               /* and #32,a,b */
    taken = (b == 0) != 0;                                     /* bcd 0x23a9,beq */
    b = a & -32768L;                                           /* bcd delay (runs) */
    b = a;                                                     /* bcd delay: ld a,b (runs) */
    if (taken)
        goto l23a9;
    goto l23ab;
l23a9:
    b |= 31L;                                                  /* or #31,b */
l23ab:
    b &= -2L;                                                  /* and #-2,b */
    *(ar3++) = (int)(b & 0xFFFFL);                             /* stl b,*ar3+ */
    *(ar3++) = 18048;                                          /* st #18048,*ar3+ */
    *(ar3++) = (int)(a & 0xFFFFL);                             /* stl a,*ar3+ */
    *(ar3++) = 18048;                                          /* st #18048,*ar3+ */
    ar3 = (int *)4723;                                        /* stm #4723,ar3 */
    b = (long)*ar3;                                            /* ld *ar3-,b */
    ar3--;
    b += 192;                                                  /* add #192,b */
    a = b - (long)*(volatile int *)0x36A;                      /* sub *(0x36a),b,a (shift 0, SXM flagged) */
    /* nop; nop */
    if (a >= 0)                                                /* xc 1,alt (skips ld) */
        b = a;                                                 /* ld b,a */
    a |= (256L << 16);                                         /* or #256,16,a */
    *ar3 = (int)((a >> 16) & 0xFFFFL);                         /* dst a,*ar3 */
    *(ar3 + 1) = (int)(a & 0xFFFFL);
    a = (long)port13_stable_read();                            /* call 0x3ee1 */
    a += (long)*(volatile int *)0x3EE7;                        /* add *(0x3ee7),a (SXM flagged) */
    b = a - (long)*(volatile int *)0x36A;                      /* sub *(0x36a),a,b (SXM flagged) */
    /* nop; nop */
    if (b >= 0)                                                /* xc 1,blt (skips ld) */
        a = b;                                                 /* ld a,b */
    *(volatile int *)0x1271 = (int)(b & 0xFFFFL);              /* stl b,*(0x1271) */
    *(volatile int *)0x13D0 |= 4096;                           /* orm #4096 */
    ar3 = (int *)4726;
    ar2 = (int *)4720;
    /* nop */
    port_write_48(*(ar2++));                                   /* portw *ar2+,pa48 */
    /* nop; nop */
    port_write_49(*(ar3++));                                   /* portw *ar3+,pa49 */
    /* nop; nop */
    port_write_50(*(ar3++));                                   /* portw *ar3+,pa50 */
    /* nop; nop */
    port_write_4(*ar2);                                         /* portw *ar2,pa4 */
    for (i = 0; i < 15; i++) {}                                /* rpt #14 nop */
    *(volatile int *)0x58E = *(ar2++);                         /* mvdk *ar2+,0x58e */
    ar2 = (int *)552;
    a = 0;                                                     /* ld #0,a */
    *ar2 = (int)((a >> 16) & 0xFFFFL);                         /* dst a,*ar2+ */
    *(ar2 + 1) = (int)(a & 0xFFFFL);
    ar2++;
    *(volatile int *)0x22A = 5;                                /* st #5,*(0x22a) */
    goto l2427;                                                /* b 0x2427 */
l23f2:
    a = b >> 6;                                                /* sfta b,-6 */
    t = 21845;                                                 /* stm #21845,t */
    a = ((long)*(volatile int *)0xC * (long)t + 0x4000L) >> 16; /* mpyr *(0xc),a (rounded; FRCT flagged) */
    b = a << 1;                                                /* sfta a,1,b */
    b += a;                                                    /* add a,b */
    taken = (*(volatile int *)0x51D & 16) != 0;               /* bitf *(0x51d),#16 */
    ar2 = (int *)0x3E98;                                      /* stm #16024,ar2 */
    if (taken)                                                 /* xc 1,ntc (skips mar) */
        ar2++;                                                 /* mar *ar2+ */
    a = -b;                                                    /* neg b,a */
    a += (long)*ar2 << 16;                                     /* add *ar2,16,a (SXM flagged) */
    b = 0;                                                     /* ld #0,b */
    if (a < b)                                                 /* max a */
        a = b;
    b = (long)*(volatile int *)0x3E94 << 16;                  /* ld *(0x3e94),16,b */
    taken = (*(volatile int *)0x51F & 128) != 0;              /* bitf *(0x51f),#128 */
    if (!taken)                                                /* bc 0x2412,ntc */
        goto l2412;
    taken = (*(volatile int *)0x263B & 4) != 0;               /* bitf *(0x263b),#4 */
    if (taken)                                                 /* bc 0x2412,tc */
        goto l2412;
    b = (long)*(volatile int *)0x3EDC << 16;                  /* ld *(0x3edc),16,b */
l2412:
    if (a > b)                                                 /* min a */
        a = b;
    *(volatile int *)0x22D = (int)((a >> 16) & 0xFFFFL);      /* calld delay: sth (runs) */
    sub_3CD2();                                                /* calld 0x3cd2 */
    a = 0;                                                     /* ld #0,a */
    *(volatile int *)0x228 = (int)((a >> 16) & 0xFFFFL);      /* dst a,*(0x228) */
    *(volatile int *)0x229 = (int)(a & 0xFFFFL);
    ar2 = (int *)0x51D;                                       /* stm #1309,ar2 */
    taken = (*ar2 & 16) != 0;                                  /* bitf *ar2,#16 */
    *(volatile int *)0x22A = 2;                                /* st #2,*(0x22a) */
    if (!taken)                                                /* bc 0x2427,ntc */
        goto l2427;
    *ar2 &= -17;                                               /* bd delay: andm (runs) */
l2427:
    *(volatile int *)0x22C &= -9;                              /* andm #-9 */
    goto l2437;                                                /* b 0x2437 */
l242c:
    a = b >> 5;                                                /* sfta b,-5,a */
    gain_map_4315(a, ar2, &ar2);                               /* call 0x4315 (AR2=0x22d) */
    ar2 = (int *)0x22B;                                       /* stm #555,ar2 */
    *(ar2--) = (int)((b >> 16) & 0xFFFFL);                     /* sth b,*ar2- */
    *(volatile int *)0x51D |= 1;                               /* orm #1 */
    sub_3E53();                                                /* call 0x3e53 */
l2437:
    goto l25bc;                                                /* b 0x25bc */
l2439:
    /* stm #16,bk; stm #7,brc */
    for (i = 0; i < 8; i++) {                                  /* rptbd 0x244c */
        ar4 = (int *)512;                                      /* stm (idempotent) */
        *ar4 = port_read_39();                                 /* portr pa39 ×4 */
        ar4++;
        /* nop */
        *ar4 = port_read_39();
        ar4++;
        /* nop */
        *ar4 = port_read_39();
        ar4++;
        /* nop */
        *ar4 = port_read_39();
        ar4++;
        /* nop */
    }
    *(volatile int *)0x22A = (int)(long)ar2;                   /* banzd delay: mvmd (runs) */
    taken = (ar2 != (int *)0) != 0;                           /* banzd *ar2 */
    if (taken)
        ar2--;
    if (taken)                                                 /* banzd 0x25bc */
        goto l25bc;
    ar2 = (int *)556;                                         /* stm #556,ar2 */
    taken = (*ar2 & 8) != 0;                                   /* bitf *ar2,#8 */
    if (!taken)                                                /* bc 0x245a,ntc */
        goto l245a;
    b = 1;                                                     /* ld #1,b */
    goto l2464;                                                /* b 0x2464 */
l245a:
    taken = (*ar2 == 2) != 0;                                  /* cmpm *ar2,#2 */
    if (!taken)                                                /* bc 0x2462,ntc */
        goto l2462;
    b = (b & ~0xFFFFL) | (long)(unsigned)*(volatile int *)0x230; /* bd delay: mvdm bl (B-high kept, flagged) */
l2464:
    *(volatile int *)0x22F = (int)(b & 0xFFFFL);               /* bd delay: mvmd bl (runs) */
    goto l25bc;                                                /* bd 0x25bc */
l2462:
    b = (b & ~0xFFFFL) | (long)(unsigned)*(volatile int *)0x22E;
    goto l2464;
l2468:
    sub_05DE();                                                /* call 0x5de (RAM) */
    /* pshm *(0x60); pshm *(0x61) (direct-dma, gas-accepted) */
    ar2 = (int *)200;                                         /* stm #200,ar2 */
    ar3 = ar2;                                                 /* mvmm ar2,ar3 */
    /* stm #16,bk; ld #0,asm; stm #16061,ar5; stm #2,ar0 (dead) */
    /* stm #512,ar6; stm #7,brc */
    ar5 = (int *)0x3EBD;
    ar6 = (int *)512;
    for (i = 0; i < 8; i++) {                                  /* rptbd 0x2499 */
        ar4 = (int *)516;                                      /* stm (idempotent) */
        *ar6 = port_read_39();
        ar6++;
        t = *ar5;
        a = (long)*ar4 * (long)t;
        ar4++;
        t = *ar5;
        b = (long)*ar4 * (long)t;
        ar5++;
        b += (long)*ar5 * (long)*ar4;
        ar4--;
        a += (long)*ar5 * (long)*ar4;
        ar5++;
        *ar6 = port_read_39();
        ar6++;
        a += (long)*ar5 * (long)*ar4;
        ar4++;
        b += (long)*ar5 * (long)*ar4;
        ar5++;
        b += (long)*ar5 * (long)*ar4;
        ar4--;
        a += (long)*ar5 * (long)*ar4;
        ar5++;
        *ar6 = port_read_39();
        ar6++;
        a += (long)*ar5 * (long)*ar4;
        ar4++;
        b += (long)*ar5 * (long)*ar4;
        ar5++;
        b += (long)*ar5 * (long)*ar4;
        ar4--;
        a += (long)*ar5 * (long)*ar4;
        ar5++;
        *ar6 = port_read_39();
        ar6++;
        a += (long)*ar5 * (long)*ar4;
        ar4++;
        b += (long)*ar5 * (long)*ar4;
        ar5++;
        b += ((long)*ar5 * (long)*ar4 + 0x4000L) >> 16;       /* macr */
        ar4--;
        *(ar3++) = (int)(b & 0xFFFFL);                         /* st b,*ar3+ */
        a += ((long)*ar4 * (long)t + 0x4000L) >> 16;          /* || macr */
        *(ar3++) = (int)(a & 0xFFFFL);                         /* st a,*ar3+ */
        t = *ar4;                                              /* || ld *ar4+0%,t */
        /* mar *ar4+0% (unchanged) */
        ar5 -= 7;                                              /* mar *+ar5(-7) */
    }
    taken = (*(volatile int *)0x56E == 1) != 0;               /* cmpm *(0x56e),#1 */
    if (taken)                                                 /* bc 0x24bb,tc */
        goto l24bb;
    b = (long)*(ar2++) << 16;                                  /* ld *ar2+,16,b (SXM) */
    a = (long)*(ar2++) << 16;                                  /* ld *ar2+,16,a */
    a += (long)*(ar2++) << 16;                                 /* add *ar2+,16,a */
    b -= (long)*(ar2++) << 16;                                 /* sub *ar2+,16,b ×2 */
    b -= (long)*(ar2++) << 16;
    a -= (long)*(ar2++) << 16;                                 /* sub *ar2+,16,a ×2 */
    a -= (long)*(ar2++) << 16;
    /* stm #72,bk */
    ar3 = (int *)(long)*(volatile int *)0x518;                /* mvdm 0x518,ar3 */
    /* nop */
    b += (long)*(ar2++) << 16;                                 /* add *ar2+,16,b */
    *ar3 = (int)((a >> 16) & 0xFFFFL);                         /* sth a,*ar3+% */
    ar3++;                                                     /* (+% BK=72 flagged) */
    *ar3 = (int)((b >> 16) & 0xFFFFL);                         /* sth b,*ar3+% */
    ar3++;
    b = (long)*(ar2++) << 16;
    a = (long)*(ar2++) << 16;
    a += (long)*(ar2++) << 16;
    b -= (long)*(ar2++) << 16;
    b -= (long)*(ar2++) << 16;
    a -= (long)*(ar2++) << 16;
    a -= (long)*(ar2++) << 16;
    b += (long)*ar2 << 16;                                     /* add *ar2,16,b */
    *ar3 = (int)((a >> 16) & 0xFFFFL);
    ar3++;
    *ar3 = (int)((b >> 16) & 0xFFFFL);
    ar3++;
    /* bd 0x24d4 (delay: mvmd ar3,0x518 runs) */
    *(volatile int *)0x518 = (int)(long)ar3;
    goto l24d4;                                                /* bd */
l24bb:
    b = (long)*(ar2++) << 16;                                  /* (second butterfly set) */
    a = (long)*(ar2++) << 16;
    a += (long)*(ar2++) << 16;
    b -= (long)*(ar2++) << 16;
    b -= (long)*(ar2++) << 16;
    a -= (long)*(ar2++) << 16;
    a -= (long)*(ar2++) << 16;
    b += (long)*(ar2++) << 16;
    b += (long)*(ar2++) << 16;
    a += (long)*(ar2++) << 16;
    a += (long)*(ar2++) << 16;
    b -= (long)*(ar2++) << 16;
    b -= (long)*(ar2++) << 16;
    a -= (long)*(ar2++) << 16;
    a -= (long)*(ar2++) << 16;
    b += (long)*ar2 << 16;
    /* stm #72,bk */
    ar3 = (int *)(long)*(volatile int *)0x518;
    /* nop */
    *ar3 = (int)((a >> 16) & 0xFFFFL);
    ar3++;
    *ar3 = (int)((b >> 16) & 0xFFFFL);
    ar3++;
    *(volatile int *)0x518 = (int)(long)ar3;                   /* mvmd ar3,0x518 */
l24d4:
    sub_05E0();                                                /* call 0x5e0 (RAM) */
    ar3 = (int *)500;                                         /* stm #500,ar3 */
    /* stm #3,brc */
    for (i = 0; i < 4; i++) {                                  /* rptbd 0x24df */
        b = 0;                                                 /* ld #0,b */
        a = (long)*ar2 - (long)*ar3;                           /* sub *ar2-,*ar3+,a (dual, SXM flagged) */
        ar2--;
        ar3++;
        d = (long)*ar2 - (long)*ar3;                           /* sqdst *ar2-,*ar3- */
        a = d << 16;
        b += d * d;
        ar2--;
        ar3--;
        d = (long)*ar2 - (long)*ar3;                           /* sqdst *ar2-,*ar3+ */
        a = d << 16;
        b += d * d;
        ar2--;
        ar3++;
    }
    sub_05E2();                                                /* call 0x5e2 (RAM) */
    /* stm #72,bk */
    ar2 = (int *)(long)*(volatile int *)0x51A;                /* mvdm 0x51a,ar2 */
    /* nop */
    *ar2 = (int)((b >> 16) & 0xFFFFL);                         /* dst b,*ar2+% */
    *(ar2 + 1) = (int)(b & 0xFFFFL);
    ar2++;                                                     /* (+% BK=72 flagged) */
    *(volatile int *)0x51A = (int)(long)ar2;                   /* mvmd ar2,0x51a */
    ar3 = (int *)0x51D;                                       /* stm #1309,ar3 */
    taken = (*ar3 & 2) != 0;                                   /* bitf *ar3,#2 */
    /* bcd 0x2547,tc (delay: andm #-3 + orm #2 run) */
    *ar3 &= -3;
    *(ar3) |= 2;
    if (taken)
        goto l2547;
    taken2 = (*(volatile int *)0x3EC8 & 32) != 0;              /* bitf *(0x3ec8),#32 */
    a = (long)*(volatile int *)0x55F;                          /* ld *(0x55f),a */
    if (!taken2)                                               /* bc 0x24fd,ntc */
        goto l24fd;
    if (a != 0)                                                /* bc 0x2547,aneq */
        goto l2547;
l24fd:
    ar3 = (int *)96;                                          /* stm #96,ar3 */
    a = (long)*(volatile int *)0x3EAA;                         /* dld (SXM flagged) */
    a = a - b;                                                 /* sub b,a */
    taken = (a < 0) != 0;                                      /* bcd 0x252b,alt */
    ar2 = (int *)557;                                          /* bcd delay: stm (runs) */
    if (taken)
        goto l252b;
    taken2 = (*(volatile int *)0x51F & 128) != 0;              /* bitf *(0x51f),#128 */
    if (!taken2)                                               /* (stale-TC lane, flagged) */
        goto l2513;
    a = (long)*ar2;                                            /* ld *ar2,a */
    a += 1;                                                    /* add #1,a */
    b = 8;                                                     /* ld #8,b */
    if (a < b)                                                 /* min a */
        a = b;
    b = a - (long)*ar2;                                        /* sub *ar2,a,b (SXM flagged) */
    if (b == 0)                                                /* bc 0x2547,beq */
        goto l2547;
    goto l254b;                                                /* b 0x254b */
l2513:
    *(volatile int *)0x60 = *(volatile int *)0x3E94;           /* mvkd 0x3e94,*ar3 */
    taken2 = (*(volatile int *)0x51F & 128) != 0;
    if (!taken2)
        goto l2521;
    taken2 = (*(volatile int *)0x263B & 4) != 0;
    if (taken2)
        goto l2521;
    *(volatile int *)0x60 = *(volatile int *)0x3EDC;           /* mvkd 0x3edc,*ar3 */
l2521:
    a = (long)*ar2 - (long)*ar3;                               /* sub *ar2,*ar3,a (SXM flagged) */
    if (a == 0)                                                /* bc 0x2547,aeq */
        goto l2547;
    a = 6L << 16;                                              /* ld #6,16,a */
    a += (long)*ar2 << 16;                                     /* add *ar2,16,a */
    /* bd 0x2543 (delay: ld+min run) */
    b = (long)*ar3 << 16;
    if (a > b)
        a = b;
    goto l2543_calld;                                          /* bd */
l252b:
    a = (long)*(volatile int *)0x3EA8;                         /* dld (SXM flagged) */
    a = a - b;
    if (a > 0)                                                 /* bc 0x2547,agt */
        goto l2547;
    taken2 = (*(volatile int *)0x51C & 3072) != 0;            /* bitf *(0x51c),#3072 */
    if (!taken2)                                               /* (stale-TC lane, flagged) */
        goto l253d;
    a = (long)*ar2;                                            /* ld *ar2,a */
    a -= 1;                                                    /* sub #1,a */
    b = 0;                                                     /* ld #0,b */
    if (a < b)                                                 /* max a */
        a = b;
    b = a - (long)*ar2;                                        /* sub *ar2,a,b */
    if (b == 0)                                                /* bc 0x2547,beq */
        goto l2547;
    goto l254b;
l253d:
    a = 3L << 16;                                              /* ld #3,16,a */
    a -= (long)*ar2 << 16;                                     /* sub *ar2,16,a */
    a = -a;                                                    /* neg a */
    if (a < 0)                                                 /* bc 0x2547,alt */
        goto l2547;
l2543_calld:
    *(volatile int *)0x22D = (int)((a >> 16) & 0xFFFFL);      /* calld delay: sth (runs) */
    sub_3CD2();                                                /* calld 0x3cd2 */
    /* fallthrough to l2547 */
l2547:
    /* bd 0x25bc (delay: popm *(0x60/0x61) run) */
    /* (delay restores Viterbi state cells) */
    goto l25bc;                                                /* bd */
l254b:
    *(volatile int *)0x22D = (int)(a & 0xFFFFL);               /* stl a,*(0x22d) */
    a += 16106;
    ar3 = (int *)(a & 0xFFFFL);                                /* stlm a,ar3 */
    /* nop; nop */
    a = (long)*ar3 << 16;                                      /* ld *ar3,16,a (SXM flagged) */
    a &= (-2L << 16);                                          /* and #-2,16,a */
    al = 18048;                                                /* stm #18048,al */
    b = 256;                                                   /* ld #256,b */
    /* nop */
    port_write_49(*(volatile int *)0x9);                        /* portw *(0x9),pa49 */
    /* nop; nop */
    port_write_50(*(volatile int *)0x8);                        /* portw *(0x8),pa50 */
    /* nop; nop */
    port_write_48(*(volatile int *)0xB);                        /* portw *(0xb),pa48 */
    /* nop */
    a = (long)port13_stable_read();                            /* call 0x3ee1 */
    a += (long)*(volatile int *)0x3EE7;
    b = a - (long)*(volatile int *)0x36A;
    if (b < 0)                                                 /* bc 0x2572,blt */
        goto l2572;
    a = b;                                                     /* ld b,a */
l2572:
    /* nop */
    port_write_4(*(volatile int *)0x8);                        /* portw *(0x8),pa4 */
    for (i = 0; i < 15; i++) {}                                /* rpt #14 */
    *(volatile int *)0x13D0 |= 16;                             /* orm #16 */
    goto l2547;                                                /* b 0x2547 */
l257d:
    sub_05E4();                                                /* call 0x5e4 (RAM) */
    ar3 = (int *)(long)*(volatile int *)0x231;                 /* mvdm 0x231,ar3 */
    /* stm #16,bk; stm #16061,ar5; stm #2,ar0 (dead); ld #0,asm */
    /* stm #516,ar4; stm #512,ar6; stm #7,brc */
    ar5 = (int *)0x3EBD;
    ar4 = (int *)516;
    ar6 = (int *)512;
    for (i = 0; i < 8; i++) {                                  /* rptbd 0x25af */
        ar2 = (int *)500;
        *ar6 = port_read_39();
        ar6++;
        t = *ar5;
        a = (long)*ar4 * (long)t;
        ar4++;
        t = *ar5;
        b = (long)*ar4 * (long)t;
        ar5++;
        b += (long)*ar5 * (long)*ar4;
        ar4--;
        a += (long)*ar5 * (long)*ar4;
        ar5++;
        *ar6 = port_read_39();
        ar6++;
        a += (long)*ar5 * (long)*ar4;
        ar4++;
        b += (long)*ar5 * (long)*ar4;
        ar5++;
        b += (long)*ar5 * (long)*ar4;
        ar4--;
        a += (long)*ar5 * (long)*ar4;
        ar5++;
        *ar6 = port_read_39();
        ar6++;
        a += (long)*ar5 * (long)*ar4;
        ar4++;
        b += (long)*ar5 * (long)*ar4;
        ar5++;
        b += (long)*ar5 * (long)*ar4;
        ar4--;
        a += (long)*ar5 * (long)*ar4;
        ar5++;
        *ar6 = port_read_39();
        ar6++;
        a += (long)*ar5 * (long)*ar4;
        ar4++;
        b += (long)*ar5 * (long)*ar4;
        ar5++;
        b += ((long)*ar5 * (long)*ar4 + 0x4000L) >> 16;       /* macr *ar5,*ar4-,b */
        ar4--;
        a += ((long)*ar5 * (long)*ar4 + 0x4000L) >> 16;       /* macr *ar5,*ar4+0%,a */
        *(ar3++) = (int)(a & 0xFFFFL);                         /* st a,*ar3+ */
        t = *ar4;                                              /* || ld *ar4+0%,t */
        b -= (long)*ar2;                                       /* sub *ar2-,16,b (SXM flagged) */
        ar2--;
        *(ar3++) = (int)(b & 0xFFFFL);                         /* st b,*ar3+ */
        t = *ar4;                                              /* || ld *ar4+0%,t */
        /* mar *ar3-% (AR3--) */
        ar3--;
    }
    sub_05E6();                                                /* call 0x5e6 (RAM) */
    *(volatile int *)0x231 = (int)(long)ar3;                   /* mvmd ar3,0x231 */
    ar2 = (int *)559;                                         /* stm #559,ar2 */
    a = (long)*ar2;                                            /* ld *ar2,a */
    a -= 1;                                                    /* sub #1,a */
    *(volatile int *)0x22A = (int)(a & 0xFFFFL);              /* stl a,*(0x22a) */
    taken = (a == 0) != 0;                                     /* cc 0x3e53,aeq */
    if (taken)
        sub_3E53();
l25bc:
    *(volatile int *)0x8 = port_read_33();                     /* epilogue: portr pa33 */
    *(volatile int *)0x8 &= -2049;                             /* and #-2049 (memory) */
    /* popm bk/rea/rsa/brc/ar3/ar2/ar5/ar4/ar0/ar6/ar1/t/bg/bh/bl/ag/ah/al/st1/st0 */
    /* frete (interrupt return, non-delayed exact 0xF4E5, no C form) */
    /* dead lane 25D9-25DE: stm/rptz/stl zero-fill + ret (unreachable, dark) */
l25df:
    sub_05E8();                                                /* call 0x5e8 (RAM) */
    /* pshm st1/al/ah/ag/bl/bh/bg/t/ar2/ar3/bk/rsa/rea (caller-live, comments only) */
    /* stm #0,rsa (MMR, no C form) */
    /* span ends at the 25EE-25EF instruction boundary; 25F0 slot abuts, then 25F2 */
    (void)t; (void)taken2; (void)i; (void)ar4; (void)ar5; (void)ar6; (void)ar1; (void)d;
}
