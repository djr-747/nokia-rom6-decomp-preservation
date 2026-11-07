/* ROM6 0x3538 COND_COPY_3538 -- 31w.
 * Verified encoding: src/rom6/kernel/3538_cond_copy_3538.asm (recombine MATCH).
 * ORIGIN 0x3538
 * EXPECT: 4914 F200 0001 F47F F010 0001 F843 3545 7713 2F00 47F8 0008 E5C9 F074 2E2F 61F8 20FF 0200 FB30 93CE 7712 2F00 F073 2E64 E745 F074 8413 F074 2E2F F073 2E64
 *
 * Intent: Sign-routed copy into lane 12032 then dispatcher tail. A = *AR4 + 1, halved arithmetic
 * then - 1 (ld + ADD #lk + SFTA + SUB #lk, 351D precedent); A >= 0 runs the rpt copy lane
 * (stm #12032,ar3; rpt *(0x8); mvdd *AR2+0%,*AR3+ with AR2 += AR0-live, 351D precedent; circular
 * wrap needs caller-live BK, linear flagged; count+1 words); join -- dispatcher_entry_2E2F(); TC =
 * cell 0x20FF & 512 (bitf, #512 vs 351D #1536); ccd delay stm #12032,ar2 runs first; TC taken runs dark 0x93CE (forward
 * extern); b-tail frag_2E64() (operand in-span). Words 3550-3556 (mvmm/call 0x8413/call 0x2E2F/b) sit past
 * the unconditional b -- dead, not modeled (5886 precedent).
 */
extern void dispatcher_entry_2E2F(void);
extern void sub_93CE(void); /* joins 93ce_msg_classify_by_caller; see docs/evidence/extern-triage.md */
extern void frag_2E64(void); /* joins 2e64_dispatch_match_loop; see docs/evidence/extern-triage.md */

void frag_3538(int *par4, int *par2, int ar0_live)
{
    long a;
    int *ar2;
    int *ar3;
    int taken;
    int n;
    int i;


    a = (long)*par4;                                       /* ld *ar4,b */
    a += 1;                                                /* add #1,b,a (351D precedent) */
    a = a >> 1;                                            /* sfta a,-1 (arithmetic) */
    a = a - 1;                                             /* sub #1,a */
    if (a >= 0) {                                          /* bc 0x3545,alt (A<0 taken) */
        ar3 = (int *)12032;                                /* stm #12032,ar3 */
        n = *(volatile int *)0x8;                          /* rpt *(0x8) */
        ar2 = par2;
        for (i = 0; i <= n; i++) {                         /* mvdd *ar2+0%,*ar3+ */
            *ar3++ = *ar2;
            ar2 += ar0_live;                               /* +0% (wrap flagged) */
        }
    }
    dispatcher_entry_2E2F();                               /* call 0x2e2f */
    taken = (*(volatile int *)0x20FF & 512) != 0;          /* bitf *(0x20ff),#512 */
    ar2 = (int *)12032;                                    /* calld delay: stm (runs first) */
    if (taken)                                             /* ccd 0x93ce,tc */
        sub_93CE();
    frag_2E64();                                           /* b 0x2e64 (tail) */
    /* dead 3550-3556 (past unconditional b, not modeled) */
    (void)a;                                               /* A dead at tail (flagged) */
}
