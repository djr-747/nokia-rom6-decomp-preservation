/* ROM6 0xD445 D3F1_TSCALE_SUB -- 2w high-store delay slot, one EXPECT.
 * Verified encoding: src/rom6/kernel/d445_d3f1_tscale_sub.asm (recombine MATCH).
 * ORIGIN 0xD445
 * EXPECT: 82F8 0B65
 *
 * Intent: *(0xB65) = A-high (sth a,*(0xb65)). The span is the executed
 * delay pair of the RETD @D444 (per .asm header: bound D445-D446);
 * entered via calld @D818 in the static caller map, so it also reads
 * as a callable micro-store. A rides in from entry. Bound D445-D446.
 */
void frag_D445(long a_live)
{
    *(volatile int *)0xB65 = (int)((a_live >> 16) & 0xFFFF); /* sth */
    /* retd-delay context per header; falls into D447 exterior */
}
