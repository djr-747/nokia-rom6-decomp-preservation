/* ROM6 0x7EA7 BIT_MERGE_7EA7 -- 11w.
 * Verified encoding: src/rom6/kernel/7ea7_bit_merge_7ea7.asm (recombine MATCH).
 * ORIGIN 0x7EA7
 * EXPECT: 448A F540 1B92 F2C3 F2C4 458A 1B82 F761 8294 FE00
 *
 * Intent: XOR-fold bit merge. A = *AR2-- << 16 into B; B |= *AR2++; A = B ^ (B << 3), then A = B ^ (B << 4) (XOR_ACC_SHIFT: dst ^ shifted-src per ti-c54x op_logical, 40-bit); B = *AR2-- << 16, B |= *AR2, B <<= 1; A-high to *AR4++ (STH src(31:16) per ti-c54x op_sth). Delayed return whose two slots fall through out of span (documented like FRAG_9B6F). AR2/AR4 live-in, net AR2 - 1, AR4 + 1.
 */
void bit_merge_7EA7(int **ppar2, int **ppar4)
{
    long a, b;
    int *ar2 = *ppar2;
    int *ar4 = *ppar4;
    a = ((long)*ar2-- << 16);                    /* ld *ar2-,16,a */
    b = a;                                      /* ld a,b */
    b |= (unsigned short)*ar2++;                 /* or *ar2+,b (Smem zero-ext) */
    a = b ^ (b << 3);                            /* xor b,3,a */
    a = b ^ (b << 4);                            /* xor b,4,a */
    b = ((long)*ar2-- << 16);                    /* ld *ar2-,16,b */
    b |= (unsigned short)*ar2;                   /* or *ar2,b (Smem zero-ext) */
    b <<= 1;                                     /* sfta b,1 */
    *ar4++ = (int)((a >> 16) & 0xFFFF);          /* sth a,*ar4+ */
    *ppar2 = ar2;
    *ppar4 = ar4;
    /* retd: delay slots execute following module words (out of span) */
}
