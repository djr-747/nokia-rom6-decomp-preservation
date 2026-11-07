/* ROM6 0x456A FRAG_456A -- 14w.
 * Verified encoding: src/rom6/kernel/456a_frag_456a.asm (recombine MATCH).
 * ORIGIN 0x456A
 * EXPECT: 4913 F310 04FA F84E 4576 4913 F310 04EF F84B 4576 7713 2F64 E59A FC00
 *
 * Intent: Two-lane dispatch gate, reversed move. B = AR3 - 1274 (live-in AR3 as value); positive jumps straight to the move (bc 0x4576,bgt). Else B = AR3 - 1263; negative skips the preset (bc 0x4576,blt); else AR3 = 12132. Move is *(AR4++) = *(AR3++) (mvdd direction reversed vs 4439), returns. AR3 doubles as tested value and source pointer (by-register convention).
 */
void frag_456A(int *par3, int *par4)
{
    int ar3val = (int)par3;
    int *src;
    int b = ar3val - 1274;                       /* ldm ar3,b; sub #1274 */
    if (b > 0)                                   /* bc 0x4576,bgt */
        src = par3;
    else {
        b = ar3val - 1263;                       /* ldm; sub #1263 */
        src = (b < 0) ? par3 : (int *)12132;     /* bc 0x4576,blt; stm */
    }
    *par4++ = *src++;                           /* mvdd *ar3+,*ar4+ */
    /* ret */
}
