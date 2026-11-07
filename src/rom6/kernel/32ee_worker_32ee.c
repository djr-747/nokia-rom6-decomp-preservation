/* ROM6 0x32EE WORKER_32EE -- 24w.
 * Verified encoding: src/rom6/kernel/32ee_worker_32ee.asm (recombine MATCH).
 * ORIGIN 0x32EE
 * EXPECT: 771A 0001 F272 32F8 7714 2625 12DA F1F8 F0E8 F1A0 8194 61D2 FFFF 7713 051D 6883 FFBF FF30 6983 0040 F074 2E2F F073 2E64
 *
 * Intent: Byte-fold with flag set. AR4 = 9765 (rptbd delay, once);
 * 2 passes of A = unsigned *AR2 (ldu, 3691 precedent; upper zero)
 * with AR2 += AR0-live (circular +0%, wrap needs caller-live BK,
 * linear flagged), B = A>>8 logical (sftl per 381b; A >= 0 exact),
 * A <<= 8, A |= B, *(AR4++) = B-low (block [RSA = PC + 4 = 0x32F4,
 * REA = 0x32F8]; RPTBD execution stays deferred, flagged). TC =
 * (*AR2 != 0) with AR2 += AR0 (bitf mask -1 = all bits);
 * cell0x51D &= -65 (16-bit cell, exact); TC set sets bit 6
 * (xc 2,tc covers the 2-word orm only, exact; 688C-class audit);
 * dark call 0x2E2F always runs; tail-branch dark 0x2E64. AR2
 * caller-live (value), dead after (dark-call liveness flagged).
 * Bound 32EE-3305.
 */
extern void dispatcher_entry_2E2F(void);
extern void frag_2E64(void); /* joins 2e64_dispatch_match_loop; see docs/evidence/extern-triage.md */

void worker_32EE(int *ar2_in, int ar0_live)
{
    int *ar2 = ar2_in;
    int *ar4;
    int *ar3;
    long a;
    long b;
    int tc;
    int i;
    /* stm #1,brc */
    ar4 = (int *)9765;                               /* rptbd delay: stm (once) */
    for (i = 0; i < 2; i++) {                        /* rptbd 0x32f8 */
        a = (unsigned long)(unsigned)*ar2;           /* ldu *ar2+0%,a */
        ar2 += ar0_live;                             /* +0% (wrap flagged) */
        b = (unsigned long)a >> 8;                   /* sftl a,-8,b (A>=0 exact) */
        a <<= 8;                                     /* sftl a,8 */
        a |= b;                                      /* or a,b */
        *ar4++ = (int)(b & 0xFFFF);                  /* stl b,*ar4+ */
    }
    tc = (*ar2 != 0);                                /* bitf *ar2+%,#-1 */
    ar2 += ar0_live;
    ar3 = (int *)1309;                               /* stm #1309,ar3 */
    *ar3 &= -65;                                     /* andm #-65,*ar3 */
    if (tc)                                          /* xc 2,tc (covers orm only) */
        *ar3 |= 64;                                  /* orm #64,*ar3 */
    dispatcher_entry_2E2F();                                      /* call 0x2e2f (dark, always runs) */
    frag_2E64();                                     /* b 0x2e64 (dark tail) */
}
