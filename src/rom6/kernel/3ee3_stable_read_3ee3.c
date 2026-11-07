/* ROM6 0x3EE3 STABLE_READ_3EE3 -- 16w port-13 stability loop.
 * Verified encoding: src/rom6/kernel/3ee3_stable_read_3ee3.asm (recombine MATCH).
 * ORIGIN 0x3EE3
 * EXPECT: E800 74F8 0008 000D F030 3FFF F540 74F8 0008 000D F030 3FFF F520 F84C 3EE9 FC00
 *
 * Intent: Port-13 stable read. Linear fall-through from the 3EE1 stub
 * head (which runs dark SUB_063E first). A = 0; loop: *(0x8) = port 13
 * (portr pa13,*(0x8): PORTR Smem-only read); A &= 16383 (14-bit mask,
 * immediate zero-extended); B = A (first sample); re-read port 13,
 * A &= 16383 (second sample); B = B - A (sub a,b: dst -= src);
 * nonzero loops (bc bneq). Exits with A = stable 14-bit reading,
 * B = 0. A-OUT PROVEN by the loop shape (both accumulators are
 * unconditionally rewritten; callee-preservation impossible) -- this
 * settles the A2C3-vs-2983 conflict in favor of A-out: every caller
 * reading A/B after call 0x3EE1 gets the reading/0, never live-ins.
 * RET @3EF2; bound 3EE3-3EF2.
 */
extern int port_read_13(void);

int stable_read_3EE3(void)
{
    long a;
    long b;

    a = 0;                                                   /* ld #0,a */
    do {
        *(volatile int *)0x8 = port_read_13();        /* portr pa13 */
        a = (long)*(volatile int *)0x8 & 16383L;     /* and #16383,a */
        b = a;                                       /* ld a,b (sample) */
        *(volatile int *)0x8 = port_read_13();        /* portr pa13 */
        a = (long)*(volatile int *)0x8 & 16383L;     /* and #16383,a */
        b -= a;                                      /* sub a,b */
    } while (b != 0);                                /* bc 0x3ee9,bneq */
    return (int)a;                                   /* ret (A-out) */
}
