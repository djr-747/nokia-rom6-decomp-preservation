/* ROM6 ORIGIN 0x4CB4 (233w): FRAG_4CB4 -- mode compare with 807F/4EE0 tail.
 * Verified encoding: src/rom6/kernel/4cb4_frag_4cb4.asm (recombine MATCH).
 * EXPECT: F074 0670 E9F0 19F8 2F1F F310 00B0 F84C 4CEB 60F8 2510 00D3 F830 4CD8 E9F0 19F8 2510 F210 00D0 F845 4CE4 60F8 2510 00B0 F830 4CD8 60F8 2F1F 00B1 F820 4CD8 F074 5BF1 E80A F073 4CFE 7711 0071 71F8 264C 0013 F274 5B18 7712 2F80 E802 F073 4CFE F274 5AAC 7712 2F80 E806 F073 4CFE 7711 0071 60F8 250F 0022 F820 4CF7 71F8 352D 0013 F073 4CF9 7713 02C2 F274 5B18 7712 2F80 E800 F274 4DA7 7716 0003 F274 924C 7713 3147 ED14 F274 4D9D 771A 000E 688A 000F 6A8A FFFF 6A8A FFFF 6A8A FF00 F274 3A26 7712 2F80 F274 3A81 7712 2F80 E901 FD44 E900 81F8 2F20 61F8 3EB5 0200 F820 4D43 61F8 0586 0002 F820 4D43 60F8 261F 0000 F830 4D31 F84C 4D9C 60F8 261F 0002 69F8 0586 0004 F820 4D3C 69F8 0586 0001 76F8 261F 0000 7715 2627 6885 FDFF 10F8 2F1F F110 0070 F84D 4D55 F110 0080 F84D 4D55 F110 00B1 F84D 4D55 F110 00B0 F84C 4D68 F274 807F 7713 2F80 76F8 2F7F 0000 7712 2F8E 7713 2F59 F274 7FDC 7711 000E F274 4F6E 7713 2F3C F274 4EE0 771A 000B F074 50B2 F84D 4D9C F074 516A F84C 4D9C 7715 0021 4BF8 2F1F 7713 2F5B F274 2C88 7714 0080 E800 8A08 F110 00B1 F84C 4D89 76F8 2EF5 0001 F073 4D9C F010 00B0 F844 4D9C 76F8 2F1D 0001 F074 4ECE 61F8 051C 0003 F820 4D9C 7712 3090 E900 EC4B 8192 FC00
 *
 * Intent: dark call 0x670; B = (240 & cell 0x2F1F) - 176; nonzero takes
 * the in-span marker lane (bc 0x4ceb,bneq; A = entry A, dead, never read
 * before A is rebuilt). Else cell 0x2510 == 211 (cmpm) takes the AR1/5B18
 * lane; else A = (240 & cell 0x2510) - 208, zero takes the 5AAC lane;
 * else cell != 176 or cell 0x2F1F == 177 takes the AR1/5B18 lane; else
 * (marker 211-miss, nonzero adjust, 176-miss, 177-hit) runs HUB_5BF1
 * with A = 10. Lanes join at the marker test (AR1 = 113 on the in-span
 * paths): marker != 34 takes the AR3 = 706 arm, else cell 0x13 =
 * cell 0x352D and AR3 stays entry-live; ROUTINE_5B18 runs with
 * (par2 = 12160, par3 = that AR3, ar1 = 113). A = 0; dark calld 0x4DA7
 * (delay AR6 = 3, dead); dark calld 0x924C with par3 = 12615;
 * ASM = -12; SUB_4D9D(14, -12); AR2 walks down from 12160:
 * cell &= 15, cell ^= 0xFFFF twice, cell ^= 0xFF00 (andm/xorm with
 * post-dec; XORM grounded via the atomic-logical leaf). PA60 writer
 * calld 0x3A26 (a = 0 assumed preserved through the dark calls per the
 * 92F4 convention, flagged); A = ROUTINE_3A81(0-assumed). B = 1, and
 * A != 0 zeroes it (xc 1,aneq over ld #0,b, exact); cell 0x2F20 =
 * B-low. Bit 9 of 0x3EB5 clear, or bit 1 of 0x586 clear, skips to the
 * 0x2F1F load (bc ntc pair). Else cell 0x261F == 0 takes the cmp-2 arm;
 * B != 0 (A == 0) returns via the 4D9C ret stub. cmp-2 arm: cell 0x586
 * |= 4 always, |= 1 when cell == 2, then cell 0x261F = 0 (the st runs
 * on both sub-paths: branch target and fall-through). 0x2F1F arm:
 * AR5 = 9767, cell &= -513, A = cell 0x2F1F; A in {112,128,177}
 * (beq chain) or A == 176 (fall-through) runs the 807F lane (dark
 * calld, cell 0x2F7F = 0, dark 7FDC/4F6E setups), other A values skip
 * to the 4EE0 lane. Both reach SUB_4EE0 (delay BRC = 11) and dark call
 * 0x50B2, then beq/bneq on B: B below is the dark-subtree exit, NOT
 * the compare-chain B (4EE0 provably reloads B in its bd delay per its
 * C, and the subtree returns via 4EF3's ret) -- unbound local with the
 * apparent B-preserved reading (A == 176 -> return) stated but not
 * asserted. B != 0 returns via the stub; else dark call 0x516A, same
 * unbound test. Dark-clobber-only tail: AR5 = 33, push cell 0x2F1F,
 * dark calld 0x2C88 (delay AR4 = 128, dead), A = popped cell
 * (zero-extended: ld #0,a clears AH/AG, popm al loads AL -- the ld is
 * the extension setup, and popm visibility to the next instruction is
 * the immediate-MMR evidence); saved != 177 stores cell 0x2EF5 = 1
 * and returns; saved == 177 falls to saved -= 176, nonzero returns,
 * else cell 0x2F1D = 1, dark call 0x4ECE, bit 3 of 0x51C clear
 * returns, else AR2 = 12432, B = 0, 76x zero fill, ret. The final ret
 * word 0x4D9C is owned here (233rd word per recombine); the 1-word
 * 4D9C stub carve-out is deferred to the overlap pass. All bc targets
 * except 0x4D9C are in-span joins. Entry A dead (rebuilt before any
 * read); AR3-entry caller param (read-only walk base); AR1/AR2/AR4/
 * AR5/AR6/ASM set in-span; TC recomputed per test.
 * Bound 4CB4-4D9B + shared ret 0x4D9C (abuts 4D9D).
 */
extern void sub_0670(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void hub_5BF1(void);
extern void routine_5B18(int *par2, int *par3, int ar1_live);
extern void routine_5AAC(int *par2);
extern void frag_4DA7(void); /* joins 4da7_dispatch_4da7; see docs/evidence/extern-triage.md */
extern void sub_924C(int *par3);
extern void sub_4D9D(int brc_live, int asm_live);
extern void pa60_57_writer_b(long a_0632_out, int *ar2_in);
extern int routine_3A81(int a_in);
extern void frag_807F(void); /* joins 807f_sub116_807f; see docs/evidence/extern-triage.md */
extern void frag_7FDC(void); /* joins 7fdc_routine_7fdc; see docs/evidence/extern-triage.md */
extern void frag_4F6E(void); /* joins 4f6e_sub_4f6e; see docs/evidence/extern-triage.md */
extern void sub_4EE0(int brc_live_in);
extern void frag_50B2(void); /* joins 50b2_feeder_2f61_50b2; see docs/evidence/extern-triage.md */
extern void frag_516A(void); /* joins 516a_routine_516a; see docs/evidence/extern-triage.md */
extern void frag_2C88(void); /* joins 2c88_ring_report_gate; see docs/evidence/extern-triage.md */
extern void sub_4ECE(void);
extern void frag_4D9C(void); /* joins 4cb4_frag_4cb4 interior @+0xE8; see docs/evidence/extern-triage.md */

void frag_4CB4(int *ar3_in)
{
    long a;
    long b;
    long b_dark;
    int tc;
    int i;
    int *ar2;
    int *ar3;
    int *ar5;
    int save;

    sub_0670();                                        /* call 0x670 (dark) */
    b = 240L & (long)*(volatile int *)0x2F1F;         /* ld/and */
    b -= 176L;                                         /* sub #176,b */
    if (b == 0) {                                      /* bc 0x4ceb,bneq */
        tc = (*(volatile int *)0x2510 == 211);          /* cmpm */
        if (!tc) {                                     /* bc 0x4cd8,tc */
            b = 240L & (long)*(volatile int *)0x2510;  /* ld/and */
            a = b - 208L;                              /* sub #208,b,a */
            if (a != 0) {                              /* bc 0x4ce4,aeq */
                tc = (*(volatile int *)0x2510 == 176); /* cmpm */
                if (!tc) {                             /* bc 0x4cd8,tc */
                    tc = (*(volatile int *)0x2F1F == 177); /* cmpm */
                    if (!tc) {                         /* bc 0x4cd8,ntc */
                        hub_5BF1();                    /* call 0x5bf1 */
                        a = 10L;                       /* ld #10,a */
                        goto marker;                   /* b 0x4cfe */
                    }
                }
            } else {
                /* 0x4ce4 lane */
                routine_5AAC((int *)12160);            /* calld (delay ar2) */
                a = 6L;                                /* ld #6,a */
                goto marker;                           /* b 0x4cfe */
            }
        }
        /* 0x4cd8 lane */
        /* AR1 = 113 (stm; consumed by the 5B18 call) */
        *(volatile int *)0x13 = *(volatile int *)0x264C; /* mvdk */
        /* calld 0x5b18 (delay stm #12160,ar2 runs first) */
        routine_5B18((int *)12160, ar3_in, 113);
        a = 2L;                                        /* ld #2,a */
        /* b 0x4cfe (fall into marker) */
    }
    /* 0x4ceb/0x4cfe marker join (A dead on the 4ceb path: rebuilt below) */
marker:
    /* AR1 = 113 (stm) */
    tc = (*(volatile int *)0x250F == 34);               /* cmpm */
    ar3 = ar3_in;
    if (!tc) {                                         /* bc 0x4cf7,ntc */
        ar3 = (int *)706;                              /* stm #706,ar3 */
    } else {
        *(volatile int *)0x13 = *(volatile int *)0x352D; /* mvdk */
    }
    /* 0x4cf9 join */
    /* calld 0x5b18 (delay stm #12160,ar2 runs first) */
    routine_5B18((int *)12160, ar3, 113);
    a = 0L;                                            /* ld #0,a */
    /* calld 0x4da7 (delay stm #3,ar6 runs first; dark, AR6 dead) */
    frag_4DA7();
    /* calld 0x924c (delay stm #12615,ar3 runs first) */
    sub_924C((int *)12615);
    /* ld #-12,asm; calld 0x4d9d (delay stm #14,brc runs first) */
    sub_4D9D(14, -12);
    ar2 = (int *)12160;
    *ar2-- &= 15;                                      /* andm #15,*ar2- */
    *ar2-- ^= 0xFFFF;                                  /* xorm */
    *ar2-- ^= 0xFFFF;                                  /* xorm */
    *ar2-- ^= 0xFF00;                                  /* xorm */
    /* calld 0x3a26 (delay stm #12160,ar2; a = 0 assumed, flagged) */
    pa60_57_writer_b(0L, (int *)12160);
    /* calld 0x3a81 (delay stm #12160,ar2; a-in = 0 assumed, flagged) */
    a = (long)routine_3A81(0);
    b = 1L;                                            /* ld #1,b */
    if (a != 0)                                        /* xc 1,aneq */
        b = 0L;                                        /* ld #0,b (slot) */
    *(volatile int *)0x2F20 = (int)(b & 0xFFFF);       /* stl b */
    tc = (*(volatile int *)0x3EB5 & 512) != 0;         /* bitf */
    if (tc) {                                          /* bc 0x4d43,ntc */
        tc = (*(volatile int *)0x586 & 2) != 0;        /* bitf */
        if (tc) {                                      /* bc 0x4d43,ntc */
            tc = (*(volatile int *)0x261F == 0);       /* cmpm */
            if (tc) {                                  /* bc 0x4d31,tc */
                /* 0x4d31 cmp-2 arm */
                tc = (*(volatile int *)0x261F == 2);   /* cmpm */
                *(volatile int *)0x586 |= 4;           /* orm #4 */
                if (!tc)                               /* bc 0x4d3c,ntc */
                    goto zero;
                *(volatile int *)0x586 |= 1;           /* orm #1 */
zero:
                /* 0x4d3c join */
                *(volatile int *)0x261F = 0;           /* st #0 */
            } else if (b != 0) {                       /* bc 0x4d9c,bneq */
                frag_4D9C();                           /* tail (ret stub) */
                return;
            }
        }
    }
    /* 0x4d43 0x2f1f arm */
    ar5 = (int *)9767;                                 /* stm #9767,ar5 */
    *ar5 &= -513;                                      /* andm #-513,*ar5 */
    a = (long)*(volatile int *)0x2F1F;                 /* ld *(0x2f1f),a */
    if (a == 112L || a == 128L || a == 177L || a == 176L) {
        /* 0x4d55 lane (beq chain + A == 176 fall-through) */
        /* calld 0x807f (delay stm #12160,ar3 runs first; dark) */
        frag_807F();
        *(volatile int *)0x2F7F = 0;                   /* st #0,*(0x2f7f) */
        ar2 = (int *)12174;                            /* stm #12174,ar2 */
        ar3 = (int *)12121;                            /* stm #12121,ar3 */
        /* calld 0x7fdc (delay stm #14,ar1 runs first; dark) */
        frag_7FDC();
        /* calld 0x4f6e (delay stm #12092,ar3 runs first; fwd) */
        frag_4F6E();
    }
    /* 0x4d68 join (direct: A outside {112,128,177,176}) */
    /* calld 0x4ee0 (delay stm #11,brc runs first) */
    sub_4EE0(11);
    frag_50B2();                                       /* call 0x50b2 (dark) */
    /* B here = dark-subtree exit (4EE0 reloads B per its C; unbound):
       apparent pre-call value A-176, i.e. A == 176 -> return. */
    if (b_dark == 0) {                                 /* bc 0x4d9c,beq */
        frag_4D9C();                                   /* tail (ret stub) */
        return;
    }
    frag_516A();                                       /* call 0x516a (dark) */
    if (b_dark != 0) {                                 /* bc 0x4d9c,bneq */
        frag_4D9C();                                   /* tail (ret stub) */
        return;
    }
    /* dark-clobber-only tail */
    ar5 = (int *)33;                                   /* stm #33,ar5 */
    save = *(volatile int *)0x2F1F;                    /* pshd *(0x2f1f) */
    ar3 = (int *)12123;                                /* stm #12123,ar3 */
    /* calld 0x2c88 (delay stm #128,ar4 runs first; dark, AR4 dead) */
    frag_2C88();
    a = 0L;                                            /* ld #0,a (AH/AG clear) */
    a = (long)(unsigned)save;                          /* popm al */
    b = a - 177L;                                      /* sub #177,a,b */
    if (b != 0) {                                      /* bc 0x4d89,bneq */
        /* 0x4d89 */
        a -= 176L;                                     /* sub #176,a */
        if (a != 0) {                                  /* bc 0x4d9c,aneq */
            frag_4D9C();                               /* tail (ret stub) */
            return;
        }
        *(volatile int *)0x2F1D = 1;                   /* st #1,*(0x2f1d) */
        sub_4ECE();                                    /* call 0x4ece */
        tc = (*(volatile int *)0x51C & 3) != 0;        /* bitf */
        if (!tc) {                                     /* bc 0x4d9c,ntc */
            frag_4D9C();                               /* tail (ret stub) */
            return;
        }
        ar2 = (int *)12432;                            /* stm #12432,ar2 */
        b = 0L;                                        /* ld #0,b */
        for (i = 0; i < 76; i++)                       /* rpt #75 */
            *ar2++ = (int)(b & 0xFFFF);                /* stl b,*ar2+ */
        /* ret (shared word 0x4d9c, owned here) */
        return;
    }
    *(volatile int *)0x2EF5 = 1;                       /* st #1,*(0x2ef5) */
    frag_4D9C();                                       /* b 0x4d9c tail */
}
