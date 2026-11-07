/* ROM6 0x8F7A ROUTINE_8F7A -- 29w saturating quantize lane.
 * Verified encoding: src/rom6/kernel/8f7a_routine_8f7a.asm (recombine MATCH).
 * ORIGIN 0x8F7A
 * EXPECT: 771A 0007 F272 8F95 4482 9680 F485 4100 F84B 8F8D 4101 F84B 8F91 F063 FFFC F273 8F92 F57E 3F02 F273 8F92 F561 F495 3D00 FD30 F784 9600 CA80 FC00
 *
 * Intent: 8-sample saturate/quantize loop (RPTBD block
 * 8F7E-8F95, BRC = 7). Per sample: A = *AR2 << 16; TC =
 * bit0 of *AR2+ (AR2++); A = |A|; B = (mem(0x00) << 16) - A
 * (4-operand SUB per SPRU172); BC BLT to the second BD when
 * B < 0; else B = (mem(0x01) << 16) - A, BC BLT to the
 * ADD00 leg when B < 0; else A &= (-4) << 16 and take BD1:
 * its two delay words run (B = A >> 2, then B +=
 * mem(0x02) << 16) and branch to the XC. BD2 (BC1 target):
 * delays B = A << 1 + NOP, branch to XC. ADD00 (BC2
 * target): B = (mem(0x00) << 16) + A (4-operand ADD). XC:
 * TC-gated negate (TC from the head BIT; no interior TC
 * writer, flagged); TC = bit0 of *AR2; parallel store B-low
 * to *AR2 with LD A = *AR2+ (loaded A dead -- next pass LD
 * overwrites; the live effect is AR2++, flagged). Return.
 * (Wave-13: 4-operand SUB/ADD order corrected per SPRU172;
 * BD = 2 delay WORDS per the silicon rule, both modeled.)
 */
void routine_8F7A(void)
{
    long a;
    long b;
    int *ar2;  /* live-in (dark, flagged) */
    int tc;
    int i;

    /* stm #7,brc */
    for (i = 0; i < 8; i++) {                                  /* rptbd 0x8f95 */
        a = (long)*ar2 << 16;                                  /* ld *ar2,16,a */
        tc = *ar2++ & 1;                                       /* bit *ar2+,0 */
        if (a < 0)                                             /* abs a */
            a = -a;
        b = ((long)*(volatile int *)0x00 << 16) - a;           /* sub 0x00,16,a,b */
        if (b < 0)                                             /* bc 0x8f8d,blt */
            goto lbd2;
        b = ((long)*(volatile int *)0x01 << 16) - a;           /* sub 0x01,16,a,b */
        if (b < 0)                                             /* bc 0x8f91,blt */
            goto ladd00;
        a &= (long)-4 << 16;                                   /* and #-4,16,a */
        /* bd 0x8f92 (delay words run, then branch): */
        b = a >> 2;                                            /* sfta a,-2,b */
        b += (long)*(volatile int *)0x02 << 16;                /* add 0x02,16,b */
        goto lxc;
lbd2:
        /* bd 0x8f92 (delay words run, then branch): */
        b = a << 1;                                            /* sfta a,1,b */
        /* nop */
        goto lxc;
ladd00:
        b = ((long)*(volatile int *)0x00 << 16) + a;           /* add 0x00,16,a,b */
lxc:
        /* xc 1,tc (executes when TC) */
        if (tc)
            b = -b;                                            /* neg b */
        tc = *ar2 & 1;                                         /* bit *ar2,0 */
        *ar2 = (int)(b & 0xFFFFL);                             /* st b,*ar2 || ld *ar2+,a */
        a = (long)*ar2++;                                      /* (loaded A dead; AR2++ live, flagged) */
    }
    /* ret */
    (void)a; (void)b;
}
