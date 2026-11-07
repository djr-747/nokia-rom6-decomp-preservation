/* ROM6 0xAB25 FRAG_AB25 -- 7w.
 * Verified encoding: src/rom6/kernel/ab25_frag_ab25.asm (recombine MATCH).
 * ORIGIN 0xAB25
 * EXPECT: F261 2C00 FC42 F540 FE00 F360 2E78
 *
 * Intent: Biased 32-bit clamp leaf. A = B - (11264 << 16) (SUB #lk,SHFT:
 * dst = src - (lk << shift) per ti-c54x op_sub_lk header doc); A >= 0
 * near-returns A (rc ageq); else B = A, B += 11896 << 16 (ADD #lk,SHFT
 * per op_add_lk), far return. The retd delay add always runs. The
 * near/far return mix is modeled as plain returns (flagged). long holds
 * the 32-bit accumulators; both immediates fit 32-bit, 40-bit guard bits
 * unmodeled (flagged). Bound AB25-AB2B.
 */
long frag_AB25(long b_live)
{
    long a = b_live - (11264L << 16);                /* sub #11264,16,b,a */
    long b;
    if (a >= 0)                                      /* rc ageq (near) */
        return a;
    b = a;                                           /* ld a,b */
    b += (11896L << 16);                             /* retd delay: add (always runs) */
    return b;                                        /* retd (far) */
}
