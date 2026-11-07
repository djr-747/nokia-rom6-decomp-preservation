/* ROM6 ORIGIN 0x505B (87w): FRAG_505B -- 7-lane sample packer.
 * Verified encoding: src/rom6/kernel/505b_frag_505b.asm (recombine MATCH).
 * EXPECT: 1092 F030 7FFF 1192 F330 FFF8 7182 000C 68F8 000C 0003 F3EC F2A0 8093 F470 1192 F330 FFC0 7182 000C 68F8 000C 001F F3E8 F2A0 8093 F0F0 1192 F330 FE00 7182 000C 68F8 000C 00FF F3E4 F2A0 8093 F0F0 1192 F330 F000 7182 000C 68F8 000C 07FF F2A0 8093 F0F0 1192 F330 8000 7192 000C 68F8 000C 3FFF F3FC F2A0 8093 F0F0 1192 F330 FFFC 7182 000C 68F8 000C 0001 F3E8 F2A0 8093 F0F0 1192 F330 FFE0 7182 000C 68F8 000C 000F F3E4 F2A0 FE00 8093 8293
 *
 * Intent: seven straight-line pack lanes. Each lane: A = *AR2++ masked,
 * B = *AR2++ masked, cell 0xC = *AR2 (masked; lane 5 post-incs AR2),
 * B barrel-shifted (sftl, logical both directions), A |= B,
 * *AR3++ = A-low (stl), A arith>>= 16 (sfta; separator into the next
 * lane's OR). Lane masks/shifts: (32767; -8; 3; <<12), (-64; 31; <<8),
 * (-512; 255; <<4), (-4096; 2047; none), (-32768; 16383; >>4),
 * (-4; 1; <<8), (-32; 15; <<4). retd with delays *AR3++ = A-low (stl)
 * then *AR3++ = A-high (sth), then return. 40-bit exactness: every
 * sftl source fits with bit39 == bit31 (lane values < 2^29 with
 * consistent sign; << drops only zero/sign bits), so 32-bit C shifts
 * match; OR/STL/STH are low-word exact. A/B internal; AR2 +16 / AR3 +8
 * in HW (local walks, caller live-outs flagged); TC untouched.
 * Bound 505B-50B1 (abuts 50B2).
 */
void frag_505B(int *ar2_in, int *ar3_in)
{
    long a;
    long b;
    int *ar2 = ar2_in;
    int *ar3 = ar3_in;

    a = (long)*ar2++;                                  /* ld *ar2+,a */
    a &= 32767L;                                       /* and #32767,a */
    b = (long)*ar2++;                                  /* ld *ar2+,b */
    b &= -8L;                                          /* and #-8,b */
    *(volatile int *)0xC = *ar2;                       /* mvdk *ar2,0xc */
    *(volatile int *)0xC &= 3;                         /* andm #3 */
    b = (long)((unsigned long)b << 12);                /* sftl b,12 */
    a |= b;                                            /* or b,a */
    *ar3++ = (int)(a & 0xFFFF);                        /* stl a,*ar3+ */
    a >>= 16;                                          /* sfta a,-16 (arith) */
    b = (long)*ar2++;                                  /* ld *ar2+,b */
    b &= -64L;                                         /* and #-64,b */
    *(volatile int *)0xC = *ar2;
    *(volatile int *)0xC &= 31;
    b = (long)((unsigned long)b << 8);                 /* sftl b,8 */
    a |= b;
    *ar3++ = (int)(a & 0xFFFF);
    a >>= 16;
    b = (long)*ar2++;
    b &= -512L;                                        /* and #-512,b */
    *(volatile int *)0xC = *ar2;
    *(volatile int *)0xC &= 255;
    b = (long)((unsigned long)b << 4);                 /* sftl b,4 */
    a |= b;
    *ar3++ = (int)(a & 0xFFFF);
    a >>= 16;
    b = (long)*ar2++;
    b &= -4096L;                                       /* and #-4096,b */
    *(volatile int *)0xC = *ar2;
    *(volatile int *)0xC &= 2047;
    a |= b;                                            /* or (no shift) */
    *ar3++ = (int)(a & 0xFFFF);
    a >>= 16;
    b = (long)*ar2++;
    b &= -32768L;                                      /* and #-32768,b */
    *(volatile int *)0xC = *ar2++;                     /* mvdk *ar2+,0xc */
    *(volatile int *)0xC &= 16383;
    b >>= 4;                                           /* sftl b,-4 (arith) */
    a |= b;
    *ar3++ = (int)(a & 0xFFFF);
    a >>= 16;
    b = (long)*ar2++;
    b &= -4L;                                          /* and #-4,b */
    *(volatile int *)0xC = *ar2;
    *(volatile int *)0xC &= 1;
    b = (long)((unsigned long)b << 8);                 /* sftl b,8 */
    a |= b;
    *ar3++ = (int)(a & 0xFFFF);
    a >>= 16;
    b = (long)*ar2++;
    b &= -32L;                                         /* and #-32,b */
    *(volatile int *)0xC = *ar2;
    *(volatile int *)0xC &= 15;
    b = (long)((unsigned long)b << 4);                 /* sftl b,4 */
    a |= b;                                            /* or b,a */
    /* retd (delays run, then return) */
    *ar3++ = (int)(a & 0xFFFF);                        /* stl a,*ar3+ */
    *ar3++ = (int)(((unsigned long)a >> 16) & 0xFFFF); /* sth a,*ar3+ */
    /* retd: return */
}
