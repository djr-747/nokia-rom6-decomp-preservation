/* ROM6 0xBFB7 FRAG_BFB7 -- 29w polynomial/saturate lane.
 * Verified encoding: src/rom6/kernel/bfb7_frag_bfb7.asm (recombine MATCH).
 * ORIGIN 0xBFB7
 * EXPECT: 7711 BCBA 3068 4489 4589 EC02 3689 F689 F48C 3C68 F45F 3C81 950F 0342 838A 1942 6F41 0C0C F84D BFD4 F483 8268 2768 4382 2D41 4041 FE00 8282 9C0F
 *
 * Intent: Horner polynomial evaluation with T = *(0x68) over
 * the coefficient table at AR1 = -17222, feeding a
 * square-law/saturate tail with a conditional exit to the
 * BFD4 span. A = *AR1- << 16; B = *AR1- << 16; 3x POLY
 * *AR1- (rpt #2): A = rnd(T * AH + B_old) and B =
 * SXM(*AR1-) << 16 per the oracle POLY leaf
 * (op_poly_smem; rounding/FRCT/OVM and SXM dark, flagged);
 * MACAR leg: A += T * B (round per MACAR flagged); MPYA
 * leg A = T * A; scaled add/half/tap leg; B = *AR2 << 15;
 * B = sat(B + mem(0x42)) (ADDS); store B MSW to *AR2-; B &=
 * mem(0x42); A += mem(0x41) << 12; BC BEQ to the BFD4 span
 * when A == 0 (in-image span BFD4, asm-verified, no C entry
 * -- exits the span, modeled as return with a note);
 * else SAT A (OVM dark, flagged), write back A MSW to
 * 0x68; SQUR leg B += mem(0x68)^2; B -= *AR2 << 16; B -= T
 * * mem(0x41) (MAS); A -= mem(0x41) << 16; return with
 * *AR2 = MSW(A) and TC-conditional store of T
 * (STRCD ... ,BLEQ) in the delay slots. Out: 0x68/*AR2/A/B.
 * (Wave-13: POLY dual-channel, MACAR T-form, and SUB/ADD
 * Smem <<16 corrected per the oracle leaves.)
 */
void frag_BFB7(void)
{
    long a;
    long b;
    int *ar1;
    int *ar2;  /* live-in (dark, flagged) */
    int t;
    int i;

    ar1 = (int *)-17222;                                       /* stm #-17222,ar1 */
    t = *(volatile int *)0x68;                                 /* ld 0x68,t */
    a = (long)*ar1-- << 16;                                    /* ld *ar1-,16,a */
    b = (long)*ar1-- << 16;                                    /* ld *ar1-,16,b */
    for (i = 0; i < 3; i++) {                                  /* rpt #2 */
        a = (long)t * (long)(int)(a >> 16) + b;                /* poly *ar1- (A = rnd(T*AH + B_old); round/FRCT/OVM flagged) */
        b = (long)*ar1-- << 16;                                /* poly B channel (SXM-dark, flagged) */
    }
    a += (long)t * b;                                          /* macar t,b,a (round per MACAR flagged) */
    a = (long)t * a;                                           /* mpya a (A = T*A) */
    a += (long)*(volatile int *)0x68 << 16;                    /* add 0x68,16,a */
    a >>= 1;                                                   /* ld a,-1,a */
    a += (long)*ar1 << 16;                                     /* add *ar1,16,a */
    b = (long)*ar2 << 15;                                      /* ld *ar2,15,b */
    { long nb = b + ((long)*(volatile int *)0x42 << 16);      /* adds 0x42,b (same Smem<<16 addend as ADD, then saturate) */
      if (nb > 0x7FFFFFFFL) nb = 0x7FFFFFFFL;                   /* (saturate; OVM dark, flagged) */
      if (nb < -0x80000000L) nb = -0x80000000L;
      b = nb; }
    *ar2-- = (int)((b >> 16) & 0xFFFFL);                       /* sth b,*ar2- */
    b &= (long)(*(volatile int *)0x42 & 0xFFFF);                          /* and 0x42,b */
    a += (long)*(volatile int *)0x41 << 12;                    /* add 0x41,12,a */
    if (a == 0)                                                /* bc 0xbfd4,beq */
        return; /* (exits to BFD4 span: in-image, asm-verified, no C entry -- span owns the word) */
    /* sat a (OVM dark, flagged) */
    if (a > 0x7FFFFFFFL) a = 0x7FFFFFFFL;
    if (a < -0x80000000L) a = -0x80000000L;
    *(volatile int *)0x68 = (int)((a >> 16) & 0xFFFFL);       /* sth a,0x68 */
    b += (long)*(volatile int *)0x68 * (long)*(volatile int *)0x68; /* squr 0x68,b */
    b -= (long)*ar2 << 16;                                     /* sub *ar2,16,b */
    b -= (long)t * (long)*(volatile int *)0x41;                /* mas 0x41,b */
    a -= (long)*(volatile int *)0x41 << 16;                    /* sub 0x41,16,a */
    /* retd (delay words run, then return): */
    *ar2 = (int)((a >> 16) & 0xFFFFL);                         /* sth a,*ar2 */
    if (b <= 0)                                                /* strcd *ar2,bleq */
        *ar2 = t;
    /* retd */
    (void)ar1;
}
