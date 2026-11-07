/* ROM6 0x5434 DISPATCH_P_LANES -- 22w.
 * Verified encoding: src/rom6/rf/5434_dispatch_p_lanes.asm (recombine MATCH).
 * ORIGIN 0x5434
 * EXPECT: F074 06E4 60F8 0573 A249 F830 5446 771A 0277 E800 F272 5442 7711 2C00 8091 E904 F074 B4A8 F074 C717 F073 54BB
 *
 * Intent: P-lane dispatch fragment (5395-family; all lanes converge
 * on 54BB). Runs dark SUB_06E4 (forward extern void; no symbol,
 * opaque). TC = (*(0x573) == -23991) (cmpm Smem,#lk, 3691 precedent;
 * signed-cell compare, flagged). TC set skips the zero-fill and the
 * B4A8 call (bc 0x5446,tc lands mid-span on the c717 call word).
 * Else: AR1 = 11264 (stm, runs once as the rptbd delay); BRC = 631
 * (folded); 632 passes over stl + ld (rptbd block 5441-5442 per the
 * RPTBD PC+4 convention, d5ca groundwork): MEM[*AR1++] = 0 (stl a
 * with A = 0 from ld #0,a), B = 4 (ld #4,b, idempotent). Then runs
 * pooled ROUTINE_B4A8 and INIT_FILTER_C717 (forward externs void;
 * B = 4 and AR1-out entry-live through both, opaque, flagged).
 * Tails into the 5489 span at 54BB (b 0x54bb; mid-span entry,
 * msg_producer_converge_54BB per the 5301 precedent).
 */
extern void sub_06E4(void);                          /* dark, no symbol */
extern void routine_B4A8(void);                      /* pooled */
extern void init_filter_C717(void);                  /* pooled */
extern void msg_producer_converge_54BB(void);        /* mid-span entry */

void frag_5434(void)
{
    long a = 0;                                      /* ld #0,a */
    int b;
    int *ar1;
    int pass;
    sub_06E4();                                      /* call 0x6e4 */
    if (*(volatile int *)0x573 == -23991) {          /* cmpm; bc 0x5446,tc */
        init_filter_C717();                          /* 5446: the c717 call */
        msg_producer_converge_54BB();                /* b 0x54bb */
        return;
    }
    ar1 = (int *)(long)11264;                        /* stm #11264,ar1 (delay, once) */
    /* stm #631,brc (folded); rptbd 0x5442 */
    for (pass = 0; pass < 632; pass++) {             /* rptbd block 5441-5442 */
        *ar1++ = (int)(a & 0xFFFFL);                 /* stl a,*ar1+ */
        b = 4;                                       /* ld #4,b */
    }
    (void)b;                                         /* B = 4 across the pooled calls (opaque) */
    (void)ar1;                                       /* AR1-out, caller-observable, not carried */
    routine_B4A8();                                  /* call 0xb4a8 */
    init_filter_C717();                              /* call 0xc717 */
    msg_producer_converge_54BB();                    /* b 0x54bb */
}
