/* ROM6 0x55B1 MSG_PRODUCER_CONVERGE_55B1 -- 38w.
 * Verified encoding: src/rom6/msg/55b1_msg_producer_converge.asm (recombine MATCH).
 * ORIGIN 0x55B1
 * EXPECT: 60F8 250F 002F F830 55D7 E801 18F8 250F 80F8 2EF8 60F8 2EF8 0001 E80C E919 FF30 E819 E90C 81F8 2652 80F8 2653 4481 F063 FFFE 3CF8 2EF8 770E 000D F48C 80F8 2651 F000 000C 80F8 2640 F073 5683
 *
 * Intent: Flag-driven swap store. Cell 0x250F == 47 tail-enters 0x55D7 (bc tc, C: frag_55D7 with AR1 passthrough). Cell 0x2EF8 = 1 AND cell 0x250F (ld plus and, stored); its == 1 sets TC (cmpm, TC live into the xc). Same swap-store block as 55D7, then A = *AR1 << 16 with bit 16 cleared (and #-2,16,a: A AND (-2)<<16) plus cell 0x2EF8 << 16 (add); T = 13; A = 13 times A-high (mpya a per op_mpya_dst); stores to 0x2651, A += 12 to 0x2640; tail-enters 0x5683 (b, C: frag_5683). 38w per .asm header (recombine MATCH).
 */
extern void frag_55D7(int *par1);
extern void frag_5683(void);

void frag_55B1(int *par1)
{
    int a;
    int b;
    int t;
    int cell;
    int c2ef8;
    if (*(volatile int *)0x250F == 47) {         /* cmpm, bc tc */
        frag_55D7(par1);                         /* tail call */
        return;
    }
    a = 1 & (unsigned short)*(volatile int *)0x250F; /* ld #1,a; and (Smem zero-ext) */
    *(volatile int *)0x2EF8 = a;             /* stl a */
    c2ef8 = a;
    /* cmpm *(0x2ef8),#1 (TC = (cell == 1), live into xc) */
    a = 12;                                      /* ld #12,a */
    b = 25;                                      /* ld #25,b */
    if (c2ef8 == 1) {                            /* xc 2,tc */
        a = 25;
        b = 12;
    }
    *(volatile int *)0x2652 = b;
    *(volatile int *)0x2653 = a;
    cell = *par1;
    a = (long)cell << 16;                        /* ld *ar1,16,a */
    a &= (long)-2 << 16;                         /* and #-2,16,a */
    a += (long)c2ef8 << 16;                      /* add *(0x2ef8),16,a */
    t = 13;                                      /* stm #13,t */
    a = (long)t * (a >> 16);                     /* mpya a (A = T x A-high) */
    *(volatile int *)0x2651 = a;
    a += 12;                                     /* add #12,a */
    *(volatile int *)0x2640 = a;
    frag_5683();                                 /* b 0x5683 tail */
}
