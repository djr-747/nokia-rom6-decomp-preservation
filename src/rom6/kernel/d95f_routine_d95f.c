/* ROM6 0xD95F ROUTINE_D95F -- 17w.
 * Verified encoding: src/rom6/kernel/d95f_routine_d95f.asm (recombine MATCH).
 * ORIGIN 0xD95F
 * EXPECT: E900 F272 D965 7713 FC58 A289 F1A0 10F8 0B68 F030 FFFD FF4D F040 0002 FE00 80F8 0B68
 *
 * Intent: OR-reduce with masked writeback. B = 0; the rptbd delay
 * slot AR3 = 0xFC58 runs once; BRC + 1 passes (BRC caller-live) of
 * A = ((*AR3++ - *AR2++) << 16) with SXM sign-extension (SUB dual
 * MOD0 = X - Y fixed-left-16 per ti-c54x op_dual_arithmetic; OVM
 * saturation needs unbound OVM state, values assumed small, flagged),
 * B |= A each pass (block [RSA = PC + 4 = 0xD964, REA = 0xD965] per
 * the vendored TI note; RPTBD execution stays deferred, flagged).
 * Then A = cell0xB68 with low bits &= 0xFFFD (AND imm16
 * zero-extends: upper cleared, per ti-c54x op_logical_immediate);
 * B == 0 sets bit 1 (xc 2,beq covers the 2-word OR only, exact);
 * the retd delay stores A-low to the cell (always runs); return.
 * Bound D95F-D96F.
 */
void routine_D95F(int *ar2, int brc_live)
{
    int *ar3;
    long a;
    long b;
    int i;
    b = 0;                                           /* ld #0,b */
    ar3 = (int *)0xFC58;                             /* rptbd delay: stm #-936,ar3 */
    for (i = 0; i < brc_live + 1; i++) {              /* rptbd 0xd965 */
        a = ((long)*ar2++ - (long)*ar3++) << 16;     /* sub *ar2+,*ar3+,a (dual X-Y order per header rule; wave-13: was Y-X, corrected) */
        b |= a;                                      /* or a,b */
    }
    a = (long)*(volatile int *)0xB68;                /* ld *(0xb68),a */
    a &= 0xFFFDL;                                    /* and #-3,a (imm16 zero-ext) */
    if (b == 0)                                      /* xc 2,beq (taken runs or) */
        a |= 2;                                      /* or #2,a */
    *(volatile int *)0xB68 = (int)(a & 0xFFFF);      /* retd delay: stl (always runs) */
    /* retd */
}
