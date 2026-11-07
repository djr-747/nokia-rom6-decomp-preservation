/* ROM6 ORIGIN 0x4B2C (59w): SUB_4B2C -- sample-pack lanes with shifted stores.
 * Verified encoding: src/rom6/kernel/4b2c_sub_4b2c.asm (recombine MATCH).
 * EXPECT: F074 059E 7714 0060 F020 B0FC 00F8 250B 8814 1182 9993 45E2 0001 1B92 9B93 45E2 0001 1B92 9B93 45E2 0001 1B92 F763 F363 1FFF 4484 F063 E000 F1C0 1084 F030 007F 8393 E529 45E2 0001 1B92 F77D F337 FFFF F064 007F F1C0 8193 771A 0002 F072 4B60 45E2 0001 1B92 F77D 8193 F363 0001 F360 FFF0 8393 FC00
 *
 * Intent: dark head call 0x059E. AR4 = (-20228 + cell 0x250B)-low
 * (stlm). B = *AR2 (ld). *AR3++ = (B << 3)[15:0] (stl b,3: logical
 * left per the oracle stl_shft leaf, exact in 32-bit C). Three
 * pack lanes, each B = (AR2[1] << 16) | *AR2++ (ld long-offset plus
 * or-with-post-inc; Smem OR zero-extends per op_or_smem): lanes 1-2
 * store *AR3++ = (B arith>>13)>>16 (sth b,3: STH_SHFT_XMEM leaf =
 * arith>> (16-3), bits 31-16; exact for sign-extended 40-bit values,
 * flagged). Lane 3: B <<= 3 (sfta, unsigned-long shift exact: B < 2^33
 * rides 40-bit clean); B &= 8191<<16 (and #8191,16,b); A = *AR4<<16;
 * A &= (-8192)<<16 (and #-8192,16,a; low-32 exact, high sign kept);
 * B ^= A; A = *AR4; A &= 127; *AR3++ = (B>>16) (sth, high exact);
 * *AR3++ = *AR4 (mvdd, no step on source). Next B built the same way;
 * B arith>>= 3 (sfta); B &= -128 (and #-1,7,b: mask (-1)<<7); A |=
 * 127<<16 (or #127,16,a on the retained A&127); B ^= A;
 * *AR3++ = B-low (stl). BRC = 2; rptb 0x4B60: RSA = 0x4B5C,
 * REA = 0x4B60, block inclusive (oracle repeat_block.c), 3 passes of
 * the same build/shift/store kernel. Post: B &= 1<<16; B += (-16)<<16;
 * *AR3++ = (B>>16). Ret. AR2 +7 / AR3 +9 in HW (local walks, caller
 * live-outs flagged); AR4 set in-span; A/B internal; TC untouched.
 * Bound 4B2C-4B66 (abuts 4B67).
 */
extern void sub_059E(void);

void sub_4B2C(int *ar2_in, int *ar3_in)
{
    long a;
    long b;
    int i;
    int *ar2 = ar2_in;
    int *ar3 = ar3_in;
    int *ar4;

    sub_059E();                                        /* call 0x59e (dark) */
    ar4 = (int *)0x60;                                 /* stm #96,ar4 */
    a = -20228L + (long)*(volatile int *)0x250B;       /* ld/add */
    ar4 = (int *)(int)(a & 0xFFFF);                    /* stlm a,ar4 */
    b = (long)*ar2;                                    /* ld *ar2,b */
    *ar3++ = (int)(((unsigned long)b << 3) & 0xFFFF);  /* stl b,3,*ar3+ */
    /* lanes 1-2 */
    for (i = 0; i < 2; i++) {
        b = (long)ar2[1] << 16;                        /* ld *ar2(0x1),16,b */
        b |= (long)(unsigned)*ar2++;                   /* or *ar2+,b */
        *ar3++ = (int)(((unsigned long)(b >> 13) >> 16) & 0xFFFF);
                                                       /* sth b,3,*ar3+ */
    }
    /* lane 3 */
    b = (long)ar2[1] << 16;                            /* ld *ar2(0x1),16,b */
    b |= (long)(unsigned)*ar2++;                       /* or *ar2+,b */
    b = (long)((unsigned long)b << 3);                 /* sfta b,3 */
    b &= 8191L << 16;                                  /* and #8191,16,b */
    a = (long)*ar4 << 16;                              /* ld *ar4,16,a */
    a &= -8192L << 16;                                 /* and #-8192,16,a */
    b ^= a;                                            /* xor a,b */
    a = (long)*ar4;                                    /* ld *ar4,a */
    a &= 127L;                                         /* and #127,a */
    *ar3++ = (int)(((unsigned long)b >> 16) & 0xFFFF); /* sth b,*ar3+ */
    *ar3++ = *ar4;                                     /* mvdd *ar4,*ar3+ */
    b = (long)ar2[1] << 16;                            /* ld *ar2(0x1),16,b */
    b |= (long)(unsigned)*ar2++;                       /* or *ar2+,b */
    b >>= 3;                                           /* sfta b,-3 (arith) */
    b &= -128L;                                        /* and #-1,7,b */
    a |= 127L << 16;                                   /* or #127,16,a */
    b ^= a;                                            /* xor a,b */
    *ar3++ = (int)(b & 0xFFFF);                        /* stl b,*ar3+ */
    /* stm #2,brc; rptb 0x4b60: [0x4b5c,0x4b60] inclusive, 3 passes */
    for (i = 0; i < 3; i++) {
        b = (long)ar2[1] << 16;                        /* ld *ar2(0x1),16,b */
        b |= (long)(unsigned)*ar2++;                   /* or *ar2+,b */
        b >>= 3;                                       /* sfta b,-3 (arith) */
        *ar3++ = (int)(b & 0xFFFF);                    /* stl b,*ar3+ */
    }
    b &= 1L << 16;                                     /* and #1,16,b */
    b += -16L << 16;                                   /* add #-16,16,b */
    *ar3++ = (int)(((unsigned long)b >> 16) & 0xFFFF); /* sth b,*ar3+ */
    /* ret */
}
