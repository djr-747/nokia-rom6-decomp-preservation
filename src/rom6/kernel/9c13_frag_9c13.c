/* ROM6 0x9C13 FRAG_9C13 -- 58w message-shape select + xor-fold + status store.
 * Verified encoding: src/rom6/kernel/9c13_frag_9c13.asm (recombine MATCH).
 * ORIGIN 0x9C13
 * EXPECT: F350 0020 F640 4917 F94D 9B5C 4816 08F8 20FE F845 9C21 4817 F845 9BDC F074 9C4D 6D8D 6D8D 6C83 9C2D 6D89 1291 F0E8 F0B0 F073 9C35 6D89 1091 F030 00FF 1191 F330 FF00 F2A0 E756 4A08 F274 9C61 7712 2F00 E900 8A0B F495 F2C0 7713 2F00 FB45 2C88 7714 009B 10F8 20FE F010 0004 76F8 20FA FFFF FC00
 *
 * Intent: Two entries: 9C13 (bc @9C0E) xors B with 32 then falls into
 * the 9C15 lane; 9C15 (4x external joins) starts with B live (ld b,a).
 * All regs caller-live dark (params, 8b9d precedent). A = B; B = AR7
 * (ldm); B == 0 runs msg_leaf_9B5C (cc beq; AR5/AR3/A/AR1 threaded per
 * its int**/int*/int/int** contract, mapping flagged). A = AR6 (ldm);
 * A -= cell 0x20FE; nonzero reloads A = AR7 and A == 0 tail-joins the
 * 9BDC lane inside FRAG_9BC3 (bc aeq; frag_9BDC forward extern,
 * interior @+0x19, 28d6 interior-join precedent). Zero (or the 9C21
 * skip) runs wrap_9C4D(AR2, AR4, AR6); AR5 -= 2; banz tests AR3 with
 * test-then-decrement (4ee0 precedent: if (ar3-- != 0)). Taken builds
 * A = (*AR1+ & 0xFF) | (*AR1+ & ~0xFF) (9C2D mask-merge lane, AR1 net
 * +1); not-taken builds A = (unsigned *AR1+) << 8 then A |= A >> 16
 * (sftl + OR_ACC_SHIFT, logical right per op_logical, exact for
 * non-negative 16-bit input; AR1 net unchanged). Join 9C35: AR6 = AR5;
 * push A-low (pshm); calld wrap_9C61 (delay stm #12032,ar2 runs first;
 * 9C61 redefines A dark -- 2e84 clobber convention: xor/ccd structure
 * exact, values flagged); B = 0 then B-low = popped word (B-high was
 * zero); A ^= B (xor); AR3 = 12032; AR4 = 155 (ccd delay, always runs);
 * A == 0 runs ring_report_2C88 (ccd aeq, 351d/a7eb delay convention);
 * A = cell 0x20FE - 4; cell 0x20FA = -1 (st); ret. Out cells/A/ARs;
 * B/TC dark. EXPECT from the image.
 */
extern void msg_leaf_9B5C(int **p5, int *p3, int a, int **p1);
extern void wrap_9C4D(int *ar2, int ar4_live, int ar6_live);
extern void wrap_9C61(void);
extern void ring_report_2C88(void);
extern void frag_9BDC(void); /* joins 9bc3_frag_9bc3 interior @+0x19 (0x9BDC) */

void lane_9C15(long b_in, int *ar1_in, int *ar2_in, int *ar3_in,
               int ar4_in, int *ar5_in, int ar6_in, int ar7_in);

void frag_9C13(long b_in, int *ar1_in, int *ar2_in, int *ar3_in,
               int ar4_in, int *ar5_in, int ar6_in, int ar7_in)
{
    long b = b_in;

    b ^= 32L;                                                /* xor #32,b */
    lane_9C15(b, ar1_in, ar2_in, ar3_in, ar4_in, ar5_in, ar6_in, ar7_in);
}

void lane_9C15(long b_in, int *ar1_in, int *ar2_in, int *ar3_in,
               int ar4_in, int *ar5_in, int ar6_in, int ar7_in)
{
    long a;
    long b = b_in;
    int *ar1 = ar1_in;
    int *ar2 = ar2_in;
    int *ar3 = ar3_in;
    int ar4 = ar4_in;
    int *ar5 = ar5_in;
    int ar6 = ar6_in;
    int ar7 = ar7_in;
    int stk;

    a = b;                                                   /* ld b,a */
    b = (long)ar7;                                           /* ldm ar7,b */
    if (b == 0)                                              /* cc 0x9b5c,beq */
        msg_leaf_9B5C(&ar5, ar3, (int)a, &ar1);
    a = (long)ar6;                                           /* ldm ar6,a */
    a -= (long)*(volatile int *)0x20FE;                      /* sub *(0x20fe),a */
    if (a != 0) {                                            /* bc 0x9c21,aeq not taken */
        a = (long)ar7;                                       /* ldm ar7,a */
        if (a == 0) {                                        /* bc 0x9bdc,aeq */
            frag_9BDC();                                     /* interior join (forward extern) */
            return;
        }
    }
    wrap_9C4D(ar2, ar4, ar6);                                /* call 0x9c4d */
    ar5--;                                                   /* mar *ar5- */
    ar5--;                                                   /* mar *ar5- */
    if (ar3-- != 0) {                                        /* banz 0x9c2d,*ar3 */
        ar1--;                                               /* mar *ar1- */
        a = (long)*ar1++;                                    /* ld *ar1+,a */
        a &= 0xFFL;                                          /* and #255,a */
        b = (long)*ar1++;                                    /* ld *ar1+,b */
        b &= -256L;                                          /* and #-256,b */
        a |= b;                                              /* or b,a */
    } else {
        ar1--;                                               /* mar *ar1- */
        a = (long)(unsigned)*ar1++;                          /* ldu *ar1+,a */
        a <<= 8;                                             /* sftl a,8 */
        a |= a >> 16;                                        /* or a,-16 (dst=A, logical) */
    }
    ar6 = (int)(long)ar5;                                 /* mvmm ar5,ar6 (address as value) */
    stk = (int)(a & 0xFFFFL);                                /* pshm al */
    ar2 = (int *)(long)12032;                                /* calld delay: stm #12032,ar2 */
    wrap_9C61();                                             /* calld 0x9c61 (A redefined dark) */
    b = 0L;                                                  /* ld #0,b */
    b = (long)(stk & 0xFFFF);                                /* popm bl (B-high was zero) */
    /* nop */
    a ^= b;           /* xor b,a (A-input clobber-dark per 9c61 header, flagged) */
    ar3 = (int *)(long)12032;                                /* stm #12032,ar3 */
    ar4 = 155;                                               /* ccd delay: stm #155,ar4 (always) */
    if (a == 0)                                              /* ccd 0x2c88,aeq */
        ring_report_2C88();
    a = (long)*(volatile int *)0x20FE;                       /* ld *(0x20fe),a */
    a -= 4L;                                                 /* sub #4,a */
    *(volatile int *)0x20FA = -1;                            /* st #-1,*(0x20fa) */
}
