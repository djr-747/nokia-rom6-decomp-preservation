/* ROM6 0x3691 FRAG_3691 -- 16w sieve-gated trampoline, one EXPECT.
 * Verified encoding: src/rom6/kernel/3691_frag_3691.asm (recombine MATCH).
 * ORIGIN 0x3691
 * EXPECT: 1282 60F8 0008 0009 F820 36A1 11F8 250F F074 580B F930 84CF F074 2E2F F073 2E64
 *
 * Intent: MMIO-gated sieve call into the dispatch loop. A = *(AR2)
 * unsigned (ldu *ar2,a, no post-inc: AR2 preserved); TC = (*(0x8) == 9)
 * (cmpm; TC-only per op_cmpm_smem_lk); mismatch exits to FRAG_36A1
 * (bc 0x36a1,ntc). B = id cell 0x250F (ld); runs SIEVE_580B(B) (call
 * 0x580b, C: sieve_580B per its header); TC from the cmpm is read by the
 * conditional call (cc 0x84cf,tc, C: sub_84CF_init) -- threaded through
 * dark SIEVE_580B by the callee-preservation convention (538d precedent,
 * trace-confirmable HYPOTHESIS); match runs SUB_84CF_INIT.
 * Then runs DISPATCHER_ENTRY_2E2F (call 0x2e2f); tail-enters
 * DISPATCH_MATCH_LOOP (b 0x2e64, bare extern per 361C: live state rides
 * unmodeled). Bound 3691-36A0.
 */
extern void frag_36A1(void);
extern void sieve_580B(int b_live);
extern void sub_84CF_init(void);
extern void dispatcher_entry_2E2F(void);
extern void dispatch_match_loop(void);

void frag_3691(int *par2)
{
    long a = (unsigned long)(unsigned)*par2;   /* ldu *ar2,a */
    long b;
    int tc = (*(volatile int *)0x8 == 9);      /* cmpm */

    if (!tc) {                                 /* bc 0x36a1,ntc */
        frag_36A1();
        return;
    }
    b = (long)*(volatile int *)0x250F;         /* ld *(0x250f),b */
    sieve_580B((int)b);                        /* call 0x580b */
    /* TC threads through the call (convention, flagged above) */
    if (tc)                                    /* cc 0x84cf,tc */
        sub_84CF_init();
    dispatcher_entry_2E2F();                    /* call 0x2e2f */
    dispatch_match_loop();                      /* b 0x2e64 */
}
