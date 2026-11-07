/* ROM6 0xE583 BLK_E583 -- 26w scale/normalize lane.
 * Verified encoding: src/rom6/kernel/e583_blk_e583.asm (recombine MATCH).
 * ORIGIN 0xE583
 * EXPECT: 827D 407D F466 8212 4808 F47F 807E 6DEA FAA8 4592 428A 337E E81D 087D F484 880E F000 0010 F78F F495 FD43 F770 E801 FE00 F500 F67F
 *
 * Intent: Fixed-point scaling lane. A MSW saved to 0x7D; A =
 * A_old - (mem(0x7D) << 16) (SUB Smem,SHFT per op_sub_smem),
 * scaled << 6, MSW to 0x12; A = AL halved to 0x7E tap; AR2 +=
 * 0xFAA8 table hop; B = *AR2 << 16; A = (*AR2 << 16) - B
 * (4-operand SUB Xmem,SHFT,src,dst per SPRU172: dst =
 * (Xmem << SHFT) - src; successive-sample difference);
 * MASA against the 0x7E tap (B -= T*mem); shift count from
 * (mem(0x7D) - 29) + 16 into T; single NORM step on B (count
 * to T, conditional-shift exact per SPRU172, flagged);
 * ALT-gated B >>= 16; return with A = 1, B += A, A = B >> 1
 * in the delay slots. AGC/normalize helper: A + AR2 live-in
 * (dark, flagged); T live-in (dark, flagged).
 * (Wave-13: SUB direction/scale and 4-operand order
 * corrected per the oracle leaves; was reversed/unshifted.)
 */
void blk_E583(void)
{
    long a;  /* live-in (dark, flagged) */
    long b;
    int *ar2;  /* live-in (dark, flagged) */
    int t;  /* T live-in (dark, flagged) */

    *(volatile int *)0x7D = (int)((a >> 16) & 0xFFFFL);        /* sth a,0x7d */
    a = a - ((long)*(volatile int *)0x7D << 16);                /* sub 0x7d,16,a */
    a <<= 6;                                                   /* sfta a,6 */
    *(volatile int *)0x12 = (int)((a >> 16) & 0xFFFFL);        /* sth a,0x12 */
    a &= 0xFFFFL;                                              /* ldm al,a */
    a >>= 1;                                                   /* sfta a,-1 */
    *(volatile int *)0x7E = (int)(a & 0xFFFFL);                /* stl a,0x7e */
    ar2 += 0xFAA8;                                             /* mar *+ar2(0xfaa8) */
    b = (long)*ar2 << 16;                                      /* ld *ar2+,16,b */
    ar2++;
    a = ((long)*ar2 << 16) - b;                                /* sub *ar2-,16,b,a */
    ar2--;
    b = b - (long)t * (long)*(volatile int *)0x7E;            /* masa 0x7e,b */
    a = 29;                                                    /* ld #29,a */
    a = (long)*(volatile int *)0x7D - a;                       /* sub 0x7d,a */
    a = -a;                                                    /* neg a */
    t = (int)(a & 0xFFFFL);                                    /* stlm a,t */
    a += 16;                                                   /* add #16,a */
    /* norm b (single conditional normalize step; count to T, flagged) */
    b <<= 1;                                                   /* (representative shift; exact condition per SPRU172, flagged) */
    /* nop */
    if (a < 0)                                                 /* xc 1,alt (executes when A<0) */
        b >>= 16;                                              /* sfta b,-16 */
    a = 1;                                                     /* ld #1,a */
    /* retd (delay words run, then return): */
    b = b + a;                                                 /* add a,b */
    a = b >> 1;                                                /* sfta b,-1,a */
    /* retd */
    (void)a; (void)b;
}
