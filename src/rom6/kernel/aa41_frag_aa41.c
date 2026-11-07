/* ROM6 0xAA41 FRAG_AA41 -- 21w.
 * Verified encoding: src/rom6/kernel/aa41_frag_aa41.asm (recombine MATCH).
 * ORIGIN 0xAA41
 * EXPECT: F074 0688 61F8 263A 0200 FC30 10F8 0B67 FC44 61F8 051C 0003 FC30 F074 CFBD E800 F274 D0BE 80F8 0ECC FC00
 *
 * Intent: Triple-gated call chain. Runs dark SUB_0688; bit0x263A.9
 * set near-returns (bitf + rc tc, 32b4 precedent); cell0xB67 nonzero
 * near-returns (rc aneq); bits 0x51C.0-1 set near-returns (bitf +
 * rc tc); else runs dark SUB_CFBD, A = 0, stores 0 to cell0xECC
 * (calld delay slot, runs before the callee per the 80fc precedent),
 * runs dark SUB_D0BE, returns. Callee heads set DP/BK first (no
 * entry reads), so void externs are exact. Bound AA41-AA55.
 */
extern void sub_0688(void);
extern void sub_CFBD(void);
extern void sub_D0BE(void);

void frag_AA41(void)
{
    int tc;
    long a;
    sub_0688();                                      /* call 0x688 (dark) */
    tc = (*(volatile int *)0x263A & 512) != 0;       /* bitf *(0x263a),#512 */
    if (tc)                                          /* rc tc */
        return;
    a = (long)*(volatile int *)0xB67;                /* ld *(0xb67),a */
    if (a != 0)                                      /* rc aneq */
        return;
    tc = (*(volatile int *)0x51C & 3) != 0;          /* bitf *(0x51c),#3 */
    if (tc)                                          /* rc tc */
        return;
    sub_CFBD();                                      /* call 0xcfbd (dark) */
    /* ld #0,a folded: calld delay stores 0 */
    *(volatile int *)0xECC = 0;                      /* calld delay: stl a,*(0xecc) */
    sub_D0BE();                                      /* calld 0xd0be (dark) */
    /* ret */
}
