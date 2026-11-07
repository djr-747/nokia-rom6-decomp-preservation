/* ROM6 0x69A9 SUB_69A9 -- 21w.
 * Verified encoding: src/rom6/kernel/69a9_sub_69a9.asm (recombine MATCH).
 * ORIGIN 0x69A9
 * EXPECT: F074 0598 E807 1881 61F8 2627 0100 F110 0003 FF30 F844 69B9 FA4F 69BB E900 F495 E908 F520 FE00 81F8 0564
 *
 * Intent: Compare-gated store with delayed branch. Runs dark
 * SUB_0598; A = 7 & *AR1; TC = (cell0x2627 & 256) != 0; B = A - 3
 * (SUB #lk,src,dst: B = A - lk per 381b). TC clear skips the bc+bcd
 * pair (xc 2,tc: taken executes, per ti-c54x op_xc) and rejoins at
 * the ld#8 (the skipped-over ld#0/nop are effect-free, exact).
 * TC set: A != 0 jumps into the span at ld#8 (bc aneq; in-span
 * rejoin, goto per the 83b4 precedent); A == 0 runs the bcd delays
 * (B = 0, nop) then always branches to retd (bleq with B = 0) whose
 * delay stores 0 to cell0x564. At ld#8: B = 8, B -= A (SUB src,dst:
 * dst minus src), cell0x564 = B-low (retd delay, always runs),
 * return. Callers land on 0x69A9 with AR1 live (and *ar1 read
 * first). Bound 69A9-69BD.
 */
extern void sub_0598(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void sub_69A9(int *ar1)
{
    long a;
    long b;
    int tc;
    sub_0598();                                      /* call 0x598 (dark) */
    a = 7 & (long)*ar1;                              /* ld #7,a; and *ar1,a */
    tc = (*(volatile int *)0x2627 & 256) != 0;       /* bitf *(0x2627),#256 */
    b = a - 3;                                       /* sub #3,a,b */
    if (!tc)                                         /* xc 2,tc (skips bc+bcd) */
        goto ld8;
    if (a != 0)                                      /* bc 0x69b9,aneq (in-span) */
        goto ld8;
    /* bcd 0x69bb,bleq delays (always run): */
    b = 0;                                           /* ld #0,b */
    /* nop */
    /* taken (B = 0 <= 0): retd with delay store of 0 */
    *(volatile int *)0x564 = 0;                      /* retd delay: stl (always runs) */
    return;                                          /* retd @69bb */
ld8:
    b = 8;                                           /* ld #8,b */
    b = b - a;                                       /* sub a,b (B = B - A) */
    *(volatile int *)0x564 = (int)(b & 0xFFFF);      /* retd delay: stl (always runs) */
    /* retd */
}
