/* ROM6 ORIGIN 0x516A (38w): ROUTINE_516A -- tune pre-filter.
 * Verified encoding: src/rom6/kernel/516a_routine_516a.asm (recombine MATCH).
 * ORIGIN 0x516A
 * EXPECT: F074 059C 60F8 2F1F 00A0 E900 FC20 7714 2627 61F8 2F5C FF00 F830 51D4 6FF8 2F60 0C58 F030 000F F110 000F F84D 51D4 F110 0008 F84D 51CC 61F8 054F 0400 F830 51CC F845 5190 1184 FE00 F330 0100
 *
 * Intent: Guard chain fanning into the 5190 lane cluster. Runs dark
 * SUB_059C (opaque, forward extern; A/B rewritten after, outputs dead).
 * B = 0 (ld #0,b); cell 0x2F1F != 160 returns B = 0 (cmpm sets TC iff
 * equal, a7b7 precedent; rc ntc is taken-return, oracle op_rc).
 * AR4 = 0x2627; (*0x2F5C & 0xFF00) != 0 jumps to the miss sink (bitf
 * mask test, TC = (cell & mask) != 0; bc tc, tail-called).
 * A = (*0x2F60)>>8 & 15 (LD-shifted load; low 4 exact under either SXM
 * extension, AND clears guard/high); B = A - 15 (sub #lk,src,dst),
 * B == 0 jumps to the miss sink. B = A - 8, B == 0 jumps to the hit
 * tail (tail-called). (*0x054F & 1024) != 0 jumps to the hit tail.
 * A == 0 chains to LANE_36F (bc aeq, tail-called). Else B = *AR4,
 * return-delayed with B &= 256 (and #256,b delay slot) then return.
 * B-out modeled as int return, matching the lane cluster convention.
 * A internal; AR4 set at head; AR1/AR2/AR3/AR5 untouched; no params.
 * Bound 516A-518F (retd + and delay, abuts LANE_36F at 5190).
 * Entry call F074@4D70 (far forward call from 4D-worker zone).
 */
extern void sub_059C(void);
extern int lane_36F(int *par4);
extern int hit_51CC(int *par4);
extern int miss_sink_51D4(int *par4);

int routine_516A(void)
{
    long a;
    long b;
    int *ar4;

    sub_059C();                                            /* call 0x59c */
    b = 0;                                                /* ld #0,b */
    if (*(volatile int *)0x2F1F != 160)                   /* cmpm; rc ntc */
        return (int)b;
    ar4 = (int *)0x2627;                                  /* stm #9767,ar4 */
    if ((*(volatile int *)0x2F5C & 0xFF00) != 0)          /* bitf; bc tc */
        return miss_sink_51D4(ar4);
    a = (long)*(volatile int *)0x2F60 >> 8;               /* ld -8 */
    a &= 15L;                                             /* and #15,a */
    b = a - 15L;                                          /* sub #15,a,b */
    if (b == 0)                                           /* bc beq */
        return miss_sink_51D4(ar4);
    b = a - 8L;                                           /* sub #8,a,b */
    if (b == 0)                                           /* bc beq */
        return hit_51CC(ar4);
    if ((*(volatile int *)0x054F & 1024) != 0)            /* bitf; bc tc */
        return hit_51CC(ar4);
    if (a == 0)                                           /* bc 0x5190,aeq */
        return lane_36F(ar4);
    b = (long)*ar4;                                       /* ld *ar4,b */
    b &= 256L;                                            /* and (delay) */
    return (int)b;                                        /* retd */
}
