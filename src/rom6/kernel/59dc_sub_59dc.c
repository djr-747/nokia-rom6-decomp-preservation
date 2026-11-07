/* ROM6 ORIGIN 0x59DC (140w): SUB_59DC -- dispatch-table scan lanes plus RPTB packer.
 * Verified encoding: src/rom6/kernel/59dc_sub_59dc.asm (recombine MATCH).
 * ORIGIN 0x59DC
 * EXPECT: F074 059C 11F8 24F4 F310 0070 10F8 0060 FA44 59EA 7712 261E F84C 59F5 E800 7692 FFEB 809A 80F8 24F4 7713 264C 8083 F073 59FF 1082 F000 0001 F110 0004 7713 264C FD4A F640 8082 7714 0160 7715 0060 7685 000F 1083 62F8 0008 0039 F47F 60F8 250F 0022 F820 5A2F 60F8 37DB 37DB F820 5A29 61F8 3490 0001 F820 5A29 00F8 352C 80F8 37DC F020 3532 76F8 37DA 0000 F808 5A40 76F8 37DA 0001 F073 5A33 FA08 5A40 00F8 352C F073 5A33 FA08 5A40 F000 2B1C 8811 1094 1885 1181 F330 00FF F1A8 1094 1885 F273 5A41 F1AC 8191 8811 771A 001B F072 5A50 1194 1985 1094 1885 F1A4 1094 1885 F1A8 1094 1885 F1AC 8191 1083 F47F 1181 F330 FF00 FA0C 5A5F 1094 1885 F1A0 1094 1885 F1A4 8181 1083 F110 0015 F000 0001 FD4D E800 8083 FC00
 *
 * Intent: Cell-dispatch head, qualifier chain, RPTB lane packer, tail.
 * Runs dark SUB_059C (opaque, forward extern; A/B rewritten after,
 * outputs dead). B = *(0x24F4) - 112; A = *(0x60) (plain DARAM cell,
 * not the 0x8 AL-alias). bcd 0x59EA,aneq under WORD-count delay slots
 * (ti-c54x delayed_branch oracle: the 2-word stm fills the window, so
 * the bcd fires before the next word; taken runs A != 0 to 59EA,
 * untaken falls to the bc). A == 0 lane (59EA): A = 0; *AR2+ = -21
 * (AR2 9758->9759, st #lk indirect post-inc); *+AR2 = 0 with pre-inc
 * (AR2 9759->9760, the *+ pre-increment form proven by the
 * gap-preserving store pattern shared with 5825); *(0x24F4) = 0;
 * AR3 = 9804; *AR3 = 0; jump to 59FF. B != 0 lane (59F5): A = *AR2
 * (0x261E); A += 1; B = A - 4; AR3 = 9804; B >= 0 keeps A = B
 * (xc 1,bgeq taken-runs); *AR2 = A-low; join 59FF.
 * 59FF join: AR4 = 352, AR5 = 96; *(96) = 15 (mask; written before
 * first and-use, so the mask is provably 15 and non-negative --
 * guard-clear at every and, beq tests exact). A = *AR3;
 * A = ALIAS(0x8) * 57 (mpy Smem,#lk, 311f precedent: plain signed
 * long multiply, T = Smem dead flagged; 16-bit inputs bound the
 * product under 2^30, so bit31 stays clear under either SXM
 * extension and every downstream add fits int32 -- proven, no SXM
 * or OVM flag needed); A >>= 1 arith (sfta a,-1; C = old bit0 per
 * oracle op_sfta_acc, tracked below). Qualifier chain:
 * *(0x250F) == 34 else jump bcd#2 (bc ntc); *(0x37DB) == 0x37DB
 * (cmpm 3-word: cell, address-word, immediate-word coincide) else
 * jump bcd#1; *(0x3490) & 1 else jump bcd#1 (bitf mask test).
 * Head-lane fallthrough: A += *(0x352C) with C = low32 carry
 * (oracle op_add_smem syntaxes 1-2 write C from bit-32 carry; carry
 * via the unsigned comparison form (32-bit-long clean), sums proven
 * under 2^31, no wrap);
 * *(0x37DC) = A-low; A = 13618; *(0x37DA) = 0;
 * C == 0 chains to 5A40 (bc nc), else *(0x37DA) = 1, jump 5A33.
 * bcd#1 (C from the 5A19 add): the add delay fills the window, so
 * NC-taken jumps to 5A40 SKIPPING the b at 5A2D, while C-fallthrough
 * runs the b to 5A33 (word-count rule). bcd#2 (5A2F, same shape):
 * its add delay fills the window; NC-taken jumps to 5A40 SKIPPING
 * the stlm at 5A33, C-fallthrough runs the stlm (AR1 = A-low16,
 * masked: STLM stores low16, masked here where 56a2 bare-casts --
 * exactness over consistency) and continues into the RPTB.
 * 5A33/5A40 join: AR1 = A-low16 (computed address, plain deref per
 * AR convention); RPTB block 5A45-5A50 (non-delayed rptb, RSA =
 * first word after, BRC = 27, 28 passes, inclusive REA per oracle
 * repeat_block) packs three masked cells per pass:
 * B = (*AR4+ & 15); A = (*AR4+ & 15); B |= A<<4; A = (*AR4+ & 15);
 * B |= A<<8; A = (*AR4+ & 15); B |= A<<12 (OR_ACC_SHIFT dst |=
 * src<<shift, 7ea7 precedent; all parts non-negative, B exact);
 * *AR1++ = B-low. AR4 walks 352+84 to 436, AR1 walks +28.
 * A = *AR3 (9804); A >>= 1 (C = old bit0); B = *AR1 (base+28);
 * B &= 0xFF00; bcd 0x5A5F,c: ld/and delays fill the window and run
 * on both paths; C-taken jumps to 5A5F SKIPPING the re-run, while
 * C-fallthrough re-executes ld+and (AR4 advances twice -- word-count
 * rule), then B |= A, A = next masked, B |= A<<4, *AR1 = B-low.
 * Tail: A = *AR3; B = A - 21; A += 1; B == 0 zeroes A (xc 1,beq)
 * and *AR3 = A-low; return (ret, no delay). No params (AR2-AR5/BRC
 * set in-span; AR0/AR1 untouched-before-set... AR1 set via stlm on
 * all paths; A/B rewritten after the dark head call) and void
 * (A/B live-outs are the tail stores, consumed in memory; the
 * SUB_5993 caller discards registers). OR/SUB/ADD C-actions between
 * the modeled writers and the four reads are dead at every read
 * (overwritten or unread -- audited per path), so only sfta-C and
 * add-carry are tracked. Bound 59DC-5A67 (ret FC00@5A67; abuts
 * next span at 5A68). Entry call F074@5995 from FRAG_5993.
 */
extern void sub_059C(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void sub_59DC(void)
{
    long a;
    long b;
    int c = 0;  /* overwritten before first read (5A09 sfta) on all paths */
    int taken;
    int i;
    int *ar1;
    int *ar2;
    int *ar3;
    int *ar4;
    int *ar5;

    sub_059C();                                            /* call 0x59c */
    b = (long)*(volatile int *)0x24F4;                    /* ld *(0x24f4),b */
    b -= 112L;                                            /* sub #112,b */
    a = (long)*(volatile int *)0x0060;                    /* ld *(0x60),a */
    ar2 = (int *)0x261E;                                  /* bcd delay (fills window) */
    taken = (a != 0);                                     /* bcd pre-decode test */
    if (!taken)                                           /* bcd untaken */
        goto lane_59F5;
    a = 0;                                                /* ld #0,a (59EA lane) */
    *ar2++ = -21;                                         /* st #-21,*ar2+ */
    *++ar2 = (int)(a & 0xFFFF);                           /* stl a,*+ar2 (pre-inc) */
    *(volatile int *)0x24F4 = (int)(a & 0xFFFF);          /* stl a,0x24f4 */
    ar3 = (int *)0x264C;                                  /* stm #9804,ar3 */
    *ar3 = (int)(a & 0xFFFF);                             /* stl a,*ar3 */
    goto join_59FF;                                       /* b 0x59ff */
lane_59F5:                                                /* B != 0 lane */
    a = (long)*ar2;                                       /* ld *ar2,a */
    a += 1L;                                              /* add #1,a */
    b = a - 4L;                                           /* sub #4,a,b */
    ar3 = (int *)0x264C;                                  /* stm #9804,ar3 */
    if (b >= 0)                                           /* xc 1,bgeq */
        a = b;                                            /* ld b,a */
    *ar2 = (int)(a & 0xFFFF);                             /* stl a,*ar2 */
join_59FF:                                                /* 59FF join */
    ar4 = (int *)352;                                     /* stm #352,ar4 */
    ar5 = (int *)96;                                      /* stm #96,ar5 */
    *ar5 = 15;                                            /* st #15,*ar5 (mask) */
    a = (long)*ar3;                                       /* ld *ar3,a */
    a = (long)*(volatile int *)0x8 * 57L;                 /* mpy AL-alias (T flagged) */
    c = (int)(a & 1L);                                    /* sfta C = shift-out bit */
    a >>= 1;                                              /* sfta a,-1 */
    if (*(volatile int *)0x250F != 34)                    /* cmpm; bc ntc */
        goto bcd2_5A2F;
    if (*(volatile int *)0x37DB != 0x37DB)                 /* cmpm; bc ntc */
        goto bcd1_5A29;
    if ((*(volatile int *)0x3490 & 1) == 0)               /* bitf; bc ntc */
        goto bcd1_5A29;
    c = ((unsigned)a > 0xFFFFFFFFUL - (unsigned)*(volatile int *)0x352C);
    a = (long)((unsigned)a + (unsigned)*(volatile int *)0x352C); /* add (proven fits) */
    *(volatile int *)0x37DC = (int)(a & 0xFFFF);          /* stl a,0x37dc */
    a = 13618L;                                           /* ld #13618,a */
    *(volatile int *)0x37DA = 0;                          /* st #0,0x37da */
    if (c == 0)                                           /* bc 0x5a40,nc */
        goto join_5A40;
    *(volatile int *)0x37DA = 1;                          /* st #1,0x37da */
    goto join_5A33;                                       /* b 0x5a33 */
bcd1_5A29:                                                /* 5A29 bcd */
    c = ((unsigned)a > 0xFFFFFFFFUL - (unsigned)*(volatile int *)0x352C);
    a = (long)((unsigned)a + (unsigned)*(volatile int *)0x352C); /* delay-add (fills window) */
    if (c == 0)                                           /* bcd taken: skips b */
        goto join_5A40;
    goto join_5A33;                                       /* fallthrough: b 0x5a33 */
bcd2_5A2F:                                                /* 5A2F bcd */
    c = ((unsigned)a > 0xFFFFFFFFUL - 11036U);            /* delay-add carry */
    a = (long)((unsigned)a + 11036U);                     /* delay-add (fills window) */
    if (c == 0)                                           /* bcd taken: skips stlm */
        goto join_5A40;
    /* fallthrough: stlm runs, then RPTB */
join_5A33:                                                /* 5A33 join */
    ar1 = (int *)(int)(a & 0xFFFF);                            /* stlm a,ar1 (low16) */
    a = (long)*ar4++;                                     /* ld *ar4+,a */
    a &= (long)*ar5;                                      /* and *ar5,a */
    b = (long)*ar1;                                       /* ld *ar1,b */
    b &= 255L;                                            /* and #255,b */
    b |= (a << 8);                                        /* or a,8,b */
    a = (long)*ar4++;                                     /* ld *ar4+,a */
    a &= (long)*ar5;                                      /* and *ar5,a */
    b |= (a << 12);                                       /* bd delay: or a,12,b */
    *ar1++ = (int)(b & 0xFFFF);                           /* bd delay: stl b,*ar1+ */
    goto rptb_5A45;                                       /* bd 0x5a41 fires */
join_5A40:                                                /* 5A40 join */
    ar1 = (int *)(int)(a & 0xFFFF);                            /* stlm a,ar1 (low16) */
rptb_5A45:                                                /* RPTB 5A45-5A50 x28 */
    for (i = 0; i < 28; i++) {
        b = (long)*ar4++;                                  /* ld *ar4+,b */
        b &= (long)*ar5;                                   /* and *ar5,b */
        a = (long)*ar4++;                                  /* ld *ar4+,a */
        a &= (long)*ar5;                                   /* and *ar5,a */
        b |= (a << 4);                                     /* or a,4,b */
        a = (long)*ar4++;                                  /* ld *ar4+,a */
        a &= (long)*ar5;                                   /* and *ar5,a */
        b |= (a << 8);                                     /* or a,8,b */
        a = (long)*ar4++;                                  /* ld *ar4+,a */
        a &= (long)*ar5;                                   /* and *ar5,a */
        b |= (a << 12);                                    /* or a,12,b */
        *ar1++ = (int)(b & 0xFFFF);                        /* stl b,*ar1+ */
    }
    a = (long)*ar3;                                       /* ld *ar3,a */
    c = (int)(a & 1L);                                    /* sfta C = shift-out bit */
    a >>= 1;                                              /* sfta a,-1 */
    b = (long)*ar1;                                       /* ld *ar1,b */
    b &= 0xFF00L;                                         /* and #-256,b */
    a = (long)*ar4++;                                     /* bcd delay: ld */
    a &= (long)*ar5;                                      /* bcd delay: and */
    if (c != 0)                                           /* bcd taken: skips re-run */
        goto tail_5A5F;
    a = (long)*ar4++;                                     /* fallthrough re-runs ld */
    a &= (long)*ar5;                                      /* fallthrough re-runs and */
    b |= a;                                               /* or a,b */
    a = (long)*ar4++;                                     /* ld *ar4+,a */
    a &= (long)*ar5;                                      /* and *ar5,a */
    b |= (a << 4);                                        /* or a,4,b */
    *ar1 = (int)(b & 0xFFFF);                             /* stl b,*ar1 */
tail_5A5F:                                                /* 5A5F tail */
    a = (long)*ar3;                                       /* ld *ar3,a */
    b = a - 21L;                                          /* sub #21,a,b */
    a += 1L;                                              /* add #1,a */
    if (b == 0)                                           /* xc 1,beq */
        a = 0;                                            /* ld #0,a */
    *ar3 = (int)(a & 0xFFFF);                             /* stl a,*ar3 */
    /* ret */
}
