/* ROM6 0xD8F4 SUB_D8E3 -- 2w cell store pair, one EXPECT.
 * Verified encoding: src/rom6/kernel/d8f4_sub_d8e3.asm (recombine MATCH).
 * ORIGIN 0xD8F4
 * EXPECT: 8059 805A
 *
 * Intent: *(0x59) = *(0x5A) = A-low (stl pair). A rides in from entry,
 * unchanged. Called via calld @D979 (per header); the span is the RETD
 * @D8F3 delay pair. Bound D8F4-D8F5.
 */
void sub_D8E3(long a_live)
{
    int lo = (int)(a_live & 0xFFFF);                 /* stl a (x2) */

    *(volatile int *)0x59 = lo;                      /* stl a,0x59 */
    *(volatile int *)0x5A = lo;                      /* stl a,0x5a */
}
