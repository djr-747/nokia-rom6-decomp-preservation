/* ROM6 0x698B SUB_6993 -- 30w.
 * Verified encoding: src/rom6/kernel/698b_sub.asm (recombine MATCH).
 * ORIGIN 0x698B
 * EXPECT: F074 0598 10F8 091F F110 0032 F84D 69A6 F074 0598 1281 7714 250C F274 4384 7712 2F11 F030 FFFF F484 00F8 2513 F540 00F8 250C FD4A F640 FE00 80F8 0563
 *
 * Intent: scaled divide with conditional offset. If cell 0x91F
 * equals 50, chain to stage 0x69A6. Else: helper call, unsigned load
 * *AR1, DIV_CORE divide (delay slots set AR2 and mask A to 16 bits
 * before the core runs), negate, add tuning cell 0x2513, then select:
 * if that sum is >= 0 use it, else add cell 0x250C as well. Store
 * the result to 0x563 and return delayed.
 */
extern void helper_0598(void);
extern void stage_69A6(void);           /* chained continuation */
extern int div_core_4384(int a16);      /* fixed cells: divisor @9484
                                         * (AR4), aux @12049 (AR2, set in
                                         * delay slot); A masked to 16
                                         * bits in the other delay slot */

void sub_698B(int **pp1)
{
    int q, s;
    helper_0598();                                /* call 0x598 */
    if (*(volatile int *)0x91F == 50) {           /* ld, sub #50, bc */
        stage_69A6();                             /* bc 0x69a6,beq */
        return;
    }
    helper_0598();                                /* call 0x598 */
    q = div_core_4384((unsigned)**pp1 & 0xFFFF);  /* ldu, calld, and #-1 */
    s = -q + *(volatile int *)0x2513;            /* neg, add, ld a,b */
    if (s < 0)                                    /* xc 1,bgeq / ld b,a */
        s += *(volatile int *)0x250C;            /* add *(0x250c),a */
    *(volatile int *)0x563 = s;                   /* retd / stl spill */
}
