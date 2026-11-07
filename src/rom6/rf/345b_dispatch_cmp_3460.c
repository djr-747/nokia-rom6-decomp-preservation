/* ROM6 0x345B DISPATCH_CMP_3460 -- 5w.
 * Verified encoding: src/rom6/rf/345b_dispatch_cmp_3460.asm (recombine MATCH).
 * ORIGIN 0x345B
 * EXPECT: 7710 0001 1082 F130 00FF
 *
 * Intent: Compare-operand setup with fall-through. AR0 = 1 (dead preset, head-annex index step, noted); A = *AR2-live-in, B = A AND 255 (and); A and B both live-out into the 0x3460 compare head (out-params). 5w per .asm header (Bound 345B-345F head annex; recombine MATCH).
 */
void frag_345B(int *par2, int *pa_out, int *pb_out)
{
    int a;
    /* stm #1,ar0 (dead preset, head-annex step) */
    a = *par2;                                      /* ld *ar2,a */
    *pa_out = a;
    *pb_out = a & 255;                              /* and #255,a,b */
    /* falls through (no exit in span) */
}
