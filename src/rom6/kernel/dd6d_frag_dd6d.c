/* ROM6 0xDD6D FRAG_DD6D -- 10w.
 * Verified encoding: src/rom6/kernel/dd6d_frag_dd6d.asm (recombine MATCH).
 * ORIGIN 0xDD6D
 * EXPECT: 4492 40F8 0EC7 F58C F300 0003 0182 FE00 F495 440B
 *
 * Intent: Multiply-add probe with delay-clobbered accumulators.
 * A = (*AR2++ << 16) - (cell0xEC7 << 16) (LD/SUB Smem,16: int->long
 * models the SXM = 1 sign-extension exactly, flagged); B = T x A-high
 * (MPYA dst overwrites B per ti-c54x op_mpya_dst and the 6961/dbd4
 * precedents; T caller-live); B += 3; B += sign-extended *AR2 (ADD
 * Xmem per op_add_xmem, flagged). The retd delays (nop; LD cell0x0B
 * into A, DP = 0 assumed per da40, flagged) run, then far return --
 * no store anywhere: A/B die at retd and the only observable effect
 * is the single AR2 step (flagged, matches ROM bytes exactly).
 * Bound DD6D-DD76.
 */
void frag_DD6D(int **ppar2, int t_live)
{
    long a;
    long b;
    a = (long)**ppar2 << 16;                         /* ld *ar2+,16,a */
    (*ppar2)++;
    a -= (long)*(volatile int *)0xEC7 << 16;         /* sub *(0xec7),16,a */
    b = (long)t_live * (a >> 16);                    /* mpya b (B = T x A-hi) */
    b += 3;                                          /* add #3,b */
    b += (long)**ppar2;                              /* add *ar2,b */
    a = (long)*(volatile int *)0x0B << 16;           /* retd delay: ld (always runs) */
    (void)a;                                         /* A/B dead at retd (flagged) */
    (void)b;
    /* retd */
}
