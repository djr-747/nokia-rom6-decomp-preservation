/* ROM6 ORIGIN 0x4BD7 (82w): FILL_2F5D_4BD7 -- staged fill with calld chain.
 * Verified encoding: src/rom6/kernel/4bd7_fill_2f5d_4bd7.asm (recombine MATCH).
 * EXPECT: F110 00C1 F84C 4C29 7711 0071 71F8 264C 0013 F274 5B18 7712 2F80 E802 F274 4DA7 7716 0003 F274 9281 7713 30F9 7712 2F80 771A 000B F272 4BF9 7713 09C8 1292 7182 0009 F47D 8093 68F8 09D3 01FF 10F8 09D9 7712 30FA 7713 09D4 F274 4F5F 7711 0004 68F8 09D8 3FFF 69F8 051D 0004 7712 2F5C 7692 0000 7713 09C8 EC0B E598 7712 2F68 7713 2F53 F274 7FDC 7711 000B F274 4F6E 7713 2F3C F274 4FC2 7317 2F69 F074 4ECE F073 4D9C
 *
 * Intent: B = A - 193; nonzero tail-enters FRAG_4C29 with A (bc bneq).
 * Else AR1 = 113; cell 0x13 = cell 0x264C (mvdk); calld ROUTINE_5B18
 * (delay stm #12160,ar2 runs first: par2 = (int *)12160, par3 = entry
 * AR3, ar1_live = 113). A = 2; calld dark 0x4DA7 (delay AR6 = 3);
 * calld dark 0x9281 (delay AR3 = 12537); AR2 = 12160; BRC = 11;
 * rptbd 0x4BF9 (delay stm #2504,ar3 runs once; RSA = PC+2 = 0x4BF5,
 * REA = 0x4BF9, block inclusive per the oracle sequencer end
 * comparator, 12 passes): A = unsigned *AR2++ (ldu); cell 0x9 = *AR2
 * (post-inc read); A arith>>= 3 (sfta, exact: ldu zeroes high);
 * *AR3++ = A-low (stl). cell 0x9D3 &= 511 (andm); A = cell 0x9D9;
 * AR2 = 12538; AR3 = 2516; calld dark 0x4F5F (delay AR1 = 4; forward
 * extern, revisit when the 4F5F span lands). AR1 = 4;
 * cell 0x9D8 &= 16383; cell 0x51D |= 4; AR2 = 12124; cell AR2 = 0
 * with post-inc (st); AR3 = 2504; rpt #11: 12x *AR2++ = *AR3++
 * (mvdd). AR2 = 12136; AR3 = 12115; calld dark 0x7FDC (delay
 * AR1 = 11); calld dark 0x4F6E (delay AR3 = 12092); delay
 * cell 0x2F69 = AR7-value (mvmd) then calld dark 0x4FC2. Dark call
 * 0x4ECE; tail-branch dark 0x4D9C (b). AR3-entry and AR7-value are
 * caller params (read-only); AR1/AR2/AR4/AR6 set in-span; A restored
 * by contract (A never clobbered on the fall path: sub writes B);
 * B internal; TC untouched. Bound 4BD7-4C28 (abuts 4C29).
 */
extern void frag_4C29(int a_live);
extern void routine_5B18(int *par2, int *par3, int ar1_live);
extern void frag_4DA7(void); /* joins 4da7_dispatch_4da7; see docs/evidence/extern-triage.md */
extern void sub_9281(void); /* joins 9281_sub_9281; see docs/evidence/extern-triage.md */
extern void frag_4F5F(void); /* joins 4f5f_rolror_banz_4f5f; see docs/evidence/extern-triage.md */
extern void frag_7FDC(void); /* joins 7fdc_routine_7fdc; see docs/evidence/extern-triage.md */
extern void frag_4F6E(void); /* joins 4f6e_sub_4f6e; see docs/evidence/extern-triage.md */
extern void frag_4FC2(void); /* joins 4fc2_sub_4fc2; see docs/evidence/extern-triage.md */
extern void sub_4ECE(void);
extern void frag_4D9C(void); /* joins 4cb4_frag_4cb4 interior @+0xE8; see docs/evidence/extern-triage.md */

void fill_2F5D_4BD7(long a_live_in, int *ar3_in, int ar7_in)
{
    long a = a_live_in;
    long b;
    int i;
    int *ar2;
    int *ar3;

    b = a - 193L;                                      /* sub #193,a,b */
    if (b != 0) {                                      /* bc 0x4c29,bneq */
        frag_4C29((int)a);                             /* tail */
        return;
    }
    /* AR1 = 113 (stm; consumed by the 5B18 call) */
    *(volatile int *)0x13 = *(volatile int *)0x264C;   /* mvdk */
    /* calld 0x5b18 (delay stm #12160,ar2 runs first) */
    routine_5B18((int *)12160, ar3_in, 113);
    a = 2L;                                            /* ld #2,a */
    /* calld 0x4da7 (delay stm #3,ar6 runs first; dark, flagged) */
    frag_4DA7();
    /* calld 0x9281 (delay stm #12537,ar3 runs first; dark, flagged) */
    sub_9281();
    ar2 = (int *)12160;                                /* stm #12160,ar2 */
    /* stm #11,brc; rptbd 0x4bf9 (delay stm #2504,ar3 runs once) */
    ar3 = (int *)2504;
    for (i = 0; i < 12; i++) {                         /* [0x4bf5,0x4bf9] */
        a = (unsigned long)(unsigned)*ar2++;           /* ldu *ar2+,a */
        *(volatile int *)0x9 = *ar2;                   /* mvdk *ar2,0x9 */
        a >>= 3;                                       /* sfta a,-3 (exact) */
        *ar3++ = (int)(a & 0xFFFF);                    /* stl a,*ar3+ */
    }
    *(volatile int *)0x9D3 &= 511;                     /* andm #511 */
    a = (long)*(volatile int *)0x9D9;                  /* ld *(0x9d9),a */
    ar2 = (int *)12538;                                /* stm #12538,ar2 */
    ar3 = (int *)2516;                                 /* stm #2516,ar3 */
    /* calld 0x4f5f (delay stm #4,ar1 runs first; forward extern) */
    frag_4F5F();
    /* AR1 = 4 (stm) */
    *(volatile int *)0x9D8 &= 16383;                   /* andm #16383 */
    *(volatile int *)0x51D |= 4;                       /* orm #4 */
    ar2 = (int *)12124;                                /* stm #12124,ar2 */
    *ar2++ = 0;                                        /* st #0,*ar2+ */
    ar3 = (int *)2504;                                 /* stm #2504,ar3 */
    for (i = 0; i < 12; i++)                           /* rpt #11 */
        *ar2++ = *ar3++;                               /* mvdd *ar3+,*ar2+ */
    ar2 = (int *)12136;                                /* stm #12136,ar2 */
    ar3 = (int *)12115;                                /* stm #12115,ar3 */
    /* calld 0x7fdc (delay stm #11,ar1 runs first; dark, flagged) */
    frag_7FDC();
    /* calld 0x4f6e (delay stm #12092,ar3 runs first; forward extern) */
    frag_4F6E();
    *(volatile int *)0x2F69 = ar7_in;                  /* mvmd ar7,0x2f69 */
    /* (calld 0x4fc2 delay above runs first; forward extern) */
    frag_4FC2();
    sub_4ECE();                                        /* call 0x4ece */
    frag_4D9C();                                       /* b 0x4d9c tail */
}
