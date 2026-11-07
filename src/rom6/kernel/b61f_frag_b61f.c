/* ROM6 0xB61F FRAG_B61F -- 21w.
 * Verified encoding: src/rom6/kernel/b61f_frag_b61f.asm (recombine MATCH).
 * ORIGIN 0xB61F
 * EXPECT: F763 8182 F468 F468 3182 F485 F470 EC0F 1E82 8082 E800 0882 FD4B 8082 6D92 1083 F030 00FF F463 8082 FC00
 *
 * Intent: Shift/divide/normalize lane. B <<= 3, store B-low; A <<= 16
 * (two sfta 8); A = *AR2 x A (mpya, FRCT flagged); A = |A| (abs);
 * A >>= 16; 16 SUBC divide steps against *AR2 (rpt #15, subc_step32
 * placeholder per 4348 precedent); store quotient; A = -*AR2; if B >= 0
 * refresh the store (xc 1,blt skips when B < 0); AR2++; A = *AR3 & 255;
 * A <<= 3; store; return. Entry bc (exterior) + post-RET head per asm
 * evidence. A/B/AR2/AR3 live-in (dark, flagged).
 */
extern long subc_step32(long b, int divisor);        /* SUBC placeholder (4348 precedent) */

void frag_B61F(void)
{
    long a;  /* live-in (dark, flagged) */
    long b;  /* live-in (dark, flagged) */
    int *ar2;  /* live-in (dark, flagged) */
    int *ar3;  /* live-in (dark, flagged) */
    int t;  /* T live-in for mpya (dark, flagged) */
    int i;

    b <<= 3;                                                       /* sfta b,3 */
    *ar2 = (int)(b & 0xFFFFL);                                      /* stl b,*ar2 */
    a <<= 8;                                                       /* sfta a,8 */
    a <<= 8;                                                       /* sfta a,8 */
    a = (long)t * (long)*ar2;                                      /* mpya *ar2 (A = T*Smem; T caller-live dark, flagged; FRCT flagged) */
    if (a < 0)                                                     /* abs a */
        a = -a;
    a >>= 16;                                                      /* sfta a,-16 */
    for (i = 0; i < 16; i++)                                       /* rpt #15 */
        a = subc_step32(a, *ar2);                                  /* subc *ar2,a */
    *ar2 = (int)(a & 0xFFFFL);                                     /* stl a,*ar2 */
    a = 0;                                                         /* ld #0,a */
    a -= (long)*ar2 << 16;                                        /* sub *ar2,a (SUB Smem: dst_old - Smem<<16 per op_sub_smem) */
    if (b < 0)                                                     /* xc 1,blt (executes when B<0) */
        *ar2 = (int)(a & 0xFFFFL);                                 /* stl a,*ar2 */
    ar2++;                                                         /* mar *ar2+ */
    a = (long)*ar3;                                                /* ld *ar3,a */
    a &= 255L;                                                     /* and #255,a */
    a <<= 3;                                                       /* sfta a,3 */
    *ar2 = (int)(a & 0xFFFFL);                                     /* stl a,*ar2 */
    /* ret */
}
