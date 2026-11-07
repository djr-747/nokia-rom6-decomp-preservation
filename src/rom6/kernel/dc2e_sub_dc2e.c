/* ROM6 0xDC2E SUB_DC2E -- 19w.
 * Verified encoding: src/rom6/kernel/dc2e_sub_dc2e.asm (recombine MATCH).
 * ORIGIN 0xDC2E
 * EXPECT: 771A 009F 7713 0008 E900 F272 DC38 7712 0013 A20A F1A0 10F8 0C4C F030 FFFD FF4D F040 0002 FE00
 *
 * Intent: Dual-subtract OR-reduce. BRC = 159, AR3 = 8 (dead, noted),
 * B = 0; the rptbd delay slot AR2 = 19 runs once; 160 passes of
 * A = ((*AR2 - *AR4++) << 16) with SXM sign-extension (SUB dual MOD0
 * = X - Y fixed-left-16 per ti-c54x op_dual_arithmetic; OVM
 * saturation needs unbound OVM state, values assumed small, flagged),
 * B |= A each pass (block [RSA = PC + 4 = 0xDC37, REA = 0xDC38] per
 * the vendored TI note; RPTBD execution stays deferred, flagged).
 * Then A = cell0xC4C with low bits &= 0xFFFD (AND imm16 zero-extends:
 * upper cleared, per ti-c54x op_logical_immediate); B == 0 sets bit 1
 * (xc 2,beq covers the 2-word OR only, exact); retd with delays in
 * the DC41 span (9B6F pattern, flagged). AR2/AR4 dead at return
 * (flagged). Bound DC2E-DC40.
 */
void sub_DC2E(int *ar4)
{
    int *ar2;
    long a;
    long b;
    int i;
    /* stm #159,brc; stm #8,ar3 (dead, noted); ld #0,b */
    b = 0;
    ar2 = (int *)19;                                 /* rptbd delay: stm (once) */
    for (i = 0; i < 160; i++) {                      /* rptbd 0xdc38 */
        a = ((long)*ar2 - (long)*ar4++) << 16;       /* sub *ar2,*ar4+,a */
        b |= a;                                      /* or a,b */
    }
    a = (long)*(volatile int *)0xC4C;                /* ld *(0xc4c),a */
    a &= 0xFFFDL;                                    /* and #-3,a (imm16 zero-ext) */
    if (b == 0)                                      /* xc 2,beq (taken runs or) */
        a |= 2;                                      /* or #2,a */
    /* retd (delays in DC41 span, always run there) */
    (void)a;                                         /* A/B dead at retd (flagged) */
    (void)b;
}
