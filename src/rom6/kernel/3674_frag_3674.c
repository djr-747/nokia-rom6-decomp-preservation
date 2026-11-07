/* ROM6 0x3674 FRAG_3674 -- 15w register-count bitrev copy, one EXPECT.
 * Verified encoding: src/rom6/kernel/3674_frag_3674.asm (recombine MATCH).
 * ORIGIN 0x3674
 * EXPECT: 4914 F310 0003 F3FF 10D2 8813 7710 0001 47F8 000B E5C9 F074 2E2F F073 2E64
 *
 * Intent: Register-counted bit-reversed window copy into the dispatch
 * loop. Post-RET head (thin: AR4 = count seed, AR2 = source, DP live-in).
 * B = AR4 (ldm); B -= 3 (sub); B >>= 1 logical (sftl per op_logical:
 * SFTL is logical shift; B-shape dead after -- status side-effects noted,
 * value unused). A = *(AR2) unsigned (ld *ar2+%,a: bit-reversed
 * post-increment unmodelable, AR2 position unknown after -- noted);
 * AR3 = A-low (stlm); AR0 = 1. RPT *(0xB) loads RC = *(DP+0x0B)
 * (DP live-in assumed 0, flagged; RC = Smem per op_rpt_smem) for
 * RC + 1 iterations (RPT counts k + 1, 4EBC precedent): *AR3++ =
 * *(AR2-bitrev++) (mvdd *ar2+0%,*ar3+: source advance unmodelable,
 * dest plain). Then runs DISPATCHER_ENTRY_2E2F (call 0x2e2f);
 * tail-enters DISPATCH_MATCH_LOOP (b 0x2e64, bare extern per 361C).
 * Bound 3674-3682.
 */
extern void dispatcher_entry_2E2F(void);
extern void dispatch_match_loop(void);

void frag_3674(int *par2, int ar4_live)
{
    long b = (long)ar4_live;                 /* ldm ar4,b */
    long a;
    int ar3;
    int *par3;
    int n;
    int k;

    b -= 3;                                  /* sub #3,b */
    b >>= 1;                                 /* sftl b,-1 (B dead) */
    a = (unsigned long)(unsigned)*par2;      /* ld *ar2+%,a (brev+) */
    ar3 = (int)(a & 0xFFFF);                 /* stlm a,ar3 */
    /* stm #1,ar0 (by-AR0 step for the mvdd source; brev, unmodelable) */
    par3 = (int *)ar3;
    n = *(volatile int *)0x0B;               /* rpt *(0xb) (DP = 0?) */
    for (k = 0; k <= n; k++)                 /* RC = Smem: N = Smem + 1 */
        *par3++ = *par2;         /* mvdd (source brev-advance unmod.) */
    /* AR2/AR3 live-out unknown (bitrev); B dead; status noted */
    dispatcher_entry_2E2F();                    /* call 0x2e2f */
    dispatch_match_loop();                      /* b 0x2e64 */
}
