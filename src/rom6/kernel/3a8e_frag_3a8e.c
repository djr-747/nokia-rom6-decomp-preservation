/* ROM6 0x3A8E FRAG_3A8E -- 40w.
 * Verified encoding: src/rom6/kernel/3a8e_frag_3a8e.asm (recombine MATCH).
 * ORIGIN 0x3A8E
 * EXPECT: 74F8 000B 003A F330 00FF F784 F300 00D4 F67C F030 000F 00F8 0012 8812 F330 000F 74F8 0008 003B F030 0FFF F784 771A 000E F072 3AAD FD4B F461 F300 0001 F495 F495 1192 7182 000C F2C0 828A 8082 E840 FC00
 *
 * Intent: Port-driven gain-ramp plus table tap. Ports are extern reads (PORTR writes Smem only per ti-c54x op_portr, so B is live-in, 0 on the 3A81 path). B = 212 - (B & 255); A = ((B >> 4) & 15) + cell 0x12 into AR2; B stays low nibble, negated. 15-iteration block (BRC = 14, rptb 0x3aad over xc/sfta/add/nop/nop): A doubles while B < 0 (xc 1,blt exact skip), B ticks up. Then B = *AR2++, cell 0xC = *AR2, A ^= B, 32-bit A stored across AR2/AR2-1 (STH high word src(31:16) per ti-c54x op_sth, low word STL), A = 64, return. 40-bit accumulator shifts noted where the int model narrows.
 */
extern int port_read_58(void);                                        /* HW port 58 (per 3a8e span); no ROM definition */
extern int port_read_59(void);                                        /* HW port 59 (per 3a8e span); no ROM definition */

int frag_3A8E(void)
{
    int a, b;
    int *ar2;
    int i;
    /* portr 58,*(0xb): DATA 0xB aliases BL, so B-low = port value
       (ti-c54x PORTR = Smem write; the accumulator half follows
       the MMR alias, confirmed by the 3ADE poll loop). */
    b = port_read_58();
    *(volatile int *)0xB = b;
    b = 212 - (b & 255);                         /* and #255, neg, add */
    a = (b >> 4) & 15;                           /* sfta b,-4,a; and #15,a */
    a += *(volatile int *)0x12;              /* add *(0x12),a */
    ar2 = (int *)a;                              /* stlm a,ar2 */
    b = -(b & 15);                               /* and #15,b; neg b */
    /* portr 59,*(0x8): DATA 0x8 aliases AL, so A-low = port value
       (A-high preserved until the mask below clears it). */
    a = (a & ~0xFFFF) | port_read_59();
    *(volatile int *)0x8 = a;
    a &= 4095;                                   /* and #4095,a */
    for (i = 0; i < 15; i++) {                   /* stm #14,brc; rptb */
        if (b < 0)                               /* xc 1,blt */
            a <<= 1;                             /* sfta a,1 (40-bit) */
        b += 1;                                  /* add #1,b; nop; nop */
    }
    b = *ar2++;                                 /* ld *ar2+,b */
    *(volatile int *)0xC = *ar2;             /* mvdk *ar2,0xc */
    a ^= b;                                      /* xor b,a */
    *ar2 = (a >> 16) & 0xFFFF; ar2--;            /* sth a,*ar2- */
    *ar2 = a & 0xFFFF;                           /* stl a,*ar2 */
    return 64;                                   /* ld #64,a; ret */
}
