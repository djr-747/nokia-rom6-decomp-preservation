/* ROM6 0x2ACC FRAG_2ACC -- 48w.
 * Verified encoding: src/rom6/boot/2acc_frag_2acc.asm (recombine MATCH).
 * ORIGIN 0x2ACC
 * EXPECT: 7212 265E 7213 2660 6182 0004 F830 2AE6 11F8 3E81 0983 74F8 0008 000C 1AF8 3ECD F84D 2AE2 11F8 3ECD F793 F280 F495 75F8 0008 000C F495 7592 0030 F495 F495 7592 0004 EC16 F495 F495 7593 0031 F495 F495 7593 0032 7312 265E 7313 2660 F073 283D
 *
 * Intent: Masked RF-port program. AR2/AR3 cursor pair from cells 0x265E/0x2660 (mvdm, locals); bit 2 (4) of *AR2 set skips the whole sample block to the in-span nop at 0x2AE6 (bc tc, rejoins). Else B = *(0x3E81) - *AR3 (ld/sub: SUB Smem,src per op_sub, B full rate); A = port 12 (portr 12,*(0x8): AL alias) OR *(0x3ECD), A live-in accumulates, Z from A; A == 0 skips only the complement mask via the in-span nop at 0x2AE2 (bc beq, rejoins at the port-12 write of the un-ORed alias value). Mask: B = *(0x3ECD), B = ~B (cmpl: full-40-bit NOT per ti-c54x op_cmpl.c:44-45, C/TC preserved; low16 exact, A high/guard kept by the AND), A &= B. Port 12 = A via alias; *AR2++ to ports 48 then 4; 23 idle cycles (rpt #22 nop); *AR3++ block to ports 49 then 50; cursors saved back to cells; tail-enters dark 0x283D (b, forward extern). Ports 4/12/48/49/50 direct-mapped (extern ops). Bound 2ACC-2AFB.
 */
extern int port_read_12(void);
extern void port_write_12(int v);
extern void port_write_48(int v);
extern void port_write_4(int v);
extern void port_write_49(int v);
extern void port_write_50(int v);
extern void frag_283D(void);

void frag_2ACC(int a_live)
{
    int a = a_live;
    int b;
    int *ar2 = (int *)(long)*(volatile int *)0x265E; /* mvdm */
    int *ar3 = (int *)(long)*(volatile int *)0x2660; /* mvdm */
    if ((*ar2 & 4) != 0) {                         /* bitf *ar2,#4 */
        goto l2ae6;                                /* bc 0x2ae6,tc */
    }
    b = *(volatile int *)0x3E81;               /* ld *(0x3e81),b */
    b -= *ar3;                                     /* sub *ar3,b */
    a = port_read_12();                            /* portr 12,*(0x8) */
    *(volatile int *)0x8 = a;                  /* AL alias write */
    a |= (unsigned short)*(volatile int *)0x3ECD; /* or *(0x3ecd),a (Smem zero-ext) */
    if (a != 0) {                                  /* bc 0x2ae2,beq skips mask */
        b = *(volatile int *)0x3ECD;           /* ld *(0x3ecd),b */
        b = ~b & 0xFFFF;                           /* cmpl b: NOT, low16 exact */
        a &= b;                                    /* and b,a */
    }
/* l2ae2: beq rejoin */
    *(volatile int *)0x8 = a;                  /* AL alias write */
    /* nop */
    port_write_12(a);                              /* portw *(0x8),12 */
l2ae6:
    /* nop @2AE6 (tc rejoin) */
    port_write_48(*ar2++);                         /* portw *ar2+,48 */
    /* nop; nop */
    port_write_4(*ar2++);                          /* portw *ar2+,4 */
    /* rpt #22 nop: 23 idle cycles */
    /* nop; nop */
    port_write_49(*ar3++);                         /* portw *ar3+,49 */
    /* nop; nop */
    port_write_50(*ar3++);                         /* portw *ar3+,50 */
    *(volatile int *)0x265E = (int)(long)ar2;  /* mvmd ar2 */
    *(volatile int *)0x2660 = (int)(long)ar3;  /* mvmd ar3 */
    frag_283D();                                   /* b 0x283d tail */
}
