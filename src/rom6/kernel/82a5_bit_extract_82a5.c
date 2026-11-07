/* ROM6 0x82A5 BIT_EXTRACT_82A5 -- 16w.
 * Verified encoding: src/rom6/kernel/82a5_bit_extract_82a5.asm (recombine MATCH).
 * ORIGIN 0x82A5
 * EXPECT: 4582 448A 1B92 F2C2 F2C3 F2C5 F2C6 8294 448A F2C1 F2C4 F2C6 FD30 8294 F2C2 FE00
 *
 * Intent: XOR bit-extract pair. B = (cellAR2 << 16); A =
 * (cellAR2 << 16), AR2--; B |= cellAR2, AR2++ (net AR2 unchanged
 * here); A ^= B<<2, B<<3, B<<5, B<<6 accumulating (XOR_ACC_SHIFT:
 * dst ^= shifted src, logical shifts per the oracle leaf; 32-bit
 * unsigned wrap is exact for the observed low 32 bits -- high
 * bits 32-39 never stored, flagged); store A-high, AR4++;
 * A reloaded, ^= B<<1, B<<4, B<<6; TC-live set stores A-high
 * (xc 1,tc covers the single sth, per ti-c54x op_xc); A ^= B<<2;
 * retd with delays in the next span (always run there, flagged).
 * TC caller-live (no in-span writer). AR2/AR4 caller-live,
 * dead at return. Bound 82A5-82B4.
 */
void bit_extract_82A5(int *ar2_in, int *ar4_in, int tc_live)
{
    int *ar2 = ar2_in;
    int *ar4 = ar4_in;
    long a;
    long b;
    int tc = tc_live;
    b = (long)((unsigned long)(unsigned)*ar2 << 16); /* ld *ar2,16,b */
    a = (long)((unsigned long)(unsigned)*ar2 << 16); /* ld *ar2-,16,a */
    ar2--;
    b |= (long)*ar2;                                 /* or *ar2+,b */
    ar2++;
    a = (long)((unsigned long)a ^ ((unsigned long)b << 2));  /* xor b,2,a */
    a = (long)((unsigned long)a ^ ((unsigned long)b << 3));  /* xor b,3,a */
    a = (long)((unsigned long)a ^ ((unsigned long)b << 5));  /* xor b,5,a */
    a = (long)((unsigned long)a ^ ((unsigned long)b << 6));  /* xor b,6,a */
    *ar4++ = (int)((a >> 16) & 0xFFFF);              /* sth a,*ar4+ */
    a = (long)((unsigned long)(unsigned)*ar2 << 16); /* ld *ar2-,16,a */
    ar2--;
    a = (long)((unsigned long)a ^ ((unsigned long)b << 1));  /* xor b,1,a */
    a = (long)((unsigned long)a ^ ((unsigned long)b << 4));  /* xor b,4,a */
    a = (long)((unsigned long)a ^ ((unsigned long)b << 6));  /* xor b,6,a */
    if (tc)                                          /* xc 1,tc (taken runs sth) */
        *ar4++ = (int)((a >> 16) & 0xFFFF);          /* sth a,*ar4+ */
    a = (long)((unsigned long)a ^ ((unsigned long)b << 2));  /* xor b,2,a */
    /* retd (delays in next span, always run there) */
    (void)a; (void)b;                                /* A/B dead at return (flagged) */
}
