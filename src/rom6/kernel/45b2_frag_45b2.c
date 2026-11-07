/* ROM6 0x45B2 FRAG_45B2 -- 8w.
 * Verified encoding: src/rom6/kernel/45b2_frag_45b2.asm (recombine MATCH).
 * ORIGIN 0x45B2
 * EXPECT: 7713 04FA 6883 FFFE FF45 6983 0001 FC00
 *
 * Intent: Address preset plus conditional set. AR3 = 1274; clears bit 0 there (andm -2); A == 0 sets bit 0 then returns, A != 0 returns with bit clear. The xc 2,aeq skip covers the 2-word orm only (per ti-c54x op_xc); the ret always runs, so FRAG_45BA is NOT reached from here (correction: earlier revision tail-called it past the ret).
 */

void frag_45B2(int a_in)
{
    *(volatile int *)1274 &= -2;             /* stm; andm #-2,*ar3 */
    if (a_in == 0)                               /* xc 2,aeq */
        *(volatile int *)1274 |= 1;          /* orm #1,*ar3 */
    /* ret (both paths) */
}
