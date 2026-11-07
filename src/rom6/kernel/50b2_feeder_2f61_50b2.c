/* ROM6 ORIGIN 0x50B2 (184w): FEEDER_2F61_50B2 -- tune-cell feeder with
 * 2x9 pass compare-fold over the 0x2F21 lane.
 * Verified encoding: src/rom6/kernel/50b2_feeder_2f61_50b2.asm (recombine MATCH).
 * EXPECT: F074 059C 10F8 250F F030 00F0 F010 0010 E901 F844 515E 60F8 250F 001A F830 515E 10F8 264E F130 0010 F84D 50DA 720B 250C F768 7714 2F21 F062 005A 8184 F074 4348 F479 80F8 2623 80F8 2624 76F8 2662 0000 60F8 2F1F 0060 E901 F820 515E 61F8 264E 0004 F830 5106 7714 2623 7713 2F5C 1183 F230 FF00 F845 5100 1084 F010 0004 8094 E900 F846 515E 718C 2623 7712 008C F274 2D5E 7713 086D E900 F073 515E 1094 F000 0001 118C F487 8084 7715 2F61 1085 F578 F310 002B F84D 515E F540 F330 0003 F310 0003 7714 2662 7713 264E 6183 0004 F830 5125 FD4C 8084 1184 F330 0003 F310 0001 6983 0040 FF4C 6883 FFBF 10F8 051D F030 0040 6184 0003 E901 F845 515E F830 515E 6FF8 2F61 0C58 F010 0021 F845 5141 F010 0001 F845 5141 F010 0002 F844 515E 7715 0001 7714 2625 7713 0000 771A 0008 F272 5159 7712 2F61 4492 4184 1A82 F038 FFFF FD4D 6D93 F478 0A84 F495 F495 FD45 6D93 6D94 6C8D 5147 4913 61F8 264E 0030 F820 5167 68F8 264E FFCF E901 FE00 7313 2F0A
 *
 * Intent: guard chain, divisor setup, mode dispatch, repeat-fold, epilogue.
 * Runs dark SUB_059C (opaque, forward extern; A/B rewritten after, so its
 * outputs are dead). A = *0x250F & 240 - 16; nonzero exits (bc aneq).
 * CMPM *0x250F,#26 equal exits (bc tc: TC = (cell == lk), a7b7 precedent).
 * B = A & 16 (AND B-destination, oracle op_logical_immediate destination
 * field; guard cleared since the immediate zero-extends); B == 0 chains to
 * the 50DA tune check, else: BL = *0x250C low byte (mvdm to byte MMR, high
 * byte kept, 0 at this site), B <<= 8 (sfta b,8), AR4 = 0x2F21,
 * A = 90<<16, *0x2F21 = B-low (stl), A = DIV_STEP_4348(A, *AR4) (linked C,
 * int div_step(int a, int divisor); A fits int), A >>= 7 (sfta a,-7),
 * *0x2623 = *0x2624 = A-low, *0x2662 = 0 (st #lk), rejoin 50DA.
 * 50DA: CMPM *0x2F1F,#96 not-equal exits; BITF *0x264E,#4 (TC =
 * (cell & mask) != 0) set chains to 5106. Else AR4 = 0x2623, AR3 = 0x2F5C,
 * B = *AR3, A = B & 0xFF00; A == 0 chains to 5100, else A = *AR4 - 4 stored
 * post-inc, B = 0 (bc agt never taken: dead lane, modeled as written),
 * *0x2623 = *AR4 post-dec (mvdk Smem->dmad, 2a5f precedent), AR2 = 140,
 * calld SUB_2D5E (linked C; delay slot AR3 = 0x086D runs first, then the
 * call with (AR2, AR3) = (140, 0x086D) per the 56a2 (int *) cast
 * precedent), B = 0, exit. 5100: *0x2623 = min(*0x2623 + 1, *0x2624)
 * (min a: signed full-40 select, oracle op_compare; values 16-bit so the
 * 32-bit select is exact), rejoin 5106. 5106: AR5 = 0x2F61, A = *AR5,
 * B = A >> 8 arith (sfta a,-8,b) - 43; zero exits. B = A, B &= 3, B -= 3,
 * AR4 = 0x2662, AR3 = 0x264E; BITF *AR3,#4 set skips the stl lane to the
 * andm. Else B != 0 stores A-low to *0x2662 (xc 1,bneq taken-runs).
 * B = *0x2662, B &= 3, B -= 1, *AR3 |= 64 (orm); B != 0 clears bits 6-7
 * (*AR3 &= 0xFFBF, xc 2,bneq taken-runs over the 2-word andm); either way
 * A = *0x051D. A &= 64; B = 1; A == 0 exits; BITF *AR4,#3 set exits.
 * A = (*0x2F61) >> 8 arith (3-word LD-shift; shift-outcome exact: the
 * 33/32/30 dispatch compares agree under either SXM extension for every
 * v, and A is reloaded per fold pass so the dispatch residue is dead);
 * A - 33/32/30 dispatch: 33 or 32 chains to 5141, 30 falls to 5141,
 * else exit. 5141: AR5 = 1, AR4 = 0x2625, AR3 = 0;
 * BRC = 8, rptbd block 514B-5159 (Z=1 delayed form has no oracle leaf,
 * flagged; RSA = first word after the 2-word op): 9 passes per arming.
 * Per pass: AR2 = 0x2F21 (stm inside block), A = (*AR2++)<<16,
 * B = A - (*AR4<<16) (SUB shifted, SXM-sign assumed flagged; mod-2^32 wrap
 * keeps the beq test exact, B value flagged), A |= *AR2 (0x2F22, no step),
 * A &= 0xFFFF00 (and #-1,8: mask imm<<8 zero-extended, clears bit 31:24
 * and guard, so A is nonnegative after), B == 0 steps AR3 (xc 1,beq),
 * A >>= 8 arith (sfta a,-8), A -= (unsigned)*AR4 (subs zero-extends Smem;
 * bounds [-8454143, 16777215] fit long, no OVM), A == 0 steps AR3
 * (xc 1,aeq over the REA mar; an XC skip still closes the iteration per
 * the repeat_block sequencer). After 9 passes AR4++ (mar outside block);
 * banz *ar5- tests-then-decrements (taken = nonzero, always decrements,
 * 3199 precedent): taken re-runs stm #8,brc + rptbd re-arm, so exactly 2
 * block runs (18 passes); fall-through reaches ldm. B = AR3 (ldm MMR,
 * 2d5e precedent), BITF *0x264E,#48 clear exits with B = AR3 live-out,
 * else cell &= ~49 (andm #-49 = 0xFFCF), B = 1, retd with delay
 * *0x2F0A = AR3 (mvmd) then return; second delay word is 516A (abut).
 * AR3 entry is dark (caller 4D6C asm-only): explicit ar3_in param, stored
 * to *0x2F0A on early exits. 40-bit exactness: AND/OR masks zero-extend
 * to full 40 (oracle op_logical_immediate), so guard bits clear at every
 * AND and the beq/aeq/anec tests are low-32 exact; accumulator high bytes
 * above bit 31 are dropped, flagged. BRC MMR folded into the pass count
 * (unobservable after). TC written by BITF/CMPM reads only.
 * Bound 50B2-5169 (retd + mvmd delay, abuts 516A). Caller 4D6C (call).
 */
extern void sub_059C(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern int div_step(int a, int divisor);
extern void sub_2D5E(int *par2, int *par3);

void feeder_2F61_50B2(int *ar3_in)
{
    long a;
    long b;
    int *ar2;
    int *ar3 = ar3_in;
    int *ar4;
    int *ar5;
    int pass;

    sub_059C();                                            /* call 0x59c */
    a = (long)*(volatile int *)0x250F;                    /* ld *(0x250f),a */
    a &= 240L;                                            /* and #240,a */
    a -= 16L;                                             /* sub #16,a */
    b = 1;                                                /* ld #1,b */
    if (a != 0)                                           /* bc 0x515e,aneq */
        goto epilogue_515E;
    if (*(volatile int *)0x250F == 26)                     /* cmpm; bc tc */
        goto epilogue_515E;
    a = (long)*(volatile int *)0x264E;                    /* ld *(0x264e),a */
    b = a & 16L;                                          /* and #16,a,b */
    if (b == 0)                                           /* bc 0x50da,beq */
        goto check_50DA;
    b = (b & ~0xFFL) | (*(volatile int *)0x250C & 0xFF);  /* mvdm 0x250c,bl */
    b = b << 8;                                           /* sfta b,8 */
    ar4 = (int *)0x2F21;                                  /* stm #12065,ar4 */
    a = 90L << 16;                                        /* ld #90,16,a */
    *ar4 = (int)(b & 0xFFFF);                             /* stl b,*ar4 */
    a = (long)div_step((int)a, *ar4);                     /* call 0x4348 */
    a >>= 7;                                              /* sfta a,-7 */
    *(volatile int *)0x2623 = (int)(a & 0xFFFF);          /* stl a,0x2623 */
    *(volatile int *)0x2624 = (int)(a & 0xFFFF);          /* stl a,0x2624 */
    *(volatile int *)0x2662 = 0;                          /* st #0,0x2662 */
check_50DA:                                               /* 50DA cmpm */
    if (*(volatile int *)0x2F1F != 96)                    /* cmpm; bc ntc */
        goto epilogue_515E;
    if ((*(volatile int *)0x264E & 4) != 0)               /* bitf; bc tc */
        goto lane_5106;
    ar4 = (int *)0x2623;                                  /* stm #9763,ar4 */
    ar3 = (int *)0x2F5C;                                  /* stm #12124,ar3 */
    b = (long)*ar3;                                       /* ld *ar3,b */
    a = b & 0xFF00L;                                      /* and #-256,b,a */
    if (a == 0)                                           /* bc 0x5100,aeq */
        goto min_5100;
    a = (long)*ar4;                                       /* ld *ar4,a */
    a -= 4L;                                              /* sub #4,a */
    *ar4++ = (int)(a & 0xFFFF);                           /* stl a,*ar4+ */
    b = 0;                                                /* ld #0,b */
    if (b > 0)                                            /* bc agt (dead) */
        goto epilogue_515E;
    *(volatile int *)0x2623 = *ar4;                       /* mvdk *ar4-,dmad */
    ar4--;
    ar2 = (int *)140;                                     /* stm #140,ar2 */
    ar3 = (int *)0x086D;                                  /* calld delay slot */
    sub_2D5E(ar2, ar3);                                   /* calld 0x2d5e */
    b = 0;                                                /* ld #0,b */
    goto epilogue_515E;                                   /* b 0x515e */
min_5100:                                                 /* 5100 min lane */
    a = (long)*ar4++;                                     /* ld *ar4+,a */
    a += 1L;                                              /* add #1,a */
    b = (long)*ar4--;                                     /* ld *ar4-,b */
    if (b < a)                                            /* min a */
        a = b;
    *ar4 = (int)(a & 0xFFFF);                             /* stl a,*ar4 */
lane_5106:                                                /* 5106 mode lane */
    ar5 = (int *)0x2F61;                                  /* stm #12129,ar5 */
    a = (long)*ar5;                                       /* ld *ar5,a */
    b = a >> 8;                                           /* sfta a,-8,b */
    b -= 43L;                                             /* sub #43,b */
    if (b == 0)                                           /* bc 0x515e,beq */
        goto epilogue_515E;
    b = a;                                                /* ld a,b */
    b &= 3L;                                              /* and #3,b */
    b -= 3L;                                              /* sub #3,b */
    ar4 = (int *)0x2662;                                  /* stm #9826,ar4 */
    ar3 = (int *)0x264E;                                  /* stm #9806,ar3 */
    if ((*ar3 & 4) != 0) {                                /* bitf; bc tc */
        *ar3 &= 0xFFBF;                                   /* andm #-65 */
        goto mode_5127;
    }
    if (b != 0)                                           /* xc 1,bneq */
        *ar4 = (int)(a & 0xFFFF);                         /* stl a,*ar4 */
    b = (long)*ar4;                                       /* ld *ar4,b */
    b &= 3L;                                              /* and #3,b */
    b -= 1L;                                              /* sub #1,b */
    *ar3 |= 64;                                           /* orm #64,*ar3 */
    if (b != 0)                                           /* xc 2,bneq */
        *ar3 &= 0xFFBF;                                   /* andm #-65 */
mode_5127:                                                /* 5127 ld */
    a = (long)*(volatile int *)0x051D;                   /* ld *(0x51d),a */
    a &= 64L;                                             /* and #64,a */
    b = 1;                                                /* ld #1,b */
    if (a == 0)                                           /* bc 0x515e,aeq */
        goto epilogue_515E;
    if ((*ar4 & 3) != 0)                                  /* bitf; bc tc */
        goto epilogue_515E;
    a = (long)*(volatile int *)0x2F61 >> 8;               /* ld -8 (exact) */
    a -= 33L;                                             /* sub #33,a */
    if (a == 0)                                           /* bc 0x5141,aeq */
        goto fold_5141;
    a -= 1L;                                              /* sub #1,a */
    if (a == 0)                                           /* bc 0x5141,aeq */
        goto fold_5141;
    a -= 2L;                                              /* sub #2,a */
    if (a != 0)                                           /* bc 0x515e,aneq */
        goto epilogue_515E;
fold_5141:                                                /* 5141 fold */
    ar5 = (int *)1;                                       /* stm #1,ar5 */
    ar4 = (int *)0x2625;                                  /* stm #9765,ar4 */
    ar3 = (int *)0;                                       /* stm #0,ar3 */
    for (;;) {                                            /* banz outer x2 */
        for (pass = 0; pass < 9; pass++) {                /* rptbd BRC=8 */
            ar2 = (int *)0x2F21;                          /* RSA 514B */
            a = (long)*ar2++ << 16;                       /* ld *ar2+,16,a */
            b = (long)((unsigned long)a -                 /* sub shifted */
                ((unsigned long)(long)*ar4 << 16));
            a |= (long)*ar2;                              /* or *ar2,a */
            a &= 0xFFFF00L;                               /* and #-1,8,a */
            if (b == 0)                                   /* xc 1,beq */
                ar3++;                                    /* mar *ar3+ */
            a >>= 8;                                      /* sfta a,-8 */
            a -= (long)(unsigned int)*ar4;                /* subs *ar4,a */
            if (a == 0)                                   /* xc 1,aeq */
                ar3++;                                    /* mar (REA) */
        }
        ar4++;                                            /* mar *ar4+ */
        {                                                 /* banz */
            int taken = (ar5 != (int *)0);
            ar5--;
            if (!taken)
                break;
        }
    }
    b = (int)(long)ar3;                                   /* ldm ar3,b */
epilogue_515E:                                            /* 515E bitf */
    if ((*(volatile int *)0x264E & 0x30) == 0)            /* bitf; bc ntc */
        goto retd_5167;
    *(volatile int *)0x264E &= 0xFFCF;                    /* andm #-49 */
    b = 1;                                                /* ld #1,b */
retd_5167:                                                /* retd */
    *(volatile int *)0x2F0A = (int)(long)ar3;             /* mvmd (delay) */
    return;
}
