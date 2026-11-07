/* ROM6 0x3623 FRAG_3623 (staged copy) -- 29w.
 * Verified encoding: src/rom6/kernel/3623_frag_3623.asm (recombine MATCH).
 * ORIGIN 0x3623
 * EXPECT: 71D2 0015 71D2 0010 13D2 8914 F200 0001 F0FF F010 0001 881A 7713 2F00 F072 3634 12D2 8093 6DC2 F074 2E2F 4914 4815 F274 93CE 7712 2F00 F073 2E64
 *
 * Intent: Staged copy with classify tail. Cells 0x15 and
 * 0x10 each take *(AR2) with AR2 += AR0 per cell (mvdk +0%
 * source per the 351d convention: read pre-step address,
 * step by AR0; circular wrap needs caller-live BK, linear
 * modeled flagged; if entry AR2 runs bit-reversed
                    
 * (361C's note on this span) the steps are brev-advances,
 * unmodelable linearly -- flagged); B = unsigned *(AR2),
 * AR2 += AR0 (ldu); AR4 = B-low (stlm, int local); A =
 * B + 1 (add lk); A logical>>= 1 (sftl, exact: A < 2^17);
 * A -= 1 (sub lk); BRC = A-low (stlm; -1 when B = 0 gives
 * an empty loop, natural). AR3 = 12032; BRC+1 passes
 * (rptb 0x3634: body ldu + stl, REA 0x3634) of A =
 * unsigned *(AR2) with AR2 += AR0 then cell AR3 = A-low
 * with AR3 post-incremented; then AR2 -= AR0 once
 * (mar *ar2-% after the loop, not in it). Then runs
 * 0x2E2F (extern); B = AR4-value, A = zero-extended
 * AR5-value (ldm pair; AR5 is caller-live); the calld
 * delay slot AR2 = 12032 runs BEFORE the call to 0x93CE
 * (dark classifier, extern void per the 2D5E convention;
 * the A/B/AR2 setup feeds it opaquely, flagged); after
 * it returns, tail-branches to frag_2E64 (extern). ARs,
 * A, B dead at exit (flagged). Bound 3623-363F.
 * Name: frag_361C already declares the opaque
 * frag_3623(void) away-jump (its entry carries no AR
 * values to thread), so this full intent lives under
 * frag_3623_stage to avoid a signature collision.
 */
extern void dispatcher_entry_2E2F(void);
extern void frag_93CE(void); /* joins 93ce_msg_classify_by_caller; see docs/evidence/extern-triage.md */
extern void frag_2E64(void); /* joins 2e64_dispatch_match_loop; see docs/evidence/extern-triage.md */

void frag_3623_stage(int ar0_live, int *ar2_in, int ar5_live)
{
    int *ar2 = ar2_in;
    int *ar3;
    int ar4v;
    long a;
    long b;
    int brc;
    int i;
    *(volatile int *)0x15 = *ar2;                    /* mvdk *ar2+%,imm */
    ar2 += ar0_live;                                 /* +0% (wrap flagged) */
    *(volatile int *)0x10 = *ar2;                    /* mvdk *ar2+%,imm */
    ar2 += ar0_live;
    b = (unsigned long)(unsigned)*ar2;               /* ldu *ar2+%,b */
    ar2 += ar0_live;
    ar4v = (int)(b & 0xFFFF);                        /* stlm b,ar4 */
    a = b + 1;                                       /* add #1,b,a */
    a = (unsigned long)a >> 1;                       /* sftl a,-1 (logical) */
    a -= 1;                                          /* sub #1,a */
    brc = (int)(a & 0xFFFF);                         /* stlm a,brc */
    ar3 = (int *)12032;                              /* stm #12032,ar3 */
    for (i = 0; i < brc + 1; i++) {                  /* rptb 0x3634 */
        a = (unsigned long)(unsigned)*ar2;           /* ldu *ar2+%,a */
        ar2 += ar0_live;                             /* +0% (wrap flagged) */
        *ar3++ = (int)(a & 0xFFFF);                  /* stl a,*ar3+ */
    }
    ar2 -= ar0_live;                                 /* mar *ar2-% */
    dispatcher_entry_2E2F();                                      /* call 0x2e2f */
    b = (long)ar4v;                                  /* ldm ar4,b */
    a = (long)(unsigned)ar5_live;                    /* ldm ar5,a (zero-ext) */
    ar2 = (int *)12032;                              /* calld delay (runs first) */
    frag_93CE();                                     /* calld 0x93ce */
    frag_2E64();                                      /* b 0x2e64 (tail) */
}
