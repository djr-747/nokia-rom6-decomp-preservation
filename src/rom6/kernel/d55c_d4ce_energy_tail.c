/* ROM6 0xD55C D4CE_ENERGY_TAIL -- 2w low-store pair, one EXPECT.
 * Verified encoding: src/rom6/kernel/d55c_d4ce_energy_tail.asm (recombine MATCH).
 * ORIGIN 0xD55C
 * EXPECT: 8082 805E
 *
 * Intent: *(AR2) = *(0x5E) = A-low (stl a,*ar2 + stl a,0x5e). A rides in
 * from entry, unchanged. Entered via 0xD49B bc ntc (per header); the span
 * is the RETD @D55B delay pair. Bound D55C-D55D.
 */
void frag_D55C(long a_live, int *par2)
{
    int lo = (int)(a_live & 0xFFFF);                 /* stl a (x2) */

    *par2 = lo;                                      /* stl a,*ar2 */
    *(volatile int *)0x5E = lo;                      /* stl a,0x5e */
}
