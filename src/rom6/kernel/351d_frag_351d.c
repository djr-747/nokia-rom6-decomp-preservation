/* ROM6 0x351D FRAG_351D -- 27w.
 * Verified encoding: src/rom6/kernel/351d_frag_351d.asm (recombine MATCH).
 * ORIGIN 0x351D
 * EXPECT: 4914 F200 0001 F47F F010 0001 F843 352A 7713 2F00 47F8 0008 E5C9 F074 2E2F 61F8 20FF 0600 7710 00F8 E81C FB20 93CE 7712 2F00 F073 2E64
 *
 * Intent: Copy-gated status fork. A = AR4-value + 1, halved
 * arithmetic then - 1 (ldm + ADD #lk + SFTA + SUB #lk, SXM = 1
 * assumed flagged); A >= 0 runs RC = *(0x8) + 1 dual moves
 * *(AR3++) = *AR2 with AR2 += AR0-live (rpt Smem + MVDD +0%,
 * 457f precedent; circular wrap needs caller-live BK, linear
 * flagged; bc 0x352a,alt skips exactly rpt + mvdd, exact), else
 * skips to the dark call; runs dark SUB_2E2F; TC = (cell0x20FF &
 * 1536) != 0 (bitf, 32b4 precedent); AR0 = 248; A = 28; the ccd
 * delay AR2 = 12032 always runs (2 words), TC clear calls dark
 * SUB_93CE (ccd grounded per ti-c54x op_ccd; entry state of 93CE
 * unbound, flagged); tail-branch dark 0x2E64. AR2/AR0 caller-live,
 * dead after (dark-call liveness flagged). Bound 351D-3537.
 */
extern void dispatcher_entry_2E2F(void);
extern void sub_93CE(void); /* joins 93ce_msg_classify_by_caller; see docs/evidence/extern-triage.md */
extern void frag_2E64(void); /* joins 2e64_dispatch_match_loop; see docs/evidence/extern-triage.md */

void frag_351D(int ar4_live, int *ar2_in, int ar0_live)
{
    int *ar2 = ar2_in;
    int *ar3;
    long a;
    int tc;
    int rc;
    int i;
    a = (long)ar4_live;                              /* ldm ar4,b */
    a += 1;                                          /* add #1,b,a */
    a = a >> 1;                                      /* sfta a,-1 */
    a -= 1;                                          /* sub #1,a */
    if (a >= 0) {                                    /* bc 0x352a,alt (skips rpt+mvdd) */
        ar3 = (int *)12032;                          /* stm #12032,ar3 */
        rc = *(volatile int *)0x8;                   /* rpt *(0x8) */
        for (i = 0; i < rc + 1; i++) {               /* mvdd *ar2+0%,*ar3+ */
            *ar3++ = *ar2;
            ar2 += ar0_live;                         /* +0% (wrap flagged) */
        }
    }
    dispatcher_entry_2E2F();                                      /* call 0x2e2f (dark) */
    tc = (*(volatile int *)0x20FF & 1536) != 0;      /* bitf *(0x20ff),#1536 */
    /* stm #248,ar0 (dead, noted) */
    a = 28;                                          /* ld #28,a (dead, flagged) */
    ar2 = (int *)12032;                              /* ccd delay: stm (always runs) */
    if (!tc)                                         /* ccd 0x93ce,ntc */
        sub_93CE();                                  /* (dark) */
    frag_2E64();                                     /* b 0x2e64 (dark tail) */
    (void)a;                                         /* A dead at tail (flagged) */
}
