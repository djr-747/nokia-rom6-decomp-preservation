/* ROM6 0xE8C7 FRAG_E8C7 -- 29w butterfly add/sub network.
 * Verified encoding: src/rom6/kernel/e8c7_frag_e8c7.asm (recombine MATCH).
 * ORIGIN 0xE8C7
 * EXPECT: A301 A001 8783 A123 F600 8692 F621 A323 C81A 8795 A327 F680 8293 F63F 4585 8295 A023 8684 A201 F602 86B5 F623 A101 C82D F502 87B2 F523 87B4 FC00
 *
 * Intent: In-place sum/difference (butterfly) network over
 * the AR2/AR3 and AR4/AR5 pairs with ASM-saturated MSW
 * stores (sth ...,asm,... -- ASM shifter mode dark,
 * flagged). B = (*AR2 - *AR3) << 16, A = (*AR2 + *AR3) <<
 * 16 (SUB/ADD dual MOD0 = X -/+ Y, SXM-widened <<16 per
 * op_dual_arithmetic); B/MSW to *AR3; cross-accumulate
 * with the AR4/AR5 pair; offset ladder in the accumulator-
 * first shift forms (A = A_old - (B << 1); A = A_old -
 * (B >> 1); A = A_old + (B << 2); A = A_old - (B << 3);
 * B = B_old - (A << 3) per the op_arithmetic/op_sub_src_asm
 * leaves); two parallel store/load pairs; tail re-sums
 * into B and streams saturated MSWs to *AR2+0/*AR4+0;
 * return. FFT-butterfly shape (cf. modem 9146/9118 lanes).
 * (Wave-13: dual results <<16 with X-first order; shift
 * forms as dst_old +/- src<<SHFT -- corrected per the
 * oracle leaves.)
 */
void frag_E8C7(void)
{
    long a;
    long b;
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;  /* live-in (dark, flagged) */
    int *ar4;  /* live-in (dark, flagged) */
    int *ar5;  /* live-in (dark, flagged) */
    int asmsh;  /* ASM shifter mode (dark, flagged) */

    b = ((long)*ar2 - (long)*ar3) << 16;                       /* sub *ar2,*ar3,b (dual) */
    a = ((long)*ar2 + (long)*ar3) << 16;                       /* add *ar2,*ar3,a (dual) */
    *ar3 = (int)(((b << asmsh) >> 16) & 0xFFFFL);              /* sth b,asm,*ar3 */
    b = ((long)*ar4 + (long)*ar5) << 16;                       /* add *ar4,*ar5,b (dual) */
    a += b;                                                    /* add b,a */
    *ar2++ = (int)(((a << asmsh) >> 16) & 0xFFFFL);            /* sth a,asm,*ar2+ */
    a -= b << 1;                                               /* sub b,1,a */
    b = ((long)*ar4 - (long)*ar5) << 16;                       /* sub *ar4,*ar5,b (dual) */
    *ar4++ = (int)(a & 0xFFFFL);                               /* st a,*ar4+ || ld *ar3,a */
    a = (long)*ar3;
    *ar5++ = (int)(((b << asmsh) >> 16) & 0xFFFFL);            /* sth b,asm,*ar5+ */
    b = ((long)*ar4 - (long)*ar5--) << 16;                     /* sub *ar4,*ar5-,b (dual) */
    a += b << asmsh;                                           /* add b,asm,a */
    *ar3++ = (int)((a >> 16) & 0xFFFFL);                       /* sth a,*ar3+ */
    a -= b >> 1;                                               /* sub b,-1,a */
    b = (long)*ar5 << 16;                                      /* ld *ar5,16,b */
    *ar5++ = (int)((a >> 16) & 0xFFFFL);                       /* sth a,*ar5+ */
    a = ((long)*ar4 + (long)*ar5) << 16;                       /* add *ar4,*ar5,a (dual) */
    *ar4 = (int)(((a << asmsh) >> 16) & 0xFFFFL);              /* sth a,asm,*ar4 */
    a = ((long)*ar2 - (long)*ar3) << 16;                       /* sub *ar2,*ar3,a (dual) */
    a += b << 2;                                               /* add b,2,a */
    *ar5 = (int)(((a << asmsh) >> 16) & 0xFFFFL);              /* sth a,asm,*ar5+0 */
    a -= b << 3;                                               /* sub b,3,a */
    b = ((long)*ar2 + (long)*ar3) << 16;                       /* add *ar2,*ar3,b (dual) */
    *ar3 = (int)(a & 0xFFFFL);                                 /* st a,*ar3+0% || ld *ar4,a */
    a = (long)*ar4;
    b += a << 2;                                               /* add a,2,b */
    *ar2 = (int)(((b << asmsh) >> 16) & 0xFFFFL);              /* sth b,asm,*ar2+0 */
    b -= a << 3;                                               /* sub a,3,b */
    *ar4 = (int)(((b << asmsh) >> 16) & 0xFFFFL);              /* sth b,asm,*ar4+0 */
    /* ret */
    (void)a; (void)b; (void)asmsh;
}
