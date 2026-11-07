/* ROM6 0xD3EF D3BE_CLAMP_STORE_SUB -- 2w high-store pair, one EXPECT.
 * Verified encoding: src/rom6/kernel/d3ef_d3be_clamp_store_sub.asm (recombine MATCH).
 * ORIGIN 0xD3EF
 * EXPECT: 835B 8382
 *
 * Intent: *(0x5B) = *(AR2) = B-high (sth b,DP+0x5b + sth b,*ar2;
 * DP-relative transcribed absolute with DP = 0 assumed -- thin retd-delay
 * entry, trace-confirmable). B rides in from entry, unchanged. Interior
 * of the D3BE lane (calld @D834 per header); the span is the RETD @D3EE
 * delay pair. Bound D3EF-D3F0.
 */
void d3be_clamp_store_sub(long b_live, int *par2)
{
    int hi = (int)((b_live >> 16) & 0xFFFF);         /* sth b (x2) */

    *(volatile int *)0x5B = hi;                      /* sth b,DP+0x5b */
    *par2 = hi;                                      /* sth b,*ar2 */
}
