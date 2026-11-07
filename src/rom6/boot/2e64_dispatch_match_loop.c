/* ROM6 0x2E64 DISPATCH_MATCH_LOOP -- 32w.
 * Verified encoding: src/rom6/boot/2e64_dispatch_match_loop.asm (recombine MATCH).
 * ORIGIN 0x2E64
 * EXPECT: F074 05A0 61F8 054D 0004 F820 2E8F F074 942E FC45 8914 F030 00FF F050 00F4 FC44 6D8C 1282 F1F8 F350 0005 F84D 2E84 F1F8 F350 0000 FC4C F030 00FF 80F8 054D FC00
 *
 * Intent: Match-loop filter with early returns. Runs 0x5A0 (dark, forward extern); cell 0x54D bit 2 clear jumps away to 0x2E8F (bc ntc, C-bound frag_2E8F: hot entry, 275x trace). A = sub_942E() (dark callee, A live-out as int return); A == 0 returns (rc aeq). AR4 = B-live-in then AR4-- (stlm plus mar, AR4 modeled in-out); A = *AR2 unsigned (AR2 live-in); B = A >> 8 logical (sftl -8 per logical barrel semantics) XOR 5, zero tail-enters WORKER_2E84 (bc 0x2e84,beq: C-bound; head trace-cold). Recomputes B, XOR 0 is a no-op pad (assembles F350 0000, kept for honesty); B != 0 returns (rc bneq). Else A &= 255, stores to cell 0x54D, return. Bound 2E64-2E83.
 */
extern void sub_05A0(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void frag_2E8F(void);
extern int sub_942E(void); /* joins 942e_cobba_verify_loop; see docs/evidence/extern-triage.md */
extern void worker_2E84(void);

void dispatch_match_loop(int b_live, int *par2, int **ppar4)
{
    int a;
    int b;
    int *ar4;
    sub_05A0();                                  /* call 0x5a0 */
    if ((*(volatile int *)0x54D & 4) == 0) {     /* bitf, bc ntc */
        frag_2E8F();                             /* away, dark */
        return;
    }
    a = sub_942E();                                /* call 0x942e (A live-out) */
    if (a == 0)                                  /* rc aeq */
        return;
    ar4 = (int *)b_live;                        /* stlm b,ar4 */
    b = b_live;
    a &= 255;                                    /* and #255,a */
    a ^= 244;                                    /* xor #244,a */
    if (a != 0)                                  /* rc aneq */
        return;
    ar4--;                                       /* mar *ar4- */
    a = (unsigned)*par2;                        /* ldu *ar2,a */
    b = (a >> 8) & 0xFF;                         /* sftl a,-8,b (logical) */
    b ^= 5;                                      /* xor #5,b */
    if (b == 0) {                                /* bc 0x2e84,beq */
        *ppar4 = ar4;
        worker_2E84();                           /* tail, unbound C */
        return;
    }
    b = (a >> 8) & 0xFF;                         /* sftl a,-8,b */
    b ^= 0;                                      /* xor #0,b (no-op pad) */
    if (b != 0) {                                /* rc bneq */
        *ppar4 = ar4;
        return;
    }
    a &= 255;                                    /* and #255,a */
    *(volatile int *)0x54D = a;              /* stl a,*(0x54d) */
    *ppar4 = ar4;
    /* ret */
}
