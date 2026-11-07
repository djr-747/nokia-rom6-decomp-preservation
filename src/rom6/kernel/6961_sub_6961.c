/* ROM6 0x6961 SUB_6961 -- 18w.
 * Verified encoding: src/rom6/kernel/6961_sub_6961.asm (recombine MATCH).
 * ORIGIN 0x6961
 * EXPECT: 890E F074 6973 4480 F48C F600 8813 6FF8 000E 0E20 F000 0006 F495 F495 FD46 E900 4813 FC00
 *
 * Intent: Modulo plus accumulate. T = B-low (B live-in); runs the 0x6973 modulo loop (C: sub_6973, A-result dead, AR1/AR2 live-ins); A = *AR0 << 16 (AR0 live-in); B = T times A-high (MPYA dst overwrites B per ti-c54x op_mpya_dst); A += B; AR3 = A; A = B minus cell 0xE (sub, dst = src minus operand per ti-c54x op_sub); A += 6; A > 0 clears B (xc 1,agt skips nothing... clears via ld #0,b, exact); A = AR3; returns A with B out-param (both accumulators live out). nop pair is pipeline padding.
 */
extern void sub_6973(int b_in, int *par1, int *par2);

int sub_6961(int b_in, int *par0, int *par1, int *par2, int *b_out)
{
    int t = b_in;                                /* stlm b,t */
    int a;
    int b;
    int ar3tmp;
    sub_6973(b_in, par1, par2);                  /* call 0x6973 */
    a = *par0 << 16;                             /* ld *ar0,16,a */
    b = t * (a >> 16);                           /* mpya a (B = T x A-hi) */
    a += b;                                      /* add b,a */
    ar3tmp = a;                                  /* stlm a,ar3 */
    a = b - *(volatile int *)0xE;            /* sub *(0xe),b,a */
    a += 6;                                      /* add #6,a; nop; nop */
    if (a > 0)                                   /* xc 1,agt */
        b = 0;                                   /* ld #0,b */
    *b_out = b;
    return ar3tmp;                               /* ldm ar3,a; ret */
}
