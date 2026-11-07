/* ROM6 0x9FA8 SUB_9FA8 -- 39w init/clear block.
 * Verified encoding: src/rom6/kernel/9fa8_sub_9fa8.asm (recombine MATCH).
 * ORIGIN 0x9FA8
 * EXPECT: F074 0616 7713 023C E800 4E83 80F8 023F 4EF8 0238 F022 62D9 4EF8 023A 76F8 023E 0001 57F8 288A 4FF8 288E E900 81F8 2893 81F8 2894 81F8 2895 81F8 2896 10F8 08E6 F030 00FF 80F8 2898 80F8 2897 FC00
 *
 * Intent: Calls sub_0616 (low-zone unsourced, flagged); AR3 =
 * 572 (out, flagged); A = 0; DST A to [572,573] (1-word
 * indirect DST: MSW@AR LSW@(AR+1), AR unchanged -- oracle
 * gap, flagged -- pairing per oracle DST_SMEM_ABSOLUTE);
 * *(0x23F) = 0; DST A to [0x238,0x239] (absolute form,
 * oracle-grounded); A = 25305<<2 (101220); DST A to
 * [0x23A,0x23B]; *(0x23E) = 1; B = DLD [0x288A,0x288B]
 * (absolute, oracle-grounded; SXM sign-extension dark,
 * flagged); DST B to [0x288E,0x288F]; B = 0; cells
 * 0x2893-0x2896 = 0; A = *(0x8E6) sign-extended (LD direct,
 * SXM dark, flagged); A &= 255; *(0x2898) = *(0x2897) = A;
 * return. In *(0x288A/B), *(0x8E6) (dark); out cleared and
 * copied cells/AR3.
 * EXPECT from the image.
 */
void sub_9FA8(void)
{
    long a;
    long b;
    int *ar3;

    sub_0616();                                              /* call 0x616 (low-zone, flagged) */
    ar3 = (int *)572;                                        /* stm #572,ar3 */
    a = 0;                                                   /* ld #0,a */
    *ar3 = (int)((a >> 16) & 0xFFFFL);                       /* dst a,*ar3 (oracle-gap form, flagged) */
    *(ar3 + 1) = (int)(a & 0xFFFFL);
    *(volatile int *)0x23F = (int)(a & 0xFFFFL);             /* stl a,*(0x23f) */
    *(volatile int *)0x238 = (int)((a >> 16) & 0xFFFFL);    /* dst a,*(0x238) (absolute, oracle) */
    *(volatile int *)0x239 = (int)(a & 0xFFFFL);
    a = 25305L << 2;                                         /* ld #25305,2,a */
    *(volatile int *)0x23A = (int)((a >> 16) & 0xFFFFL);    /* dst a,*(0x23a) */
    *(volatile int *)0x23B = (int)(a & 0xFFFFL);
    *(volatile int *)0x23E = 1;                              /* st #1,*(0x23e) */
    b = ((long)*(volatile int *)0x288A << 16)                /* dld *(0x288a),b (absolute, oracle) */
        | (unsigned int)*(volatile int *)0x288B;             /* (SXM sign-extension dark, flagged) */
    *(volatile int *)0x288E = (int)((b >> 16) & 0xFFFFL);   /* dst b,*(0x288e) */
    *(volatile int *)0x288F = (int)(b & 0xFFFFL);
    b = 0;                                                   /* ld #0,b */
    *(volatile int *)0x2893 = (int)(b & 0xFFFFL);            /* stl b,*(0x2893) */
    *(volatile int *)0x2894 = (int)(b & 0xFFFFL);            /* stl b,*(0x2894) */
    *(volatile int *)0x2895 = (int)(b & 0xFFFFL);            /* stl b,*(0x2895) */
    *(volatile int *)0x2896 = (int)(b & 0xFFFFL);            /* stl b,*(0x2896) */
    a = (long)*(volatile int *)0x8E6;                        /* ld *(0x8e6),a (SXM dark, flagged) */
    a &= 255L;                                               /* and #255,a */
    *(volatile int *)0x2898 = (int)(a & 0xFFFFL);            /* stl a,*(0x2898) */
    *(volatile int *)0x2897 = (int)(a & 0xFFFFL);            /* stl a,*(0x2897) */
    /* ret */
    (void)ar3;
}
