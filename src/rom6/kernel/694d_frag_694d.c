/* ROM6 0x694D FRAG_694D -- 7w.
 * Verified encoding: src/rom6/kernel/694d_frag_694d.asm (recombine MATCH).
 * ORIGIN 0x694D
 * EXPECT: F010 0021 880E F495 34E9 0003 FC30
 *
 * Intent: Shifted-bit bail with fall-through. T = A-live-in - 33 (sub plus stlm a,t); bit T of *(AR1-live-in + 3) set returns (bitt plus rc tc; T in-range assumed, noted). Else falls into the 0x6954 head. Bound 694D-6953.
 */
void frag_694D(int a_live, int *par1)
{
    int t = a_live - 33;                         /* sub #33,a; stlm a,t */
    /* nop */
    if (((*(par1 + 3) >> t) & 1) != 0)            /* bitt; rc tc */
        return;
    /* falls through (no exit in span) */
}
