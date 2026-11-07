/* ROM6 0x4439 DISPATCH_TARGET_A -- 11w.
 * Verified encoding: src/rom6/rf/4439_dispatch_target_a.asm (recombine MATCH).
 * ORIGIN 0x4439
 * EXPECT: 4913 F310 04FA F84E 4442 4913 F310 04EF FC4A E5A9 FC00
 *
 * Intent: Two-lane dispatch gate. B = AR3 - 1274 (live-in AR3 as value); positive jumps straight to the move (bc 0x4442,bgt). Else B = AR3 - 1263; non-negative skips it (rc bgeq); else *(AR3++) = *(AR4++) single-word block move (mvdd), returns. AR3 doubles as tested value and dest pointer (by-register convention).
 */
void dispatch_target_A_4439(int *par3, int *par4)
{
    int ar3val = (int)par3;
    int b = ar3val - 1274;                       /* ldm ar3,b; sub #1274 */
    if (b <= 0) {                                /* bc 0x4442,bgt */
        b = ar3val - 1263;                       /* ldm; sub #1263 */
        if (b >= 0)                              /* rc bgeq */
            return;
    }
    *par3++ = *par4++;                           /* mvdd *ar4+,*ar3+ */
    /* ret */
}
