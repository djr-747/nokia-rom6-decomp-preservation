/* ROM6 0x45C2 FRAG_45C2 -- 56w.
 * Verified encoding: src/rom6/kernel/45c2_frag_45c2.asm (recombine MATCH).
 * ORIGIN 0x45C2
 * EXPECT: 7713 2F00 7693 3532 7693 0000 E734 7710 0001 771A 000B 7715 2F0E F072 45D2 E50B E5C9 F074 2E2F F074 8529 F274 8529 7714 2F08 12F8 2F07 1CF8 B779 13F8 2F0D 1DF8 B779 F2A0 7713 04FA 6883 FFFB FF45 6983 0004 76F8 2F07 0000 76F8 2F0D 0000 7713 2F00 7714 0074 F274 2C88 7715 0034 FC00
 *
 * Intent: Dual-copy stage with fold and chained call.
 * AR3 = 12032; cell AR3 = 13618 then 0 with AR3
 * post-incremented (st immediate pair); AR4 = AR3-value
 * (mvmm); AR0 = 1; BRC = 11; AR5 = 12046; 12 passes
 * (rptb 0x45d2) of cell AR5 = *(AR2) with AR5
 * post-incremented (mvdd *ar2,*ar5+: source fixed, no
 * step) then cell AR3 = *(AR2) with AR3 post-incremented
 * and AR2 += AR0 (mvdd *ar2+0%,*ar3+ per the 351d
 * convention: read pre-step address, step by AR0;
 * circular wrap needs caller-live BK, linear modeled
 * flagged). Runs 0x2E2F (extern), 0x8529 twice -- call
 * then calld, both with live AR1 (wrapper_8529 takes
 * int** pp1, the AR1 convention from its own header,
 * unverified; AR1 untouched in-span so entry value
 * threads) -- with the calld delay slot AR4 = 12040
 * running BEFORE the second call (grounded delayed-call
 * order). A = unsigned cell 0x2F07 XOR DROM cell 0xB779
 * (ldu then xor Smem, oracle op_xor_smem); B = unsigned
 * cell 0x2F0D XOR the same DROM cell; A |= B (or b,a).
 * AR3 = 1274; cell AR3 &= 0xFFFB (andm #-5); A == 0
 * skips cell |= 4 (xc 2,aeq covers the 2-word orm);
 * cells 0x2F07 and 0x2F0D = 0 (st); AR3 = 12032,
 * AR4 = 116; the calld delay slot AR5 = 52 runs BEFORE
 * routine_2C88 (dark, extern); return. AR2/AR5/AR4/AR3
 * step on locals; AR1 passthrough; A/B locals; all dead
 * at return (flagged). Bound 45C2-45F9.
 */
extern void dispatcher_entry_2E2F(void);
extern void wrapper_8529(int **pp1_in);
extern void routine_2C88(void); /* joins 2c88_ring_report_gate; see docs/evidence/extern-triage.md */

void frag_45C2(int *ar2_in, int *ar1_in)
{
    int *ar2 = ar2_in;
    int *ar1 = ar1_in;
    int *ar3;
    int *ar4;
    int *ar5;
    int ar0 = 1;                                     /* (stm #1,ar0) */
    long a;
    long b;
    int i;
    ar3 = (int *)12032;                              /* stm #12032,ar3 */
    *ar3++ = 13618;                                  /* st #13618,*ar3+ */
    *ar3++ = 0;                                      /* st #0,*ar3+ */
    ar4 = ar3;                                       /* mvmm ar3,ar4 */
    /* stm #11,brc */
    ar5 = (int *)12046;                              /* stm #12046,ar5 */
    for (i = 0; i < 12; i++) {                       /* rptb 0x45d2 */
        *ar5++ = *ar2;                               /* mvdd *ar2,*ar5+ */
        *ar3++ = *ar2;                               /* mvdd *ar2+0%,*ar3+ */
        ar2 += ar0;                                  /* +0% (wrap flagged) */
    }
    (void)ar0;
    dispatcher_entry_2E2F();                                      /* call 0x2e2f */
    wrapper_8529(&ar1);                              /* call 0x8529 */
    ar4 = (int *)12040;                              /* calld delay (runs first) */
    wrapper_8529(&ar1);                              /* calld 0x8529 */
    a = (unsigned long)(unsigned)*(volatile int *)0x2F07;  /* ldu */
    a ^= (long)*(volatile int *)0xB779;              /* xor *(0xb779),a */
    b = (unsigned long)(unsigned)*(volatile int *)0x2F0D;  /* ldu */
    b ^= (long)*(volatile int *)0xB779;              /* xor *(0xb779),b */
    a |= b;                                          /* or b,a */
    ar3 = (int *)1274;                               /* stm #1274,ar3 */
    *ar3 &= 65531;                                   /* andm #-5,*ar3 */
    if (a == 0)                                      /* xc 2,aeq */
        *ar3 |= 4;                                   /* orm #4,*ar3 */
    *(volatile int *)0x2F07 = 0;                     /* st #0 */
    *(volatile int *)0x2F0D = 0;                     /* st #0 */
    ar3 = (int *)12032;                              /* stm #12032,ar3 */
    ar4 = (int *)116;                                /* stm #116,ar4 */
    ar5 = (int *)52;                                 /* calld delay (runs first) */
    routine_2C88();                                  /* calld 0x2c88 */
    /* ret */
}
