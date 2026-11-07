/* ROM6 0x3115 SUB_3115 -- 10w.
 * Verified encoding: src/rom6/kernel/3115_sub_3115.asm (recombine MATCH).
 * ORIGIN 0x3115
 * EXPECT: 10F8 0011 7713 051E 6883 EFFF FF46 6983 1000 FC00
 *
 * Intent: Flag-cell preset. A = MMR cell 0x11; AR3 = 1310; clears bit 12 there (andm -4097); A > 0 sets bit 12 then returns, A <= 0 returns with bit clear. The xc 2,agt skip covers the 2-word orm only (per ti-c54x op_xc: taken executes, not-taken skips exactly 2 words); the ret always runs, so 0x311F is NOT reached from here (correction: earlier revision tail-called it past the ret).
 */

void sub_3115(void)
{
    int a = *(volatile int *)0x11;               /* ld *(0x11),a */
    *(volatile int *)1310 &= -4097;          /* stm; andm */
    if (a > 0)                                   /* xc 2,agt */
        *(volatile int *)1310 |= 4096;       /* orm #4096,*ar3 */
    /* ret (both paths) */
}
