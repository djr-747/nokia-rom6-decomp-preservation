/* ROM6 0x89C4 ROUTINE_89C4 -- 39w scaled-store sequencer.
 * Verified encoding: src/rom6/kernel/89c4_routine_89c4.asm (recombine MATCH).
 * ORIGIN 0x89C4
 * EXPECT: F074 0592 7710 0002 7711 10FC 7712 3098 7715 0003 7713 0000 770E 0028 8C92 7692 0000 F074 89F4 F063 0003 82B2 7714 000C F074 89F4 770E 0006 F063 7FFF F48C F00F 0001 9A81 6C8C 89DC 6C8D 89EB FC00
 *
 * Intent: Calls sub_0592 (low-zone unsourced, flagged); AR0 =
 * 2, AR1 = 4348, AR2 = 12440, AR5 = 3, AR3 = 0, T = 40 (outs
 * for AR0/AR1/AR3, flagged); *(12440) = T, *(12441) = 0;
 * calls ROUTINE_89F4; A &= 3<<16 (and #3,16: A & (lk<<SHFT)
 * per oracle op_logical_immediate); *(12442) = A-high (sth,
 * ASM dark, flagged); AR4 = 12; 12x inner lane (banz
 * 0x89dc,*ar4-): call ROUTINE_89F4, T = 6, A &= 32767<<16,
 * A = T x A-high (mpya a, FRCT doubling + OVM flagged),
 * A += 1<<15, *(AR2++) = bits 31-16 of A<<1 (sth a,1, 25F2
 * precedent). Then AR5-- (banz 0x89eb,*ar5-): nonzero exits
 * forward to 89EB (next span owns; AR5 = 2 live-out, and the
 * span ret below is unreachable with AR5 = 3); zero would
 * return. A defined by ROUTINE_89F4 (dark, flagged); stores
 * cover cells 12440-12454; out AR2 = 12454, AR4 = 0.
 * EXPECT from the image.
 */
void routine_89C4(void)
{
    long a;  /* defined by ROUTINE_89F4 (dark, flagged) */
    int *ar2;
    int *ar4;
    int *ar5;
    int t;
    int i;

    sub_0592();                                              /* call 0x592 (low-zone, flagged) */
    /* stm #2,ar0; stm #4348,ar1; stm #0,ar3 (outs, flagged) */
    ar2 = (int *)12440;                                      /* stm #12440,ar2 */
    ar5 = (int *)3;                                          /* stm #3,ar5 */
    t = 40;                                                  /* stm #40,t */
    *ar2++ = t;                                              /* st t,*ar2+ */
    *ar2++ = 0;                                              /* st #0,*ar2+ */
    routine_89F4();                                          /* call 0x89f4 */
    a &= 0x30000L;                                           /* and #3,16,a (oracle immediate) */
    *ar2 = (int)((a >> 16) & 0xFFFFL);                       /* sth a,*ar2+0 (ASM dark, flagged) */
    ar4 = (int *)12;                                         /* stm #12,ar4 */
    for (i = 0; i < 12; i++) {                               /* banz 0x89dc,*ar4- */
        routine_89F4();                                      /* call 0x89f4 */
        t = 6;                                               /* stm #6,t */
        a &= 0x7FFF0000L;                                    /* and #32767,16,a */
        a = (long)t * ((a >> 16) & 0xFFFFL);                 /* mpya a (FRCT/OVM flagged) */
        a += 0x8000L;                                        /* add #1,15,a */
        *ar2++ = (int)(((a << 1) >> 16) & 0xFFFFL);          /* sth a,1,*ar2+ */
    }
    ar5--;                                                   /* banz 0x89eb,*ar5- */
    if (ar5 != 0)                                            /* (taken: AR5 = 2 live-out) */
        return;                                              /* 89eb (next span owns) */
    /* ret (unreachable with AR5 = 3) */
}
