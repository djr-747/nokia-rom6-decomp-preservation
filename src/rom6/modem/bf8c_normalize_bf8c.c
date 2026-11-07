/* ROM6 0xBF8C NORMALIZE_BF8C -- 30w.
 * Verified encoding: src/rom6/modem/bf8c_normalize_bf8c.asm (recombine MATCH).
 * ORIGIN 0xBF8C
 * EXPECT: F074 06DE FE45 8291 8289 4A07 F6B9 F585 F58E F6B8 F78F 0342 F583 8381 4543 EC0F 1F81 F330 FFFF 0141 F74F FD43 F784 F583 8391 8C81 6B89 FFE2 8A07 FC00
 *
 * Intent: Modem normalize/divide engine (4 callers). Runs dark
 * SUB_06DE (helper_06DE, bfaa precedent; outs dark). rcd aeq: both
 * 1-word sth delays fill the 2-word window and always run (520C
 * word-count rule), then A == 0 returns. Fall path continues.
 * MEM[*AR1] = A-high twice (sth pair; AR1 +1 then back: net 0 fall,
 * +1 taken). ST1 saved/restored around the lane (pshm/popm ST1;
 * C-local per the 2D5E precedent). OVM/SXM cleared in-lane (rsbx,
 * hardware state, no C form). B = |A| (abs a,b; LONG_MIN edge:
 * HW wraps per op_abs_acc with OVM=0, C negation UB -- flagged).
 * T = exp(B) (redundant-sign-bits minus 8 per the op_exp leaf:
 * T = lz32 - 1, B == 0 gives 0). B <<= T signed (norm b per
 * op_norm_acc; T >= 0 except the flagged edge; 40-bit wrap flagged).
 * B += sign-extended *(0x42) (adds: SXM-independent sign add per
 * the 4b81 precedent). sat b (identity in 32-bit long; 40-bit
 * overflow already flagged). MEM[*AR1] = B-high (sth). B =
 * *(0x43) << 16 (ld Smem,16, 425f precedent). 16 SUBC steps against
 * divisor *AR1 (rpt #15; subc_step32 placeholder: exact carry
 * semantics in the .asm per the 4348 div_step precedent; SUBC is
 * SXM-shifted and SXM = 0 in-lane; FRCT interaction inside the
 * placeholder, flagged). B &= 0xFFFF (and #-1,b). B +=
 * zero-extended *(0x41) (add with SXM = 0: zero-extend per the
 * ADD-Smem convention). B <<= 15 (ld b,15,b; 40-bit wrap flagged --
 * full-scale quotients exceed 32-bit long). A < B negates B (xc
 * 1,alt over neg b). sat b (identity, flagged as above).
 * MEM[*AR1++] = B-high; MEM[*AR1] = T (st t). MEM[*AR1] -= 30,
 * AR1-- (addm; AR1 net 0 fall). ST1 restored, return. A preserved
 * (abs reads only). A-in/B-in explicit (B-in live only on the
 * rcd-taken return); B-out computed (caller liveness unbound,
 * flagged); T-out = exponent (not carried, flagged); AR1 via ppar1
 * (2e64 precedent).
 */
extern void helper_06DE(void);                       /* dark */
extern long subc_step32(long b, int divisor);        /* SUBC placeholder (4348 precedent) */

long frag_BF8C(long a_in, long b_in, int **ppar1)
{
    long a = a_in;
    long b = b_in;
    int t;
    int *ar1 = *ppar1;
    int i;
    int lz;
    int k;
    unsigned long ub;
    int divisor;
    helper_06DE();                                   /* call 0x6de */
    *ar1++ = (int)((a >> 16) & 0xFFFF);              /* rcd delay 1: sth a,*ar1+ */
    *ar1-- = (int)((a >> 16) & 0xFFFF);              /* rcd delay 2: sth a,*ar1- */
    if (a == 0) {                                    /* rcd aeq taken */
        *ppar1 = ar1;
        return b;
    }
    /* pshm st1 (C-local, restored at popm) */
    /* rsbx st1,ovm / rsbx st1,sxm (hardware, no C form) */
    b = a >= 0 ? a : -a;                             /* abs a,b (LONG_MIN flagged) */
    if (b == 0) {                                    /* exp b (op_exp: 0 -> 0) */
        t = 0;
    } else {
        ub = (unsigned long)b;
        lz = 0;
        for (k = 31; k >= 0; k--) {                  /* lz32 */
            if ((ub >> k) & 1UL)
                break;
            lz++;
        }
        t = lz - 1;                                  /* redundant-bits minus 8 */
    }
    /* norm b (op_norm_acc, T-preserved) */
    if (t >= 0) {
        b <<= t;
    } else {
        b = (long)((unsigned long)b >> (unsigned)(-t)); /* SXM=0 logical (edge) */
    }
    b += (long)*(volatile int *)0x42;                /* adds 0x42,b (sign add) */
    /* sat b (identity in long, 40-bit flagged) */
    *ar1 = (int)((b >> 16) & 0xFFFF);                /* sth b,*ar1 */
    b = (long)*(volatile int *)0x43 << 16;           /* ld 0x43,16,b */
    divisor = *ar1;                                  /* subc divisor (cell stable) */
    for (i = 0; i < 16; i++)                         /* rpt #15 */
        b = subc_step32(b, divisor);                 /* subc *ar1,b */
    b &= 0xFFFFL;                                    /* and #-1,b */
    b += (long)(unsigned)*(volatile int *)0x41;      /* add 0x41,b (SXM=0 zero-ext) */
    b <<= 15;                                        /* ld b,15,b (40-bit flagged) */
    if (a < b)                                       /* xc 1,alt (40-bit compare flagged) */
        b = -b;                                      /* neg b */
    /* sat b (identity, flagged as above) */
    *ar1++ = (int)((b >> 16) & 0xFFFF);              /* sth b,*ar1+ */
    *ar1 = t;                                        /* st t,*ar1 */
    *ar1 += -30;                                     /* addm #-30,*ar1- */
    ar1--;
    /* popm st1 */
    *ppar1 = ar1;
    return b;
}
