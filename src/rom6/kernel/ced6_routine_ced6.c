/* ROM6 0xCED6 ROUTINE_CED6 -- 43w normalize/divide kernel.
 * Verified encoding: src/rom6/kernel/ced6_routine_ced6.asm (recombine MATCH).
 * ORIGIN 0xCED6
 * EXPECT: 7712 0CF2 7713 1100 ED1F 4492 EC27 C889 7712 0CA2 7713 1100 E734 E801 EC27 B089 F48E 8C63 F48F 8662 FE47 E800 ED00 2694 EC26 3894 F48E 8C65 F48F 8264 E905 E810 0163 0965 F587 F784 890E 4462 EC0E 1E64 FE00 8066 1466
 *
 * Intent: AR2 = 3314, AR3 = 4352, ASM-reg = -1; A =
 * *(AR2++)<<16; 40x parallel copy *(AR3++) = A-low with
 * A = *(AR2++) reloaded (rpt #39 runs 40; SXM dark,
 * flagged). AR2 = 3234, AR3 = 4352, AR4 = AR3; A = 1; 40x
 * A += *(AR2++) x *(AR3++) (rpt #39 mac dual; FRCT
 * doubling dark, flagged). T = exp(A) = redundant-sign-bits
 * - 8 (oracle op_exp; computed for the 32-bit int model,
 * 40-bit narrowing flagged); *(0x63) = T; A <<= T-count
 * (norm, TS = sign-extended T[5:0] per oracle op_norm_acc;
 * SXM-gated right shifts flagged); *(0x62) = bits 31-16 of
 * (A>>1) (sth a,asm with asm-reg -1, flagged). A <= 0
 * returns (rcd aleq, delayed: A = 0 and ASM-reg = 0 run
 * regardless). Else A = *(AR4++)^2 (squr); 39x A +=
 * *(AR4++)^2 (rpt #38 squra; FRCT dark, flagged); T =
 * exp(A); *(0x65) = T; A <<= T-count; *(0x64) = A-high
 * (sth default shift, ASM dark flagged). B = 5; A = 16;
 * B += *(0x63)<<16; B -= *(0x65)<<16; B = min(A,B)
 * (signed); B = -B; T = B-low (stlm); A = *(0x62)<<16;
 * 15x A = subc-step(*(0x64)) (rpt #14; t = A - (Smem<<15):
 * t > 0 wraps (t<<1)+1 C-set else (A<<1), SXM-MSB caveat
 * flagged per oracle op_subc_smem; C dead); retd delays run
 * pre-return: *(0x66) = A-low; A = *(0x66)<<(T) with TS =
 * sign-extended T[5:0] (LD-TS convention per NORM oracle,
 * flagged); return. SXM/FRCT/OVM/ASM/T dark as noted.
 * EXPECT from the image.
 */
void routine_CED6(void)
{
    long a;
    long b;
    unsigned long u;
    int *ar2;
    int *ar3;
    int *ar4;
    int t;
    int asm_reg;
    int shift;
    int take;
    long diff;
    long s;
    int i;

    ar2 = (int *)3314;                                       /* stm #3314,ar2 */
    ar3 = (int *)4352;                                       /* stm #4352,ar3 */
    asm_reg = -1;                                            /* ld #-1,asm */
    a = (long)*ar2++ << 16;                                  /* ld *ar2+,16,a */
    for (i = 0; i < 40; i++) {                               /* rpt #39 (k+1) */
        *ar3++ = (int)(a & 0xFFFFL);                         /* st a,*ar3+ (parallel) */
        a = (long)*ar2++;                                    /* ld *ar2+,a (SXM dark, flagged) */
    }
    ar2 = (int *)3234;                                       /* stm #3234,ar2 */
    ar3 = (int *)4352;                                       /* stm #4352,ar3 */
    ar4 = ar3;                                               /* mvmm ar3,ar4 */
    a = 1;                                                   /* ld #1,a */
    for (i = 0; i < 40; i++)                                 /* rpt #39 mac dual */
        a += (long)*ar2++ * (long)*ar3++;                    /* mac *ar2+,*ar3+,a (FRCT dark) */
    if (a >= 0) {                                            /* exp a (oracle; 40-bit narrow flagged) */
        u = (unsigned long)a;
        t = 0;
        while ((u & 0x80000000UL) == 0 && t < 32) {
            u <<= 1;
            t++;
        }
    } else {
        u = ~(unsigned long)a;
        t = 0;
        while ((u & 0x80000000UL) == 0 && t < 32) {
            u <<= 1;
            t++;
        }
    }
    *(volatile int *)0x63 = t;                               /* st t,0x63 */
    shift = t & 63;                                          /* norm a (TS = sign-extended T5:0) */
    if ((shift & 32) != 0)
        shift -= 64;
    if (shift >= 0)
        a = a << shift;                                      /* (wrap/OVM flagged) */
    else
        a = a >> -shift;                                     /* (SXM-gated, flagged) */
    *(volatile int *)0x62 = (int)(((a >> 1) >> 16) & 0xFFFFL); /* sth a,asm,0x62 (asm-reg -1, flagged) */
    {                                                        /* rcd aleq (delayed) */
        take = (a <= 0);                                     /* (issue-time A decides) */
        a = 0;                                               /* delay: ld #0,a */
        asm_reg = 0;                                         /* delay: ld #0,asm */
        if (take)
            return;
    }
    a = (long)*ar4 * (long)*ar4;                             /* squr *ar4+,a (FRCT dark, flagged) */
    ar4++;
    for (i = 0; i < 39; i++) {                               /* rpt #38 (k+1) */
        s = (long)*ar4++;                                    /* squra *ar4+,a */
        a += s * s;                                          /* (FRCT doubling dark, flagged) */
    }
    if (a >= 0) {                                            /* exp a (second; narrow flagged) */
        u = (unsigned long)a;
        t = 0;
        while ((u & 0x80000000UL) == 0 && t < 32) {
            u <<= 1;
            t++;
        }
    } else {
        u = ~(unsigned long)a;
        t = 0;
        while ((u & 0x80000000UL) == 0 && t < 32) {
            u <<= 1;
            t++;
        }
    }
    *(volatile int *)0x65 = t;                               /* st t,0x65 */
    shift = t & 63;                                          /* norm a (TS convention, flagged) */
    if ((shift & 32) != 0)
        shift -= 64;
    if (shift >= 0)
        a = a << shift;
    else
        a = a >> -shift;
    *(volatile int *)0x64 = (int)((a >> 16) & 0xFFFFL);      /* sth a,0x64 (ASM dark, flagged) */
    b = 5;                                                   /* ld #5,b */
    a = 16;                                                  /* ld #16,a */
    b += (long)*(volatile int *)0x63 << 16;                  /* add 0x63,b */
    b -= (long)*(volatile int *)0x65 << 16;                  /* sub 0x65,b */
    if (a < b)                                               /* min b (oracle) */
        b = a;
    b = -b;                                                  /* neg b (LONG_MIN flagged) */
    t = (int)(b & 0xFFFFL);                                  /* stlm b,t */
    a = (long)*(volatile int *)0x62 << 16;                   /* ld 0x62,16,a */
    for (i = 0; i < 15; i++) {                               /* rpt #14 (k+1) subc */
        diff = a - ((long)*(volatile int *)0x64 << 15);      /* subc (SXM-MSB caveat flagged) */
        if (diff > 0)                                        /* (C set; C dead) */
            a = (diff << 1) + 1;
        else
            a = a << 1;
    }
    /* retd: delays run, then return */
    *(volatile int *)0x66 = (int)(a & 0xFFFFL);              /* stl a,0x66 */
    shift = t & 63;                                          /* ld 0x66,ts,a (TS convention, flagged) */
    if ((shift & 32) != 0)
        shift -= 64;
    a = (long)*(volatile int *)0x66;
    if (shift >= 0)
        a = a << shift;
    else
        a = a >> -shift;
    /* retd */
    (void)asm_reg;
}
