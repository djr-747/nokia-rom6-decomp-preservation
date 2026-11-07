/* ROM6 0x55D7 MSG_PRODUCER_CONVERGE_55D7 -- 24w.
 * Verified encoding: src/rom6/msg/55d7_msg_producer_converge.asm (recombine MATCH).
 * ORIGIN 0x55D7
 * EXPECT: 770E 000F 3481 E80C E919 FF30 E819 E90C 81F8 2652 80F8 2653 4481 770E 000D F48C 80F8 2651 F000 000C 80F8 2640 F073 5683
 *
 * Intent: T-scaled swap store. T = 15; bit 15 of *AR1-live-in set swaps the (12,25) pair into (A,B) = (25,12) (ld pair plus xc 2,tc; TC from bitt). Stores B then A to cells 0x2652/0x2653. A = *AR1 << 16; T = 13; A = T times A-high (mpya a, register-only dst per ti-c54x op_mpya_dst: A = 13 x cell); stores A to 0x2651, A += 12 stored to 0x2640; tail-enters 0x5683 (b, C: frag_5683 this turn). 24w per .asm header (recombine MATCH).
 */
extern void frag_5683(void);

void frag_55D7(int *par1)
{
    int a;
    int b;
    int t;
    int cell;
    t = 15;                                      /* stm #15,t */
    /* bitt *ar1: TC = bit 15 of cell */
    a = 12;                                      /* ld #12,a */
    b = 25;                                      /* ld #25,b */
    cell = *par1;
    if (((cell >> 15) & 1) != 0) {                /* xc 2,tc */
        a = 25;                                  /* ld #25,a */
        b = 12;                                  /* ld #12,b */
    }
    *(volatile int *)0x2652 = b;             /* stl b */
    *(volatile int *)0x2653 = a;             /* stl a */
    a = cell << 16;                              /* ld *ar1,16,a */
    t = 13;                                      /* stm #13,t */
    a = (long)t * (a >> 16);                     /* mpya a (A = T x A-high) */
    *(volatile int *)0x2651 = a;             /* stl a */
    a += 12;                                     /* add #12,a */
    *(volatile int *)0x2640 = a;             /* stl a */
    frag_5683();                                 /* b 0x5683 tail */
}
