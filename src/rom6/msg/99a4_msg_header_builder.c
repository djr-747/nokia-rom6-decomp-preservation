/* ROM6 0x99A4 MSG_HEADER_BUILDER -- 66w.
 * Verified encoding: src/rom6/msg/99a4_msg_header_builder.asm (recombine MATCH).
 * ORIGIN 0x99A4
 * EXPECT: F074 05CC FC4B 8814 10F8 21FD 08F8 21FC F495 F495 FF47 F000 00FA F400 F620 F010 0009 FC47 4814 61F8 0008 FF00 F830 99C4 61F8 20FF 0002 F040 1C00 FF20 F040 1E00 8915 80D3 F540 4910 81D3 F2C0 4915 81D3 F2C0 F3FF F310 0001 891A F84B 99D8 F072 99D7 1192 F2C0 81D3 4915 F330 0001 F84D 99E2 1192 F330 FF00 F2C0 81D3 80D3 FE00 7313 21FC
 *
 * Intent: uplink message builder with XOR checksum. Header word from
 * the length delta (0x21FD - 0x21FC), bias+double when nonpositive,
 * minus B and 9, restored from the AR4 save when still nonpositive.
 * Flag select: high byte of cell 0x8 set skips to the store lane;
 * else OR 7168 or 7680 by status bit 2. Store lane emits A, AR0 and
 * the saved B with pairwise XOR folding, then a repeat-block XOR
 * checksum over BRC+1 source words, an odd-tail word when the saved
 * B is odd, the final accumulator, and writes the end pointer back
 * to 0x21FC in the return delay slot. rc/xc prefixes are
 * conditional-single wrappers (exact skip semantics in the .asm).
 */
extern int helper_05CC(void);   /* returns A in the accumulator */

void msg_header_builder_99A4(int **pp2, int **pp3, int b_in)
{
    int a, b = b_in, saved_a = 0, saved_b;
    a = helper_05CC();                            /* call 0x5cc */
    if (b < 0)                                   /* rc blt */
        saved_a = a;                             /* stlm a,ar4 */
    a = *(volatile int *)0x21FD -
        *(volatile int *)0x21FC;                /* ld, sub */
    if (a <= 0) {                                /* xc 2,aleq */
        a += 250;                                /* add #250,a */
        a += a;                                  /* add a */
    }
    a -= b;                                      /* sub b,a */
    a -= 9;                                      /* sub #9,a */
    if (a <= 0)                                  /* rc aleq */
        a = saved_a;                             /* ldm ar4,a */
    if (!(*(volatile int *)0x8 & 0xFF00)) {       /* bitf, bc 99C4 */
        if (*(volatile int *)0x20FF & 2)         /* bitf #2 */
            a |= 7680;                           /* xc 2,ntc taken */
        else
            a |= 7168;                           /* or #7168 */
    }
L_99C4:                                          /* store lane */
    saved_b = b;                                 /* stlm b,ar5 */
    *(*pp3)++ = a;                               /* stl a,*ar3+% */
    b = a;                                       /* ld a,b */
    { int ar0v = 0; b = ar0v; }                  /* ldm ar0,b */
    *(*pp3)++ = b;                               /* stl b,*ar3+% */
    a ^= b;                                      /* xor b,a */
    b = saved_b;                                 /* ldm ar5,b */
    *(*pp3)++ = b;                               /* stl b,*ar3+% */
    a ^= b;                                      /* xor b,a */
    {
        int n, i;
        b >>= 1;    /* sftl b,-1: arithmetic right shift on C54x;
                     * matches here for the nonneg counts that loop */
        n = b - 1;                               /* sub #1, stlm brc */
        if (n >= 0) {                            /* bc 99D8 blt */
            for (i = 0; i <= n; i++) {           /* rptb 99D7 */
                b = *(*pp2)++;                   /* ld *ar2+,b */
                a ^= b;                          /* xor b,a */
                *(*pp3)++ = b;                   /* stl b,*ar3+% */
            }
        }
    }
    b = saved_b;                                 /* 99D8: ldm ar5,b */
    if (!(b & 1))                                /* and #1, bc 99E2 */
        goto L_99E2;
    b = *(*pp2)++;                               /* ld *ar2+,b */
    b &= 0xFF00;                                 /* and #-256,b */
    a ^= b;                                      /* xor b,a */
    *(*pp3)++ = b;                               /* stl b,*ar3+% */
L_99E2:
    *(*pp3)++ = a;                               /* stl a; retd */
    *(volatile int *)0x21FC = (int)*pp3;         /* delay: mvmd ar3 */
}
