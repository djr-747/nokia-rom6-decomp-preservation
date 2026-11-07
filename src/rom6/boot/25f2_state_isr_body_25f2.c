/* ROM6 0x25F2 STATE_ISR_BODY_25F2 -- 503w.
 * Verified encoding: src/rom6/boot/25f2_state_isr_body_25f2.asm (recombine MATCH).
 * ORIGIN 0x25F2
 * EXPECT: 4807 F030 2000 F040 4900 8807 61F8 051F 2000 F820 2603 10F8 0020 80F8 0021 F073 27BE 61F8 051C 0800 F820 2610 11F8 20FA F310 0005 F84B 2610 F074 C851 F074 05F0 61F8 0577 0040 F820 2627 4820 880A F470 F470 F120 B495 F500 8912 F495 F495 1082 F461 F273 262C 7713 0244 7713 0244 6FF8 0020 0C44 5793 F736 4383 9A5F F50F F20F 0001 F483 F470 F583 818B 8383 61F8 051C 0C00 F820 2647 61F8 0577 2000 F930 06A0 61F8 0577 0100 F930 069A F074 06CC 4A08 4A09 4A0A 4A0B 4A0C 4A0D 4A06 4A07 4A13 4A12 61F8 04C2 0004 F830 2679 11F8 085D F330 0014 F84D 2679 7213 2A69 61F8 0577 0100 F930 069A 8093 60F8 2A69 32D5 7313 2A69 F820 2679 76F8 2A69 3236 7713 3236 7712 29C9 EC9F E598 69F8 057C 2000 8A12 8A13 8A07 8A06 8A0D 8A0C 8A0B 8A0A 8A09 8A08 F074 0714 61F8 058F 000F F820 26BC 4A06 4A07 4A19 4A12 6BF8 2967 0001 4A0B 4A0C 4A0D 13F8 2967 F310 0050 F84B 26B5 60F8 2966 0002 FA20 26B5 7719 0140 7212 296A 60F8 2969 0140 F820 26AD 6BF8 2968 0001 F073 26B5 80D2 80F8 2977 6BF8 2969 0001 7312 296A 8A0D 8A0C 8A0B 8A12 8A19 8A07 8A06 7213 01F3 7719 0278 4A08 61F8 051C 0400 F830 26D2 61F8 04C2 0004 F820 2702 F074 0724 80D3 F273 2702 7313 01F3 7712 20F7 74F8 000B 0036 F330 2000 F84D 26EB 11F8 20F9 F84D 26ED 11E2 0001 F495 75F8 000B 0034 4D82 6BF8 20F9 FFFF F073 26F3 F073 26F3 F495 75F8 0008 0034 F073 2702 11F8 20F9 F84C 26FE 80E2 0001 76F8 20F9 0001 F073 2702 8082 76F8 20F9 0002 8A0E F074 05F2 61F8 220B 0001 F830 271E 7713 0521 8C83 949E 6493 9C8F 648B CD7E 6393 6E21 678B 3711 4D83 8283 668B 3711 F463 F483 8283 3083 7719 0278 7213 054B 21F8 0855 F761 3ED3 F483 F470 F074 06CE 4A06 4A07 4A13 4A12 61F8 04C2 0004 F830 2769 61F8 085D 0004 F820 273E 61F8 058F 000F F830 273E E800 11F8 085D F330 0002 7213 057E F84D 2769 1093 60F8 057E 32D5 7313 057E F820 2769 76F8 057E 3236 69F8 057C 4000 11F8 057C F330 1000 F84D 2765 7713 32D6 7712 3236 EC9F E598 68F8 057C EFFF F073 2769 7712 3236 EC9F 8192 8A12 8A13 8A07 8A06 F074 0716 61F8 058F 000F F820 2775 F0C0 61F8 0577 0204 F930 069C 7313 054B 61F8 04D1 0001 F820 27B2 4A08 4A09 4A0A F074 B634 F470 7213 01F3 7719 0278 61F8 085D 0100 F820 2794 6DC3 1183 F500 8183 61F8 04C2 0004 8A0D 8A0C 8A0B F820 279D F600 F074 06D0 61F8 04C2 0004 F830 27B2 11F8 085D F330 0010 7213 2A69 F84D 27B2 6083 3236 F830 27B2 6D8B 8083 61F8 0577 0040 F820 27BC 4A16 F074 06B8 8A16 F463 F47D 8821 8A1C 8A1B 8A19 8A13 8A12 8A0E 8A0D 8A0C 8A0B 8A0A 8A09 8A08 8A07 8A06 F4E5 F074 05F4 4A07 4A08 4A09 4A0A 4A0B 4A0C 4A0D 4BF8 0060 4BF8 0061 4A0E 4A10 4A11 4A12 4A13 4A14 4A15 4A16 4A17 4A1A 4A1B 4A1C 4A19 771B 0000
 *
 * Intent: V20/INT4 STATE_ISR body, state-machine ISR per roms/rom6/ivt.md.
 * ST1 mode prologue; *(0x51F) gate selects the DRR/DXR echo fast path
 * (ld *(0x20) = DRR0/MMR 0x20, stl *(0x21) = DXR0/MMR 0x21 per sibling-emu
 * BSP mapping docs/5110-DSP-CANONICAL-STATE.md: writes DXR MMR 0x21, polls
 * DRR MMR 0x20) exiting via the 27BE epilogue; else mailbox copy *(0x20)->*(0x21),
 * *(0x51C) gate, frame counter *(0x20FA)-5, CALL 0xC851 (bound state_worker_C851)
 * then CALL 0x05F0 (RAM). McBSP path: LDM DRR0, AG temp, double sfta -16,
 * AGC gain block (ld #-19307, add, stlm-ar2 loop with sfta/bd), ld/shift/add
 * lane with SAT (identity in 32-bit long, 40-bit flagged per bf8c), nested
 * save + *(0x4C2)/*(0x85D) gates, round-robin store via AR3=*(0x2A69) with
 * wrap at 13013 (ST #12854 + RPT-160 MVDD), restore, CALL 0x714 (RAM).
 * Second half: frame counter ADDM, BK=320 circular single pass over AR2=*(0x296A) with
 * 26AD/26B5 joins, AR3=*(0x1F3) BK=632 lane, pa54 poll loop (AR2=0x20F7) with
 * DELAY (pipeline settle, no C form), CALL 0x724 (RAM), CALL 0x5F2 (RAM);
 * T-coefficient block on *(0x220B) bit 0 (LD/MAC/TMPY chain with DELAY, SFTA 3,
 * SAT; CALL 0x6CE (RAM)); exit cascade (bitf *(0x4C2)/*(0x85D)/*(0x58F) lanes,
 * round-robin stores with 13013/12854 wraps, RPT-160 fills); convergence 0x2769
 * (RPT-160 STL, restore, CALL 0x716 (RAM)); XOR a (=0 per oracle XOR_ACC_SHIFT
 * src/dst A shift 0), cc-069C (RAM), MVMD, save + CALL 0xB634 (asm-only gap,
 * forward extern) + SFTA/DXR0 transmit write (STLM a,DXR0 = *(0x21)); full
 * popm restore, FRETE@27CC. Sub-entry 27CD (V17/V18/V24 vectors FFC4/C8/E0):
 * FRAME prologue (call-05F4 + full pshm incl. PSHD *(0x60/0x61) Viterbi state +
 * STM RSA, flowing to 27E9/27EB). A dark across RAM callees (flagged);
 * SXM-widening flagged (ST1 dark); FRCT/OVM and circular wraps flagged;
 * bcd/bd = 2 delay WORDS per oracle test_cpu_bd; DST = 32-bit store
 * (MSW at address, LSW above per op_dst_smem_absolute).
 */
extern void sub_05F0(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_05F2(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_05F4(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_069A(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_069C(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_06A0(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_06B8(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_06CC(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_06CE(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_06D0(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_0714(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_0716(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_0724(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_B634(void); /* joins b634_gap_b634 (asm-only gap, HYPOTHESIS) */
extern void state_worker_C851(void);
extern int port13_stable_read(void);
extern int port_read_54(void);                                        /* HW port 54 (pa54 poll per 25F2 span); no ROM definition */
extern void port_write_52(int v);                                     /* HW port 52 (STATE writes per 25F2 span); no ROM definition */

void isr_body_25F2(void)
{
    long a;
    long b;
    long d;
    int *ar2;
    int *ar3;
    int t;
    int ag;
    int taken;
    int taken2;
    int i;

l25f2:
    /* ldm st1,a; and #8192,a; or #18688,a; stlm a,st1 (mode set, ST1 dark) */
    taken = (*(volatile int *)0x51F & 8192) != 0;                 /* bitf *(0x51f),#8192 */
    if (!taken)                                                  /* bc 0x2603,ntc */
        goto l2603;
    a = (long)*(volatile int *)0x20;                             /* ld *(0x20),a (DRR0) */
    *(volatile int *)0x21 = (int)(a & 0xFFFFL);                  /* stl a,*(0x21) (DXR0 echo) */
    goto l27be;                                                  /* b 0x27be */
l2603:
    taken = (*(volatile int *)0x51C & 2048) != 0;               /* bitf *(0x51c),#2048 */
    if (!taken)                                                  /* bc 0x2610,ntc */
        goto l2610;
    b = (long)*(volatile int *)0x20FA;                          /* ld *(0x20fa),b */
    b -= 5;                                                      /* sub #5,b */
    if (b < 0)                                                   /* bc 0x2610,blt */
        goto l2610;
    state_worker_C851();                                         /* call 0xc851 */
l2610:
    sub_05F0();                                                  /* call 0x5f0 (RAM) */
    taken = (*(volatile int *)0x577 & 64) != 0;                 /* bitf *(0x577),#64 */
    if (!taken)                                                  /* bc 0x2627,ntc */
        goto l2627;
    a = (long)*(volatile int *)0x20;                             /* ldm drr0,a (DRR0=MMR 0x20) */
    ag = (int)(a & 0xFFFFL);                                     /* stlm a,ag (AG temp, flagged) */
    a >>= 16;                                                    /* sfta a,-16 */
    a >>= 16;                                                    /* sfta a,-16 */
    b = -19307;                                                  /* ld #-19307,b */
    b += a;                                                      /* add a,b */
    ar2 = (int *)(b & 0xFFFFL);                                  /* stlm b,ar2 */
    /* nop; nop */
    a = (long)*ar2;                                              /* ld *ar2,a */
    a <<= 1;                                                     /* sfta a,1 */
    /* bd 0x262c (delay: stm #580,ar3 runs) */
    ar3 = (int *)580;
    goto l262c;                                                  /* bd */
l2627:
    ar3 = (int *)580;                                           /* stm #580,ar3 */
    a = (long)*(volatile int *)0x20 << 4;                        /* ld *(0x20),4,a (SXM flagged) */
l262c:
    b = (long)*(ar3++);                                          /* dld *ar3+,b (SXM flagged) */
    b = b - (b >> 10);                                           /* sub b,-10 (decay lane, flagged) */
    b -= (long)*ar3 << 16;                                       /* sub *ar3,16,b (SXM flagged) */
    *(ar3--) = (int)(((a << 15) >> 24) & 0xFFFFL);              /* sth a,15,*ar3- (bits 31-16 of A<<15, per op_sth) */
    b += (a << 15);                                              /* add a,15,b */
    a = b + (1L << 15);                                          /* add #1,15,b,a */
    /* sat a (identity in long; 40-bit flagged) */
    a >>= 16;                                                    /* sfta a,-16 */
    /* sat b (identity in long; 40-bit flagged) */
    *(ar3--) = (int)(b & 0xFFFFL);                               /* stl b,*ar3- */
    *ar3 = (int)((b >> 16) & 0xFFFFL);                           /* sth b,*ar3 */
    taken = (*(volatile int *)0x51C & 3072) != 0;               /* bitf *(0x51c),#3072 */
    if (!taken)                                                  /* bc 0x2647,ntc */
        goto l2647;
    taken = (*(volatile int *)0x577 & 8192) != 0;                /* bitf *(0x577),#8192 */
    if (taken) {                                                 /* cc 0x6a0,tc (RAM) */
        sub_06A0();
    }
    taken = (*(volatile int *)0x577 & 256) != 0;                /* bitf *(0x577),#256 */
    if (taken) {                                                 /* cc 0x69a,tc (RAM) */
        sub_069A();
    }
l2647:
    sub_06CC();                                                  /* call 0x6cc (RAM) */
    /* pshm al/ah/ag/bl/bh/bg/st0/st1/ar3/ar2 (caller-live, comments only) */
    taken = (*(volatile int *)0x4C2 & 4) != 0;                  /* bitf *(0x4c2),#4 */
    if (taken)                                                   /* bc 0x2679,tc */
        goto l2679;
    b = (long)*(volatile int *)0x85D;                           /* ld *(0x85d),b */
    b &= 20L;                                                    /* and #20,b */
    if (b == 0)                                                  /* bc 0x2679,beq */
        goto l2679;
    ar3 = (int *)(long)*(volatile int *)0x2A69;                 /* mvdm 0x2a69,ar3 */
    taken = (*(volatile int *)0x577 & 256) != 0;                /* bitf *(0x577),#256 */
    if (taken)                                                   /* cc 0x69a,tc (RAM) */
        sub_069A();
    *(ar3++) = (int)(a & 0xFFFFL);                               /* stl a,*ar3+ (A dark across 06CC, flagged) */
    taken = (*(volatile int *)0x2A69 == 13013) != 0;           /* cmpm *(0x2a69),#13013 */
    *(volatile int *)0x2A69 = (int)(long)ar3;                   /* mvmd ar3,0x2a69 */
    if (!taken)                                                  /* bc 0x2679,ntc */
        goto l2679;
    *(volatile int *)0x2A69 = 12854;                             /* st #12854 (wrap) */
    ar3 = (int *)12854;
    ar2 = (int *)10697;
    for (i = 0; i < 160; i++)                                    /* rpt #159 */
        *(ar2++) = *(ar3++);                                     /* mvdd *ar3+,*ar2+ */
    *(volatile int *)0x57C |= 8192;                              /* orm #8192 */
l2679:
    /* popm ar2/ar3/st1/st0/bg/bh/bl (restore entry state) */
    sub_0714();                                                  /* call 0x714 (RAM) */
    taken = (*(volatile int *)0x58F & 15) != 0;                 /* bitf *(0x58f),#15 */
    if (!taken)                                                  /* bc 0x26bc,ntc */
        goto l26bc;
    /* pshm st0/st1/bk/ar2 (caller-live, comments only) */
    *(volatile int *)0x2967 += 1;                                 /* addm #1 */
    /* pshm bl/bh/bg */
    b = (long)(unsigned)*(volatile int *)0x2967;                /* ldu *(0x2967),b (zero-extend) */
    b -= 80;                                                     /* sub #80,b */
    if (b < 0)                                                   /* bc 0x26b5,blt */
        goto l26b5;
    taken = (*(volatile int *)0x2966 == 2) != 0;                /* cmpm *(0x2966),#2 */
    /* bcd 0x26b5,ntc (delay: stm #320,bk runs) */
    /* stm #320,bk */
    if (!taken)
        goto l26b5;
    ar2 = (int *)(long)*(volatile int *)0x296A;                  /* mvdm 0x296a,ar2 */
    taken = (*(volatile int *)0x2969 == 320) != 0;              /* cmpm *(0x2969),#320 */
    if (!taken)                                                  /* bc 0x26ad,ntc */
        goto l26ad;
    *(volatile int *)0x2968 += 1;                                 /* addm #1 */
    goto l26b5;                                                  /* b 0x26b5 */
l26ad:
    *(ar2++) = (int)(a & 0xFFFFL);                               /* stl a,*ar2+% (A dark, flagged) */
    *(volatile int *)0x2977 = (int)(a & 0xFFFFL);                /* stl a,*(0x2977) */
    *(volatile int *)0x2969 += 1;                                 /* addm #1 */
    *(volatile int *)0x296A = (int)(long)ar2;                    /* mvmd ar2,0x296a */
l26b5:
    /* popm bg/bh/bl/ar2/bk/st1/st0 (restore entry state) */
l26bc:
    ar3 = (int *)(long)*(volatile int *)0x1F3;                   /* mvdm 0x1f3,ar3 */
    /* stm #632,bk */
    /* pshm al (caller-live, comment only) */
    taken = (*(volatile int *)0x51C & 1024) != 0;              /* bitf *(0x51c),#1024 */
    if (taken)                                                   /* bc 0x26d2,tc */
        goto l26d2;
    taken = (*(volatile int *)0x4C2 & 4) != 0;                  /* bitf *(0x4c2),#4 */
    if (!taken)                                                  /* bc 0x2702,ntc */
        goto l2702;
    sub_0724();                                                  /* call 0x724 (RAM) */
    *(ar3++) = (int)(a & 0xFFFFL);                               /* stl a,*ar3+% (A dark, flagged) */
    /* bd 0x2702 (delay: mvmd ar3,0x1f3 runs) */
    *(volatile int *)0x1F3 = (int)(long)ar3;
    goto l2702;                                                  /* bd */
l26d2:
    ar2 = (int *)8439;                                          /* stm #8439,ar2 */
    *(volatile int *)0xB = port_read_54();                       /* portr pa54,*(0xb) */
    b &= 8192L;                                                  /* and #8192,b */
    if (b == 0)                                                  /* bc 0x26eb,beq */
        goto l26eb;
    b = (long)*(volatile int *)0x20F9;                           /* ld *(0x20f9),b */
    if (b == 0)                                                  /* bc 0x26ed,beq */
        goto l26ed;
    b = (long)*(ar2 + 1);                                        /* ld *ar2(0x1),b */
    /* nop */
    port_write_52(*(volatile int *)0xB);                          /* portw *(0xb),pa52 */
    /* delay *ar2 (pipeline settle, no C form) */
    *(volatile int *)0x20F9 += -1;                               /* addm #-1 */
    goto l26f3;                                                  /* b 0x26f3 */
l26eb:
    goto l26f3;                                                  /* b 0x26f3 */
l26ed:
    /* nop */
    port_write_52(*(volatile int *)0x8);                         /* portw *(0x8),pa52 */
    goto l2702;                                                  /* b 0x2702 */
l26f3:
    b = (long)*(volatile int *)0x20F9;                           /* ld *(0x20f9),b */
    if (b != 0)                                                  /* bc 0x26fe,bneq */
        goto l26fe;
    *(ar2 + 1) = (int)(a & 0xFFFFL);                             /* stl a,*ar2(0x1) (A dark, flagged) */
    *(volatile int *)0x20F9 = 1;                                 /* st #1 */
    goto l2702;                                                  /* b 0x2702 */
l26fe:
    *ar2 = (int)(a & 0xFFFFL);                                   /* stl a,*ar2 (A dark, flagged) */
    *(volatile int *)0x20F9 = 2;                                 /* st #2 */
l2702:
    /* popm t (T restore) */
    sub_05F2();                                                  /* call 0x5f2 (RAM) */
    taken = (*(volatile int *)0x220B & 1) != 0;                 /* bitf *(0x220b),#1 (RSSI selector) */
    if (taken)                                                   /* bc 0x271e,tc */
        goto l271e;
    ar3 = (int *)0x521;                                         /* stm #1313,ar3 */
    *ar3 = t;                                                    /* st t,*ar3 */
    a = (long)*(ar3++) << 14;                                    /* ld *ar3+,14,a (SXM flagged) */
    a += (long)*(ar3++) * -25457L;                               /* mac *ar3+,#-25457,a (FRCT/OVM flagged) */
    a += (long)*ar3 * -12930L;                                   /* mac *ar3-,#-12930,a */
    ar3--;
    t = *ar3;                                                    /* tmpy *ar3+,#28193,b: T = *AR3+ */
    b = (long)t * 28193L;                                        /* (FRCT flagged) */
    ar3++;
    b += (long)*ar3 * 14097L;                                    /* mac *ar3-,#14097,b */
    ar3--;
    /* delay *ar3 (pipeline settle, no C form) */
    *ar3 = (int)((a >> 16) & 0xFFFFL);                           /* sth a,*ar3 */
    a = b + (long)*ar3 * 14097L;                                 /* mac *ar3-,#14097,b,a */
    ar3--;
    a <<= 3;                                                     /* sfta a,3 */
    /* sat a (identity in long; 40-bit flagged) */
    *ar3 = (int)((a >> 16) & 0xFFFFL);                           /* sth a,*ar3 */
    t = *ar3;                                                    /* ld *ar3,t */
l271e:
    /* stm #632,bk */
    ar3 = (int *)(long)*(volatile int *)0x54B;                   /* mvdm 0x54b,ar3 */
    b = (long)*(volatile int *)0x855 * (long)t;                  /* mpy *(0x855),b (FRCT flagged) */
    b <<= 1;                                                     /* sfta b,1 */
    a = b + ((long)*ar3 << 16);                                  /* add *ar3+%,16,b,a (SXM flagged) */
    ar3++;                                                       /* (+% BK=632 flagged) */
    /* sat a (identity in long; 40-bit flagged) */
    a >>= 16;                                                    /* sfta a,-16 */
    sub_06CE();                                                  /* call 0x6ce (RAM) */
    /* pshm st0/st1/ar3/ar2 (caller-live, comments only) */
    taken = (*(volatile int *)0x4C2 & 4) != 0;                  /* bitf *(0x4c2),#4 */
    if (taken)                                                   /* bc 0x2769,tc */
        goto l2769;
    taken = (*(volatile int *)0x85D & 4) != 0;                  /* bitf *(0x85d),#4 */
    if (!taken)                                                  /* bc 0x273e,ntc */
        goto l273e;
    taken = (*(volatile int *)0x58F & 15) != 0;                 /* bitf *(0x58f),#15 */
    if (taken)                                                   /* bc 0x273e,tc */
        goto l273e;
    a = 0;                                                       /* ld #0,a */
l273e:
    b = (long)*(volatile int *)0x85D;                           /* ld *(0x85d),b */
    b &= 2L;                                                     /* and #2,b */
    ar3 = (int *)(long)*(volatile int *)0x57E;                   /* mvdm 0x57e,ar3 */
    if (b == 0)                                                  /* bc 0x2769,beq */
        goto l2769;
    a = (long)*(ar3++);                                          /* ld *ar3+,a */
    taken = (*(volatile int *)0x57E == 13013) != 0;             /* cmpm *(0x57e),#13013 */
    *(volatile int *)0x57E = (int)(long)ar3;                     /* mvmd ar3,0x57e */
    if (!taken)                                                  /* bc 0x2769,ntc */
        goto l2769;
    *(volatile int *)0x57E = 12854;                               /* st #12854 (wrap) */
    *(volatile int *)0x57C |= 16384;                             /* orm #16384 */
    b = (long)*(volatile int *)0x57C;                           /* ld *(0x57c),b */
    b &= 4096L;                                                  /* and #4096,b */
    if (b == 0)                                                  /* bc 0x2765,beq */
        goto l2765;
    ar3 = (int *)13014;
    ar2 = (int *)12854;
    for (i = 0; i < 160; i++)                                    /* rpt #159 */
        *(ar2++) = *(ar3++);                                     /* mvdd *ar3+,*ar2+ */
    *(volatile int *)0x57C &= -4097;                             /* andm #-4097 */
    goto l2769;                                                  /* b 0x2769 */
l2765:
    ar2 = (int *)12854;
    for (i = 0; i < 160; i++)
        *(ar2++) = (int)(b & 0xFFFFL);                           /* stl b,*ar2+ */
l2769:
    /* popm ar2/ar3/st1/st0 (restore entry state) */
    sub_0716();                                                  /* call 0x716 (RAM) */
    taken = (*(volatile int *)0x58F & 15) != 0;                 /* bitf *(0x58f),#15 */
    if (!taken)                                                  /* bc 0x2775,ntc */
        goto l2775;
    a = 0;                                                       /* xor a (A^A; oracle XOR_ACC_SHIFT) */
    taken = (*(volatile int *)0x577 & 516) != 0;                /* bitf *(0x577),#516 */
    if (taken)                                                   /* cc 0x69c,tc (RAM) */
        sub_069C();
    *(volatile int *)0x54B = (int)(long)ar3;                     /* mvmd ar3,0x54b */
    taken = (*(volatile int *)0x4D1 & 1) != 0;                  /* bitf *(0x4d1),#1 */
    if (!taken)                                                  /* bc 0x27b2,ntc */
        goto l27b2;
    /* pshm al/ah/ag (caller-live, comments only) */
    sub_B634();                                                  /* call 0xb634 (gap, HYPOTHESIS) */
    a >>= 16;                                                    /* sfta a,-16 (A dark across B634, flagged) */
    ar3 = (int *)(long)*(volatile int *)0x1F3;                   /* mvdm 0x1f3,ar3 */
    /* stm #632,bk */
    taken = (*(volatile int *)0x85D & 256) != 0;                /* bitf *(0x85d),#256 */
    if (!taken)                                                  /* bc 0x2794,ntc */
        goto l2794;
    ar3--;                                                       /* mar *ar3-% */
    b = (long)*ar3;                                              /* ld *ar3,b */
    b += a;                                                      /* add a,b */
    *ar3 = (int)(b & 0xFFFFL);                                   /* stl b,*ar3 */
l2794:
    taken = (*(volatile int *)0x4C2 & 4) != 0;                  /* bitf *(0x4c2),#4 */
    /* popm bg/bh/bl (restore entry state) */
    if (!taken)                                                  /* bc 0x279d,ntc */
        goto l279d;
    a += b;                                                      /* add b,a */
l279d:
    sub_06D0();                                                  /* call 0x6d0 (RAM) */
    taken = (*(volatile int *)0x4C2 & 4) != 0;                  /* bitf *(0x4c2),#4 */
    if (taken)                                                   /* bc 0x27b2,tc */
        goto l27b2;
    b = (long)*(volatile int *)0x85D;                           /* ld *(0x85d),b */
    b &= 16L;                                                    /* and #16,b */
    ar3 = (int *)(long)*(volatile int *)0x2A69;                 /* mvdm 0x2a69,ar3 */
    if (b == 0)                                                  /* bc 0x27b2,beq */
        goto l27b2;
    taken = (*ar3 == 12854) != 0;                                /* cmpm *ar3,#12854 */
    if (taken)                                                   /* bc 0x27b2,tc */
        goto l27b2;
    ar3--;                                                       /* mar *ar3- */
    *ar3 = (int)(a & 0xFFFFL);                                   /* stl a,*ar3 (A dark across 06D0, flagged) */
l27b2:
    taken = (*(volatile int *)0x577 & 64) != 0;                 /* bitf *(0x577),#64 */
    if (!taken)                                                  /* bc 0x27bc,ntc */
        goto l27bc;
    /* pshm ar6 (caller-live, comment only) */
    sub_06B8();                                                  /* call 0x6b8 (RAM) */
    /* popm ar6 */
    a <<= 3;                                                     /* sfta a,3 (A dark, flagged) */
l27bc:
    a >>= 16;                                                    /* sfta a,-16 */
    *(volatile int *)0x21 = (int)(a & 0xFFFFL);                  /* stlm a,dxr0 (DXR0=MMR 0x21) */
l27be:
    /* popm rea/rsa/bk/ar3/ar2/t/bg/bh/bl/ag/ah/al/st1/st0 */
    /* frete (interrupt return, non-delayed exact 0xF4E5, no C form) */
l27cd:
    sub_05F4();                                                  /* call 0x5f4 (RAM) */
    /* pshm st1/al/ah/ag/bl/bh/bg; pshd *(0x60); pshd *(0x61); pshm t/ar0-ar7/brc/rsa/rea/bk */
    /* stm #0,rsa (MMR, no C form) */
    /* span ends at the 27E7-27E8 instruction boundary; 27E9 slot abuts, then 27EB */
    (void)t; (void)ag; (void)taken2; (void)i; (void)d;
}
