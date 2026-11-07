/* ROM6 ORIGIN 0x56FC (63w): SUB_56FC -- five-phase divide preset plus call.
 * Verified encoding: src/rom6/kernel/56fc_sub_56fc.asm (recombine MATCH).
 * ORIGIN 0x56FC
 * EXPECT: F074 059C 7711 247A 5681 FC45 7713 0912 5783 F600 7691 0000 7681 0000 F162 0029 F340 7000 F620 7712 2F00 FD43 F600 8293 808B 7714 0015 F274 4384 7684 001A 7711 0914 8091 5683 F274 4384 7684 0033 8091 8191 5683 F274 4384 7684 0066 8091 5683 F274 4384 7684 0068 8091 5683 F274 4384 7684 052E 8091 8181 F074 57FE FC00
 *
 * Intent: Five identical preset phases feeding DIV_CORE_4384, then
 * SUB_57FE and return. Runs dark SUB_059C (opaque, forward extern;
 * A/B rewritten after, outputs dead). AR1 = 9338 (0x247A); A = DLD
 * *AR1 (32-bit MSW-first pair, oracle op_dld_long32 compose; the
 * 0x5681/0x5783 mode-0 encodings compose no catalog row -- only the
 * MOD13 row exists -- so the form is gap-flagged: gas assembles MATCH,
 * MSW-first per the leaf, and the address walk below proves DLD steps
 * neither AR (AR1/AR3 re-read the same cells across phases)); A == 0
 * returns (rc aeq, taken-return, oracle op_rc; full-40 zero coincides
 * with long zero under either SXM extension). AR3 = 2322 (0x0912);
 * the dld *ar3,b lane is dead (B overwritten by ld #41,16,b two words
 * later; RAM read, no side effects; noted, not modeled per the 3199
 * dead-lane precedent). B = 41<<16 | 28672; A = D - B computed
 * overflow-free as: D >= B subtracts, else D stays (reassociated from
 * sub b,a / xc 1,alt / add b,a: the taken path re-adds B, netting D;
 * the direct sub overflows long only in the INT32_MIN window, so the
 * comparison form is used, noted).
 * SXM-sign assumed for the DLD compose (flagged: with SXM=0 the pair
 * is unsigned and the D<B test differs for high-bit-set pairs).
 * xc 1,alt tests full-40 signed A < 0 (oracle branch cond; exact on
 * long). A != D-B path stores the 32-bit A split: *AR3++ = high
 * (sth, high-half extract per 505B), *AR3-- = low (stl; net AR3
 * unchanged). AR4 = 21; calld DIV_CORE_4384 (asm-only, forward extern;
 * delay slot *AR4 = 26 runs first, then the call; AR4 never steps, so
 * all five phases share it). Then four more identical phases with
 * delay immediates 51/102/104/1326: each re-DLDs *AR3 (same cells --
 * AR3 net-zero across the split store), calld, *AR1++ = A-low. Final:
 * *AR1 = B-low (B = 41<<16 | 28672 throughout, never rewritten),
 * call SUB_57FE (linked C, void) and return (ret, no delay). A/B
 * live-outs are 57FE residue (dark); ARs dead at ret. No params: AR1/
 * AR2/AR3/AR4 all set in-span (AR2 = 0x2F00 set but never used --
 * dead lane, noted), A/B rewritten after the dark head call.
 * Bound 56FC-573A (ret FC00@573A; abuts next span at 573B).
 * Entry calls F074@5550/6841 (per header evidence).
 */
extern void sub_059C(void);
extern void div_core_4384(void);
extern void sub_57FE(void);

void sub_56FC(void)
{
    long a;
    long b;
    int *ar1;
    int *ar2;
    int *ar3;
    int *ar4;

    sub_059C();                                            /* call 0x59c */
    ar1 = (int *)0x247A;                                  /* stm #9338,ar1 */
    a = ((long)*ar1 << 16) | ((unsigned)*(ar1 + 1) & 0xFFFF); /* dld (flagged) */
    if (a == 0)                                           /* rc aeq */
        return;
    ar3 = (int *)0x0912;                                  /* stm #2322,ar3 */
    b = 41L << 16;                                        /* ld #41,16,b */
    b |= 28672L;                                          /* or #28672,b */
    if (a >= b)                                           /* sub+xc/add (see note) */
        a -= b;
    ar2 = (int *)0x2F00;                                  /* stm (dead lane) */
    (void)ar2;
    *ar3++ = (int)(((unsigned long)a >> 16) & 0xFFFF);    /* sth a,*ar3+ */
    *ar3-- = (int)(a & 0xFFFF);                           /* stl a,*ar3- */
    ar4 = (int *)21;                                      /* stm #21,ar4 */
    *ar4 = 26;                                            /* calld delay */
    div_core_4384();                                      /* calld 0x4384 */
    ar1 = (int *)0x0914;                                  /* stm #2324,ar1 */
    *ar1++ = (int)(a & 0xFFFF);                           /* stl a,*ar1+ */
    a = ((long)*ar3 << 16) | ((unsigned)*(ar3 + 1) & 0xFFFF); /* dld *ar3,a */
    *ar4 = 51;                                            /* calld delay */
    div_core_4384();                                      /* calld 0x4384 */
    *ar1++ = (int)(a & 0xFFFF);                           /* stl a,*ar1+ */
    *ar1++ = (int)(b & 0xFFFF);                           /* stl b,*ar1+ */
    a = ((long)*ar3 << 16) | ((unsigned)*(ar3 + 1) & 0xFFFF); /* dld *ar3,a */
    *ar4 = 102;                                           /* calld delay */
    div_core_4384();                                      /* calld 0x4384 */
    *ar1++ = (int)(a & 0xFFFF);                           /* stl a,*ar1+ */
    a = ((long)*ar3 << 16) | ((unsigned)*(ar3 + 1) & 0xFFFF); /* dld *ar3,a */
    *ar4 = 104;                                           /* calld delay */
    div_core_4384();                                      /* calld 0x4384 */
    *ar1++ = (int)(a & 0xFFFF);                           /* stl a,*ar1+ */
    a = ((long)*ar3 << 16) | ((unsigned)*(ar3 + 1) & 0xFFFF); /* dld *ar3,a */
    *ar4 = 1326;                                          /* calld delay */
    div_core_4384();                                      /* calld 0x4384 */
    *ar1++ = (int)(a & 0xFFFF);                           /* stl a,*ar1+ */
    *ar1 = (int)(b & 0xFFFF);                             /* stl b,*ar1 */
    sub_57FE();                                           /* call 0x57fe */
    /* ret */
}
