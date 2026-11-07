/* ROM6 0x2088 SUPERVISOR_LOOP_2088 -- 474w.
 * Verified encoding: src/rom6/boot/2088_supervisor_loop_2088.asm (recombine MATCH).
 * ORIGIN 0x2088
 * EXPECT: F074 0598 F274 2282 7712 0004 F820 20A8 7712 2202 6082 0000 F920 2E39 61F8 20FF 0800 F930 2E39 7712 20FE 6082 0000 F920 2E39 61F8 0866 0003 F930 2E39 F073 2090 61F8 01F2 0001 69F8 01F2 0001 F7BD F074 05B6 68F8 058F FF7F 61F8 058F 000F F830 2117 10F8 085D F030 00FF F844 20D8 68F8 058F FF7F 61F8 058F 000F F830 20D8 F274 2282 7712 0008 F830 20D8 68F8 0537 FFF7 F074 2262 F074 226C F274 2262 7712 0003 7713 054F 10F8 3EC8 F030 0010 61F8 0589 0003 FF45 6183 0001 F830 2123 6183 0080 F830 225E F7BB 74F8 0008 0003 F030 FEFF F495 75F8 0008 0003 EC15 F495 F020 0103 F495 75F8 0008 0030 61F8 3EC8 0020 F820 210C 74F8 0008 000C 11F8 3ECE F793 F280 F495 75F8 0008 000C 61F8 058F 000F F830 2117 F274 2282 7712 0008 F930 0644 F074 05B6 F6BB F074 2E39 F074 9E85 F6BB F074 E64C F073 2088 F074 05B6 61F8 058F 000F F820 2134 76F8 2453 0000 E801 F981 AA1D F274 2262 7712 0003 69F8 058F 0080 61F8 01F2 0002 69F8 01F2 0002 E901 F074 070A 76F8 054F 0000 69F8 263A 0080 E800 F074 3986 F074 AC4C E800 F074 3986 F074 4883 61F8 3EC8 0010 F820 2168 61F8 0589 0001 76F8 0589 0000 F830 2174 69F8 263A 0080 F074 AC4C F020 2BFE 80F8 2665 F073 218A 61F8 051F 4000 F820 2174 69F8 263A 0080 F074 AC4C F073 2187 F274 226C 7712 0003 E902 F074 070A F074 05FE 61F8 3EC8 0010 F830 2000 61F8 051F 0400 F830 2000 70F8 2665 38C9 F074 05B6 61F8 058F 000F F820 219B 76F8 2453 0000 E801 F981 AA1D F274 2262 7712 0003 69F8 058F 0080 76F8 036A 1387 F495 75F8 036A 000E EC0C F495 7213 2665 61F8 3EC8 0010 F820 21B9 60F8 058A 0050 F830 21CB 6083 FFFF F820 21D3 F073 21CB F020 7FFF 0883 F844 21D3 4813 F120 2BFE F620 F845 21CB 10F8 38CA F520 FA4C 21D3 80F8 2665 7713 086D F274 2D5E 7712 0087 F073 2000 7214 2665 7713 0008 7184 2545 F7BB 7483 0002 6983 1000 F495 7583 0002 F6BB 76F8 056E 0000 F274 226C 7712 0003 F074 0600 76F8 056E 0001 61F8 3EC8 0010 F820 21F9 6BF8 2665 0002 6BF8 058A 0001 6BF8 2665 FFFF F074 2E39 10F8 3EC8 F030 0010 61F8 0589 0002 FF45 61F8 054F 0001 F830 2000 61F8 2627 0080 F830 221F 7713 2F00 10F8 2545 8083 7715 0002 7713 2F00 F274 2C88 7714 008A F073 218A 61F8 01F2 0008 69F8 01F2 0008 E901 F074 070A 76F8 2627 0008 76F8 2476 0004 76F8 2546 0030 76F8 2547 0040 76F8 0574 0000 F074 2E39 7710 054F 10F8 3EC8 F030 0010 61F8 0589 0003 FF45 6180 0001 F830 2000 6180 0002 F820 225E 6880 FFFD 69F8 263A 0080 E800 F074 3986 F074 AC4C E800 F074 3986 F071 0008 7308 0912 F073 218A F074 5C4F F073 2237
 *
 * Intent: Low-ROM supervisor loop with port strobes and masked tails. Entry via F1 b-tail only.
 * 2088 head: RAM SUB_059C; calld-2282 lane (delay AR2 = 4); TC dark (unbound) clear joins the 20A8 lane,
 * else the 2090 poll loop: cmpm/bitf-gated conditional leaf_2E39 calls around AR presets, looping until
 * 2E39 diverts internally via its frag_2E52 tail (no local exit; hang noted). 20A8 lane: cell bit set (orm);
 * XF strobe (ssbx, hardware); RAM SUB_05B6; cell masks; cell-0x58F-nibble lanes with A-select, calld-2282
 * lane (delay AR2 = 8), SUB_2262/SUB_226C calls, calld-2262 lane (delay AR2 = 3). 20D8 lane: AR3 = 1359;
 * A = cell & 16; xc-stale-TC branch select (skipped bitf leaves prior TC): 2123 lane, 225E lane via AR3
 * bit 7, else INTM-guarded port 3 strobe (portr/and/nop/portw), 22x settle, A = 259, port 48 write,
 * cell-bit lanes with port 12 read-modify-write (cmpl per 2ACC: B = ~B low16 exact; A &= B), dispatcher call
 * lane via 210C join. 2117 lane: RAM SUB_05B6; INTM guards; C-bound/free leaf_2E39, sub_9E85, sub_E64C calls;
 * restart head (b 0x2088). 2123 lane: RAM SUB_05B6; nibble lanes with uploaded fcall, calld-2262 lane;
 * XF/flag orms; RAM SUB_070A; cell presets; SUB_3986 / portseq_AC4C / SUB_3986 / frag_4883 calls (all bound);
 * bit lanes with 2168/2174 joins; calld-226C lane; RAM SUB_070A/SUB_05FE; bc-2000 tails (frag_2000, never
 * return); 2187 mvkd lane rejoining 218A. 218A lane: RAM SUB_05B6; nibble clear/set lanes with uploaded
 * fcall, calld-2262 lane; cell = 4999; port 14 write; 13x settle; AR3 = *0x2665 (mvdm); cell-bit/cmpm lanes
 * selecting the 21CB/21D3 joins (b 0x21CB rejoin; ld/sub/bc/ldm/sub/bc/ld/sub with bcd delay-stmt); 21CB lane:
 * calld-2D5E (delay AR2 = 135) then tail frag_2000. 21D3 lane: INTM-guarded port 2 strobe, cell clear,
 * calld-226C lane, RAM SUB_0600, addm counters, C-bound leaf_2E39, stale-xc 2000 tail, 221F/2210 lanes
 * (2210: calld-2C88 lane with AR4 = 138 preset, b 0x218A rejoin; 221F: flag orms, RAM SUB_070A, cell presets).
 * 2237 section: C-bound leaf_2E39; AR0 = 1359 cell pointer; stale-xc 2000 tail; 225E lane (call SUB_5C4F,
 * loop to 2237 head) entered from 20E6/2249 joins. AR2/AR3/AR0/AR4/AR5 presets die in-span except where passed
 * to C-bound callees (flagged). Never returns (tails only).
 */
extern void sub_059C(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_0644(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_05B6(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_05FE(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_0600(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_070A(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void far_1AA1D(void); /* XPC page, off-image; see docs/evidence/extern-triage.md */
extern void sub_2282(void);
extern void sub_2262(void);
extern void sub_226C(void);
extern void sub_2D5E(int *par2, int *par3);
extern void leaf_2E39(void);
extern void frag_2C88(void); /* joins 2c88_ring_report_gate; see docs/evidence/extern-triage.md */
extern void sub_9E85(void); /* joins 9e85_wrap_9e85; see docs/evidence/extern-triage.md */
extern void sub_E64C(void); /* joins e64c_ext_call_stub_a; see docs/evidence/extern-triage.md */
extern void sub_3986(void);
extern void portseq_AC4C(void); /* joins ac4c_portseq_ac4c; see docs/evidence/extern-triage.md */
extern void frag_4883(void); /* joins 4883_frag_4883; see docs/evidence/extern-triage.md */
extern void sub_5C4F(void); /* joins 5c4f_sub_5c4f; see docs/evidence/extern-triage.md */
extern void frag_2000(void);
extern int port_read_3(void);                                         /* HW port 3 (supervisor cell per 2088 span); no ROM definition */
extern void port_write_3(int v);                                      /* HW port 3 (supervisor cell per 2088 span); no ROM definition */
extern int port_read_12(void);                                        /* HW port 12 (supervisor RMW per 2088 span); no ROM definition */
extern void port_write_12(int v);                                     /* HW port 12 (supervisor RMW per 2088 span); no ROM definition */
extern void port_write_14(int v);                                     /* HW port 14 (RF per 3EE1 span, 4999 preset); no ROM definition */
extern void port_write_48(int v);                                     /* HW port 48 (RF per 22F3/3cd2 spans); no ROM definition */
extern int port_read_2(void);                                         /* HW port 2 (FRAME sample combine per 27EB span); no ROM definition */
extern void port_write_2(int v);                                      /* HW port 2 (supervisor per 2875 precedent); no ROM definition */
extern void cpu_idle(int mode);                                       /* IDLE sleep (84af precedent: sleep until interrupt); no ROM definition */

void frag_2088(void)
{
    long a;
    long b;
    int *ar2;
    int *ar3;
    int *ar4;
    int *ar5;
    int *ar0loc;
    int taken;
    int tc_dark;  /* TC dark-callee-live (unbound, flagged) */
    int i;

l2088:
    sub_059C();                                            /* call 0x598 (RAM) */
    ar2 = (int *)4;                                        /* calld delay: stm */
    sub_2282();                                            /* calld 0x2282 */
    taken = tc_dark;                                       /* bc 0x20a8,ntc (unbound) */
    if (!taken)
        goto l20a8;
    ar2 = (int *)8706;                                     /* stm (poll base) */
    for (;;) {                                             /* b 0x2090 (poll; 2E39 diverts) */
        taken = (*ar2 == 0) != 0;                          /* cmpm *ar2,#0 */
        if (!taken)                                          /* cc 0x2e39,ntc */
            leaf_2E39();
        taken = (*(volatile int *)0x20FF & 2048) != 0;    /* bitf */
        if (taken)                                           /* cc 0x2e39,tc */
            leaf_2E39();
        ar2 = (int *)8446;                                 /* stm */
        taken = (*ar2 == 0) != 0;                          /* cmpm */
        if (!taken)                                          /* cc 0x2e39,ntc */
            leaf_2E39();
        taken = (*(volatile int *)0x866 & 3) != 0;         /* bitf */
        if (taken)                                           /* cc 0x2e39,tc */
            leaf_2E39();
    }
l20a8:
    taken = (*(volatile int *)0x1F2 & 1) != 0;             /* bitf *(0x1f2),#1 */
    *(volatile int *)0x1F2 |= 1;                           /* orm (always runs) */
    /* ssbx st1,xf (hardware, no C form) */
    sub_05B6();                                            /* call 0x5b6 (RAM) */
    *(volatile int *)0x58F &= -129;                        /* andm #-129 */
    taken = (*(volatile int *)0x58F & 15) != 0;            /* bitf */
    if (taken)                                             /* bc 0x2117,tc */
        goto l2117;
    a = (long)*(volatile int *)0x85D;                     /* ld *(0x85d),a */
    a &= 255L;                                             /* and #255,a */
    if (a != 0)                                            /* bc 0x20d8,aneq */
        goto l20d8;
    *(volatile int *)0x58F &= -129;                        /* andm #-129 */
    taken = (*(volatile int *)0x58F & 15) != 0;            /* bitf */
    if (taken)                                             /* bc 0x20d8,tc */
        goto l20d8;
    ar2 = (int *)8;                                        /* calld delay: stm */
    sub_2282();                                            /* calld 0x2282 */
    taken = tc_dark;                                       /* bc 0x20d8,tc (unbound) */
    if (taken)
        goto l20d8;
    *(volatile int *)0x537 &= -9;                           /* andm #-9 */
    sub_2262();                                            /* call 0x2262 */
    sub_226C();                                            /* call 0x226c */
    ar2 = (int *)3;                                        /* calld delay: stm */
    sub_2262();                                            /* calld 0x2262 */
l20d8:
    ar3 = (int *)1359;                                     /* stm #1359,ar3 */
    a = (long)*(volatile int *)0x3EC8;                     /* ld *(0x3ec8),a */
    a &= 16L;                                              /* and #16,a */
    taken = (*(volatile int *)0x589 & 3) != 0;              /* bitf (stale source) */
    if (a == 0)                                            /* xc 2,aeq (skips bitf only) */
        taken = (*ar3 & 1) != 0;                           /* bitf *ar3,#1 */
    if (taken)                                             /* bc 0x2123,tc */
        goto l2123;
    taken = (*ar3 & 128) != 0;                             /* bitf *ar3,#128 */
    if (taken)                                             /* bc 0x225e,tc */
        goto l225e;
    /* ssbx st1,intm (hardware, no C form) */
    *(volatile int *)0x8 = port_read_3();                   /* portr 3,*(0x8) (memory-only, A untouched) */
    a &= -257L;                                            /* and #-257,a (A = *(0x3ec8)&16 from 20DF) */
    /* nop (settle) */
    port_write_3(*(volatile int *)0x8);                     /* portw *(0x8),3 */
    for (i = 0; i < 22; i++) {}                            /* rpt #21 nop */
    a = 259;                                               /* ld #259,a */
    /* nop (settle) */
    port_write_48(*(volatile int *)0x8);                    /* portw *(0x8),48 */
    taken = (*(volatile int *)0x3EC8 & 32) != 0;          /* bitf *(0x3ec8),#32 */
    if (!taken)                                            /* bc 0x210c,ntc */
        goto l210c;
    a = (long)port_read_12();                              /* portr 12,*(0x8) */
    *(volatile int *)0x8 = (int)a;
    b = (long)*(volatile int *)0x3ECE;                     /* ld *(0x3ece),b */
    b = ~b & 0xFFFF;                                       /* cmpl b (2ACC: low16 exact) */
    a &= b;                                                /* and b,a */
    /* nop (settle) */
    port_write_12(*(volatile int *)0x8);                    /* portw *(0x8),12 */
l210c:
    taken = (*(volatile int *)0x58F & 15) != 0;            /* bitf */
    if (taken)                                             /* bc 0x2117,tc */
        goto l2117;
    ar2 = (int *)8;                                        /* calld delay: stm */
    sub_2282();                                            /* calld 0x2282 */
    taken = tc_dark;                                       /* cc 0x644,tc (unbound) */
    if (taken)
        sub_0644();                                        /* cc 0x644,tc (RAM) */
l2117:
    sub_05B6();                                            /* call 0x5b6 (RAM) */
    /* rsbx st1,intm (hardware, no C form) */
    leaf_2E39();                                           /* call 0x2e39 */
    sub_9E85();                                            /* call 0x9e85 */
    /* rsbx st1,intm (hardware, no C form) */
    sub_E64C();                                            /* call 0xe64c */
    goto l2088;                                            /* b 0x2088 (restart) */
l2123:
    sub_05B6();                                            /* call 0x5b6 (RAM) */
    taken = (*(volatile int *)0x58F & 15) != 0;            /* bitf */
    if (!taken)                                            /* bc 0x2134,ntc */
        goto l2134;
    *(volatile int *)0x2453 = 0;                           /* st #0,*(0x2453) */
    a = 1;                                                 /* ld #1,a */
    far_1AA1D();                                           /* fcall 0x1aa1d (uploaded) */
    ar2 = (int *)3;                                        /* calld delay: stm */
    sub_2262();                                            /* calld 0x2262 */
l2134:
    *(volatile int *)0x58F |= 128;                         /* orm #128 */
    taken = (*(volatile int *)0x1F2 & 2) != 0;             /* bitf *(0x1f2),#2 */
    *(volatile int *)0x1F2 |= 2;                           /* orm (always runs) */
    b = 1;                                                 /* ld #1,b */
    sub_070A();                                            /* call 0x70a (RAM) */
    *(volatile int *)0x54F = 0;                             /* st #0,*(0x54f) */
    *(volatile int *)0x263A |= 128;                         /* orm #128 */
    a = 0;                                                 /* ld #0,a */
    sub_3986();                                            /* call 0x3986 */
    portseq_AC4C();                                        /* call 0xac4c */
    a = 0;                                                 /* ld #0,a */
    sub_3986();                                            /* call 0x3986 */
    frag_4883();                                           /* call 0x4883 */
    taken = (*(volatile int *)0x3EC8 & 16) != 0;          /* bitf *(0x3ec8),#16 */
    if (!taken)                                            /* bc 0x2168,ntc */
        goto l2168;
    taken = (*(volatile int *)0x589 & 1) != 0;              /* bitf *(0x589),#1 */
    *(volatile int *)0x589 = 0;                             /* st #0 (always runs) */
    if (taken)                                             /* bc 0x2174,tc */
        goto l2174;
    *(volatile int *)0x263A |= 128;                         /* orm #128 */
    portseq_AC4C();                                        /* call 0xac4c */
    goto l218a;                                            /* b 0x218a */
l2168:
    taken = (*(volatile int *)0x51F & 16384) != 0;        /* bitf *(0x51f),#16384 */
    if (!taken)                                            /* bc 0x2174,ntc */
        goto l2174;
    *(volatile int *)0x263A |= 128;                         /* orm #128 */
    portseq_AC4C();                                        /* call 0xac4c */
    goto l2187;                                            /* b 0x2187 */
l2174:
    ar2 = (int *)3;                                        /* calld delay: stm */
    sub_226C();                                            /* calld 0x226c */
    b = 2;                                                 /* ld #2,b */
    sub_070A();                                            /* call 0x70a (RAM) */
    sub_05FE();                                            /* call 0x5fe (RAM) */
    taken = (*(volatile int *)0x3EC8 & 16) != 0;          /* bitf */
    if (taken) {                                           /* bc 0x2000,tc */
        frag_2000();
        return;
    }
    taken = (*(volatile int *)0x51F & 1024) != 0;         /* bitf *(0x51f),#1024 */
    if (taken) {                                           /* bc 0x2000,tc */
        frag_2000();
        return;
    }
l2187:
    *(volatile int *)0x2665 = *(volatile int *)0x38C9;    /* mvkd 0x38c9,*(0x2665) */
l218a:
    sub_05B6();                                            /* call 0x5b6 (RAM) */
    taken = (*(volatile int *)0x58F & 15) != 0;            /* bitf */
    if (!taken)                                            /* bc 0x219b,ntc */
        goto l219b;
    *(volatile int *)0x2453 = 0;                           /* st #0,*(0x2453) */
    a = 1;                                                 /* ld #1,a */
    far_1AA1D();                                           /* fcall 0x1aa1d (uploaded) */
    ar2 = (int *)3;                                        /* calld delay: stm */
    sub_2262();                                            /* calld 0x2262 */
l219b:
    *(volatile int *)0x58F |= 128;                         /* orm #128 */
    *(volatile int *)0x36A = 4999;                         /* st #4999,*(0x36a) */
    /* nop (settle) */
    port_write_14(*(volatile int *)0x36A);                 /* portw *(0x36a),14 */
    for (i = 0; i < 13; i++) {}                            /* rpt #12 nop */
    ar3 = (int *)(long)*(volatile int *)0x2665;            /* mvdm 0x2665,ar3 */
    taken = (*(volatile int *)0x3EC8 & 16) != 0;          /* bitf */
    if (!taken)                                            /* bc 0x21b9,ntc */
        goto l21b9;
    taken = (*(volatile int *)0x58A == 80) != 0;          /* cmpm *(0x58a),#80 */
    if (taken)                                             /* bc 0x21cb,tc */
        goto l21cb;
    taken = (*ar3 == -1) != 0;                             /* cmpm *ar3,#-1 */
    if (!taken)                                            /* bc 0x21d3,ntc */
        goto l21d3;
    goto l21cb;                                            /* b 0x21cb */
l21b9:
    a = 32767;                                             /* ld #32767,a */
    a = a - (long)*ar3;                                    /* sub *ar3,a */
    if (a != 0)                                            /* bc 0x21d3,aneq */
        goto l21d3;
    a = (long)ar3;                                         /* ldm ar3,a */
    b = 11262;                                             /* ld #11262,b */
    a = a - b;                                             /* sub b,a */
    if (a == 0)                                            /* bc 0x21cb,aeq */
        goto l21cb;
    a = (long)*(volatile int *)0x38CA;                    /* ld *(0x38ca),a */
    b = b - a;                                             /* sub a,b */
    *(volatile int *)0x2665 = (int)(a & 0xFFFF);          /* bcd delay: stl (runs, 2 words) */
    if (b != 0)                                            /* bcd 0x21d3,bneq */
        goto l21d3;
    /* fallthrough to l21cb */
l21cb:
    ar3 = (int *)2157;                                     /* stm #2157,ar3 */
    ar2 = (int *)135;                                      /* calld delay: stm */
    sub_2D5E(ar2, ar3);                                    /* calld 0x2d5e */
    frag_2000();                                           /* b 0x2000 (tail) */
    return;
l21d3:
    ar4 = (int *)(long)*(volatile int *)0x2665;            /* mvdm 0x2665,ar4 */
    ar3 = (int *)8;                                        /* stm #8,ar3 */
    *(volatile int *)0x2545 = *ar4;                         /* mvdk *ar4,0x2545 */
    /* ssbx st1,intm (hardware, no C form) */
    *(volatile int *)0x8 = port_read_2();                   /* portr 2,*ar3 (memory-only, A untouched) */
    *(volatile int *)0x8 |= 4096;                          /* orm #4096,*ar3 */
    /* nop (settle) */
    port_write_2(*(volatile int *)0x8);                     /* portw *ar3,2 */
    /* rsbx st1,intm (hardware, no C form) */
    *(volatile int *)0x56E = 0;                             /* st #0,*(0x56e) */
    ar2 = (int *)3;                                        /* calld delay: stm */
    sub_226C();                                            /* calld 0x226c */
    sub_0600();                                            /* call 0x600 (RAM) */
    *(volatile int *)0x56E = 1;                             /* st #1,*(0x56e) */
    taken = (*(volatile int *)0x3EC8 & 16) != 0;          /* bitf */
    if (!taken)                                            /* bc 0x21f9,ntc */
        goto l21f9;
    *(volatile int *)0x2665 += 2;                           /* addm #2 */
    *(volatile int *)0x58A += 1;                             /* addm #1 */
l21f9:
    *(volatile int *)0x2665 += -1;                          /* addm #-1 */
    leaf_2E39();                                           /* call 0x2e39 */
    a = (long)*(volatile int *)0x3EC8;                     /* ld *(0x3ec8),a */
    a &= 16L;                                              /* and #16,a */
    taken = (*(volatile int *)0x589 & 2) != 0;              /* bitf (stale source) */
    if (a == 0)                                            /* xc 2,aeq (skips bitf only) */
        taken = (*(volatile int *)0x54F & 1) != 0;         /* bitf *(0x54f),#1 */
    if (taken) {                                           /* bc 0x2000,tc */
        frag_2000();
        return;
    }
    taken = (*(volatile int *)0x2627 & 128) != 0;         /* bitf *(0x2627),#128 */
    if (taken)                                             /* bc 0x221f,tc */
        goto l221f;
    ar3 = (int *)12032;                                    /* stm #12032,ar3 */
    a = (long)*(volatile int *)0x2545;                    /* ld *(0x2545),a */
    *ar3 = (int)(a & 0xFFFF);                              /* stl a,*ar3 */
    ar5 = (int *)2;                                        /* stm #2,ar5 (dead, flagged) */
    ar3 = (int *)12032;                                    /* stm #12032,ar3 (dead, flagged) */
    ar4 = (int *)138;                                      /* calld delay: stm (2C88 may read, flagged) */
    frag_2C88();                                           /* calld 0x2c88 */
    goto l218a;                                            /* b 0x218a */
l221f:
    taken = (*(volatile int *)0x1F2 & 8) != 0;             /* bitf *(0x1f2),#8 */
    *(volatile int *)0x1F2 |= 8;                           /* orm (always runs) */
    b = 1;                                                 /* ld #1,b */
    sub_070A();                                            /* call 0x70a (RAM) */
    *(volatile int *)0x2627 = 8;                            /* st #8,*(0x2627) */
    *(volatile int *)0x2476 = 4;                            /* st #4,*(0x2476) */
    *(volatile int *)0x2546 = 48;                           /* st #48,*(0x2546) */
    *(volatile int *)0x2547 = 64;                           /* st #64,*(0x2547) */
    *(volatile int *)0x574 = 0;                             /* st #0,*(0x574) */
    /* fallthrough to l2237 */
l2237:
    leaf_2E39();                                           /* call 0x2e39 */
    ar0loc = (int *)1359;                                  /* stm #1359,ar0 (cell pointer) */
    a = (long)*(volatile int *)0x3EC8;                     /* ld *(0x3ec8),a */
    a &= 16L;                                              /* and #16,a */
    taken = (*(volatile int *)0x589 & 3) != 0;              /* bitf (stale source) */
    if (a == 0)                                            /* xc 2,aeq (skips bitf only) */
        taken = (*ar0loc & 1) != 0;                        /* bitf *ar0,#1 */
    if (taken) {                                           /* bc 0x2000,tc */
        frag_2000();
        return;
    }
    taken = (*ar0loc & 2) != 0;                            /* bitf *ar0,#2 */
    if (!taken)                                            /* bc 0x225e,ntc */
        goto l225e;
    *ar0loc &= -3;                                          /* andm #-3,*ar0 */
    *(volatile int *)0x263A |= 128;                         /* orm #128 */
    a = 0;                                                 /* ld #0,a */
    sub_3986();                                            /* call 0x3986 */
    portseq_AC4C();                                        /* call 0xac4c */
    a = 0;                                                 /* ld #0,a */
    sub_3986();                                            /* call 0x3986 */
    a = 0;                                                 /* rptz a,#8 */
    for (i = 0; i < 9; i++)                                /* (9 iters, idempotent) */
        *(volatile int *)0x912 = (int)(a & 0xFFFF);        /* mvmd al,0x912 */
    goto l218a;                                            /* b 0x218a */
l225e:
    sub_5C4F();                                            /* call 0x5c4f */
    goto l2237;                                            /* b 0x2237 (loop) */
    (void)ar5; (void)tc_dark;
}
