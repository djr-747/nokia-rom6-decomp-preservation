/* ROM6 0x87D3 ROUTINE_87D3 -- 22w.
 * Verified encoding: src/rom6/kernel/87d3_routine_87d3.asm (recombine MATCH).
 * ORIGIN 0x87D3
 * EXPECT: F074 0590 7713 11DA E808 EC0F 0093 F47C F540 F58E F84D 87E2 E916 F367 FFFF F47B F495 FD4B E900 F784 890E FE00
 *
 * Intent: Accumulate-normalize lane. CALL 0x590 (RAM-resident mini-kernel,
 * zeros in-mask, forward extern); AR3 = 4570; A = 8; rpt #15 accumulate
 * loop x16 (A += *AR3++); A >>= 4; B = A; B = exp(B) (exponent op,
 * oracle-unbound per 87e9 precedent, value flagged); if B == 0 join 87e2;
 * B = 22; B += -1*T (mac #-1,b, T dark, flagged); A >>= 5; if B >= 0
 * B = 0 (xc 1,blt skips the clear); B = -B; T = B-low; retd (delay slots
 * live in the abutting 87E9 span per its header). A/B/AR3/T live-out
 * (dark, flagged).
 */
extern void sub_0590(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void routine_87D3(void)
{
    long a;
    long b;
    int *ar3;
    int t;  /* T live-in (dark, flagged) */
    int i;

    sub_0590();                                                /* call 0x590 (RAM: zero in mask dump) */
    ar3 = (int *)4570;                                         /* stm #4570,ar3 */
    a = 8;                                                     /* ld #8,a */
    for (i = 0; i < 16; i++)                                   /* rpt #15 */
        a += (long)*ar3++ << 16;                               /* add *ar3+,a (ADD Smem: dst_old + Smem<<16 per op_add_smem) */
    a >>= 4;                                                   /* sfta a,-4 */
    b = a;                                                     /* ld a,b */
    /* exp b (exponent op; oracle-unbound per 87e9 precedent, value flagged) */
    if (b == 0)                                                /* bc 0x87e2,beq (flagged: B from exp) */
        goto l87e2;
    b = 22;                                                    /* ld #22,b */
    b += -1L * (long)t;                                        /* mac #-1,b (T dark, flagged) */
l87e2:
    a >>= 5;                                                   /* sfta a,-5 */
    /* nop */
    if (b >= 0)                                                /* xc 1,blt (skips when B<0) */
        b = 0;                                                 /* ld #0,b */
    b = -b;                                                    /* neg b */
    t = (int)(b & 0xFFFFL);                                    /* stlm b,t */
    (void)a; (void)ar3;
    /* retd (delay slots in abutting 87E9 span) */
}
