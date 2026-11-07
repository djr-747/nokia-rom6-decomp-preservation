/* ROM6 ORIGIN 0x5993 (73w): FRAG_5993 -- OVM add-lane fan with shared tail.
 * Verified encoding: src/rom6/kernel/5993_frag_5993.asm (recombine MATCH).
 * ORIGIN 0x5993
 * EXPECT: F074 059C F074 59DC 7711 2620 7712 261E 7713 01D2 7714 2621 7715 2622 1081 F7B9 F845 59C1 6B81 0001 F110 0004 F84B 59C6 F84D 59CA F110 0007 F84B 59D0 A039 8285 A021 8284 FA42 59D4 7681 0004 E800 8084 7710 2F02 F6B9 FE00 7680 00B0 E901 F273 59D4 8181 E513 F273 59D4 A013 8285 1093 A113 F273 59D4 8384 8085 A039 8285 A021 8284 F6B9 1082 FE45 7710 2F02 FE00 E800 8080
 *
 * Intent: Four-entry add-lane fan converging on one epilogue. Runs dark
 * SUB_059C then SUB_59DC (asm-only, forward extern; AR1-AR5/A/B all
 * rewritten after, outputs dead). AR1 = 0x2620, AR2 = 0x261E,
 * AR3 = 466, AR4 = 0x2621, AR5 = 0x2622. A = *AR1; ssbx st1,ovm
 * (hardware, no C form -- OVM = 1 for all dual adds below, flagged).
 * A == 0 chains to 59C1 (bc aeq). Else cell += 1 (addm); B = A - 4,
 * B < 0 chains to 59C6 (bc blt, full-40 signed, exact on small B);
 * B == 0 chains to 59CA; B = A - 7, B < 0 chains to 59D0.
 * Head lane (A >= 7): A = *AR5 + (*AR3+ << 16), *AR5 = A-high,
 * A = *AR4 + (*AR3 << 16), *AR4 = A-high (dual ADD syntax-6, oracle
 * op_dual_arithmetic: fixed-left-16, both words SXM-extended, OVM
 * saturation; SXM = 1 sign-extend assumed, flagged; saturation corners
 * need |Y| near 32768, values assumed small, flagged), then bcd
 * 0x59D4,ageq under WORD-count delay slots (ti-c54x delayed_branch
 * oracle: the 2-word st fills the window, so taken jumps to 59D4
 * with A = A_old while fallthrough executes ld #0,a + stl a,*ar4
 * at 59B9-59BA before rejoining; BCD pre-decode test, a7b7 precedent
 * corrected to the word rule): taken reaches the tail with A
 * reloaded; fall-through (A_old < 0) zeroes cell 0x2621, sets AR0 =
 * 0x2F02, rsbx ovm (hardware, no C form), and returns via retd with
 * delay *AR0 = 176.
 * 59C1 lane (A == 0): B = 1; bd 0x59D4 with delays *AR1 = B-low (1)
 * then *AR5 = *AR3 (mvdd, 4238 precedent), jump to tail.
 * 59C6 lane (A in 1..3): bd 0x59D4 with delays A = *AR3 + (*AR5 << 16)
 * then *AR5 = A-high, jump to tail.
 * 59CA lane (A == 4): A = *AR3+ (AR3 466->467); bd 0x59D4 with delays
 * B = *AR3 + (*AR5 << 16) then *AR4 = B-high; delay 2: *AR5 = A-low;
 * jump to tail.
 * 59D0 lane (A in 5..6): same two dual adds as the head lane
 * (AR3 466->467), falls to tail.
 * Tail 59D4 (all lanes except the BCD fall-through): rsbx ovm; A =
 * *AR2 (0x261E, never stepped); rcd aeq whose delay stm AR0 = 0x2F02
 * always runs, then A == 0 returns; else retd with delays A = 0 then
 * *AR0 = 0 (stl) and return. No params (all ARs set in-span); void
 * (A/B live-outs are the tail stores, consumed in memory; the BCD
 * fall-through returns nothing). AR3 ends 466/467 path-dependent, dead
 * after (noted). Bound 5993-59DB (retd + ld/stl delays, abuts SUB_59DC
 * at 59DC). Zero in-image callers (per header evidence).
 */
extern void sub_059C(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_59DC(void);

void frag_5993(void)
{
    long a;
    long b;
    int taken;
    int *ar0;
    int *ar1;
    int *ar2;
    int *ar3;
    int *ar4;
    int *ar5;

    sub_059C();                                            /* call 0x59c */
    sub_59DC();                                            /* call 0x59dc */
    ar1 = (int *)0x2620;                                  /* stm #9760,ar1 */
    ar2 = (int *)0x261E;                                  /* stm #9758,ar2 */
    ar3 = (int *)466;                                     /* stm #466,ar3 */
    ar4 = (int *)0x2621;                                  /* stm #9761,ar4 */
    ar5 = (int *)0x2622;                                  /* stm #9762,ar5 */
    a = (long)*ar1;                                       /* ld *ar1,a */
    /* ssbx st1,ovm (hardware, no C form) */
    if (a == 0)                                           /* bc 0x59c1,aeq */
        goto lane_59C1;
    *ar1 += 1;                                            /* addm #1,*ar1 */
    b = a - 4L;                                           /* sub #4,a,b */
    if (b < 0)                                            /* bc 0x59c6,blt */
        goto lane_59C6;
    if (b == 0)                                           /* bc 0x59ca,beq */
        goto lane_59CA;
    b = a - 7L;                                           /* sub #7,a,b */
    if (b < 0)                                            /* bc 0x59d0,blt */
        goto lane_59D0;
    a = (long)*ar5 + ((long)*ar3++ << 16);                /* add dual */
    *ar5 = (int)(((unsigned long)a >> 16) & 0xFFFF);      /* sth a,*ar5 */
    a = (long)*ar4 + ((long)*ar3 << 16);                  /* add dual */
    *ar4 = (int)(((unsigned long)a >> 16) & 0xFFFF);      /* sth a,*ar4 */
    taken = (a >= 0);                                     /* bcd pre-decode test */
    *ar1 = 4;                                             /* bcd delay (fills window) */
    if (!taken) {                                         /* bcd fallthrough */
        a = 0;                                            /* ld #0,a (fallthrough) */
        *ar4 = (int)(a & 0xFFFF);                         /* stl (cell 0x2621 = 0) */
        ar0 = (int *)0x2F02;                              /* stm #12034,ar0 */
        /* rsbx st1,ovm (hardware, no C form) */
        *ar0 = 176;                                       /* retd delay: st */
        return;                                           /* retd */
    }
    goto tail_59D4;                                       /* bcd 0x59d4 */
lane_59C1:                                                /* A == 0 lane */
    b = 1;                                                /* ld #1,b */
    *ar1 = (int)(b & 0xFFFF);                             /* bd delay: stl */
    *ar5 = *ar3;                                          /* bd delay: mvdd */
    goto tail_59D4;                                       /* bd 0x59d4 */
lane_59C6:                                                /* A in 1..3 */
    a = (long)*ar3 + ((long)*ar5 << 16);                  /* bd delay: add */
    *ar5 = (int)(((unsigned long)a >> 16) & 0xFFFF);      /* bd delay: sth */
    goto tail_59D4;                                       /* bd 0x59d4 */
lane_59CA:                                                /* A == 4 lane */
    a = (long)*ar3++;                                     /* ld *ar3+,a */
    b = (long)*ar3 + ((long)*ar5 << 16);                  /* bd delay: add */
    *ar4 = (int)(((unsigned long)b >> 16) & 0xFFFF);      /* bd delay: sth */
    *ar5 = (int)(a & 0xFFFF);                             /* bd delay: stl */
    goto tail_59D4;                                       /* bd 0x59d4 */
lane_59D0:                                                /* A in 5..6 */
    a = (long)*ar5 + ((long)*ar3++ << 16);                /* add dual */
    *ar5 = (int)(((unsigned long)a >> 16) & 0xFFFF);      /* sth a,*ar5 */
    a = (long)*ar4 + ((long)*ar3 << 16);                  /* add dual */
    *ar4 = (int)(((unsigned long)a >> 16) & 0xFFFF);      /* sth a,*ar4 */
    goto tail_59D4;
tail_59D4:                                                /* 59D4 epilogue */
    /* rsbx st1,ovm (hardware, no C form) */
    a = (long)*ar2;                                       /* ld *ar2,a */
    ar0 = (int *)0x2F02;                                  /* rcd delay: stm */
    if (a == 0)                                           /* rcd aeq */
        return;
    a = 0;                                                /* retd delay: ld */
    *ar0 = (int)(a & 0xFFFF);                             /* retd delay: stl */
    /* retd: return */
}
