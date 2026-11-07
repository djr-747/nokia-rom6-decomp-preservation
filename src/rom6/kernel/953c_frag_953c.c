/* ROM6 0x953C FRAG_953C -- 35w port-sweep dispatcher.
 * Verified encoding: src/rom6/kernel/953c_frag_953c.asm (recombine MATCH).
 * ORIGIN 0x953C
 * EXPECT: F074 05D8 7719 00FA E800 74F8 0008 0035 8813 F120 0200 F495 75F8 000B 0001 EC14 F495 7712 021E 7482 0036 6182 0600 10F8 20FC F110 0006 F84D 955F F844 956E F830 9667 F073 95A2
 *
 * Intent: RF port-sweep preset plus 4-way gate dispatch.
 * Call 0x5D8 (low-region RAM: zero in mask dump);
 * BK = 250; A = 0; cell 0x08 = PORT53 (PORTR, memory-only
 * -- A untouched per the F2 precedent); AR3 = AL (= 0);
 * B = 512; NOP; PORT1 = cell 0x0B; 21x NOP settle delay
 * (rpt #20); AR2 = 542; cell 542 = PORT54; TC = bit
 * 10-11 of cell 542 (BITF mask 1536, any-bit); A = cell
 * 0x20FC; B = A - 6 (SUB #lk,src,dst). Gates in order:
 * B == 0 -> the 955F sub-fragment (C entry frag_955F
 * with TC/A/AR3(=0)/AR2-dark -- branch transfer, modeled
 * terminal); else A != 0 -> the 956E span (asm-owned, no
 * C entry -- provisional join extern, transfer); else
 * TC -> the 9667 span (C entry frag_9667 with A/AR2-dark/B
 * -- transfer); else tail-branch to the 95A2 span
 * (asm-owned head, C file Pool -- provisional join
 * extern, transfer). Interior call 05D8; joins
 * 955F/956E/9667 per asm header. In AR2 (dark); out ports.
 * (Wave-13: EXPECT from the image; PORTR memory-only;
 * TC carried from BITF through ld/sub, neither of which
 * writes TC.)
 */
extern void sub_05D8(void); /* low-region: zero in mask dump (verified); see docs/evidence/extern-triage.md */
extern void frag_955F(int tc_live, long a_live, int ar3_live, int *ar2);
extern void frag_9667(long a_live, int *ar2, long b_live);
extern void frag_956E(void); /* C entry exists (counter gate lane) */
extern void frag_95A2(void); /* joins 95A2 span (asm-owned head), no C entry yet */

void frag_953C(void)
{
    long a;
    long b;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;
    int tc;
    int i;

    sub_05D8();                                                /* call 0x5d8 (RAM) */
    /* stm #250,bk (BK = 250) */
    a = 0;                                                     /* ld #0,a */
    *(volatile int *)0x08 = 0; /* portr 53,*(0x8) (memory-only; value extern-op, flagged) */
    ar3 = (int)(a & 0xFFFFL);                                  /* stlm a,ar3 (= 0) */
    b = 512;                                                   /* ld #512,b */
    /* nop */
    /* portw *(0xb),1 (PORT1 = cell 0x0B; value extern-op, flagged) */
    for (i = 0; i < 21; i++)                                   /* rpt #20 */
        ;                                                      /* nop (settle delay) */
    ar2 = (int *)542;                                          /* stm #542,ar2 */
    *ar2 = 0; /* portr 54,*ar2 (memory-only; value extern-op, flagged) */
    tc = ((*ar2 & 1536) != 0);                                 /* bitf *ar2,#1536 */
    a = (long)*(volatile int *)0x20FC;                         /* ld *(0x20fc),a */
    b = a - 6;                                                 /* sub #6,a,b */
    if (b == 0) {                                              /* bc 0x955f,beq */
        frag_955F(tc, a, (int)ar3, ar2);                       /* (branch transfer, not a call) */
        return;
    }
    if (a != 0) {                                              /* bc 0x956e,aneq */
        frag_956E();                                           /* (branch transfer, not a call) */
        return;
    }
    if (tc) {                                                  /* bc 0x9667,tc */
        frag_9667(a, ar2, b);                                  /* (branch transfer, not a call) */
        return;
    }
    frag_95A2();                                               /* b 0x95a2 (tail transfer, not a call) */
    /* (transfer, no return) */
}
