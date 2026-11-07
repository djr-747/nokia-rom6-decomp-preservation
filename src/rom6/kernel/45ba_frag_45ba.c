/* ROM6 0x45BA FRAG_45BA -- 8w.
 * Verified encoding: src/rom6/kernel/45ba_frag_45ba.asm (recombine MATCH).
 * ORIGIN 0x45BA
 * EXPECT: 7714 04FA 6884 FFFD FF4D 6984 0002 FC00
 *
 * Intent: Address preset plus conditional set. AR4 = 1274; clears bit 1 there (andm -3); B == 0 sets bit 1 then returns, B != 0 returns with bit clear. The xc 2,beq skip covers the 2-word orm only (per ti-c54x op_xc); the ret always runs, so 0x45C2 is NOT reached from here (correction: earlier revision tail-called it past the ret).
 */

void frag_45BA(int b_in)
{
    *(volatile int *)1274 &= -3;             /* stm; andm #-3,*ar4 */
    if (b_in == 0)                               /* xc 2,beq */
        *(volatile int *)1274 |= 2;          /* orm #2,*ar4 */
    /* ret (both paths) */
}
