/* ROM6 0x4EBC RPTB_MATH_4EBC -- 18w.
 * Verified encoding: src/rom6/kernel/4ebc_rptb_math_4ebc.asm (recombine MATCH).
 * ORIGIN 0x4EBC
 * EXPECT: 771A 0038 F072 4ECC 7192 0013 6DB3 4583 F76C F768 F778 F775 F062 0001 F600 3184 8783 FC00
 *
 * Intent: Shift-chain math loop (57 iterations, BRC = 56, rptb 0x4ecc). Per iteration: cell 0x13 = *AR2++ (mvdk, AR2 live-in); AR3 += AR0 (mar *ar3+0, AR0 live-in step, by-AR0 convention flagged); B = *AR3 << 16 then <<= 12, <<= 8, >>= 8 (sfta, 40-bit, arithmetic); >>= 11; A = (1 << 16) + B; B = *AR4 times A-high (MPYA Smem overwrites B per ti-c54x op_mpya_smem); *AR3 = ((B << ASM) >> 16) low word (STH with ASM shift mode, ST1 ASM field live-in, flagged). 40-bit values in long long (cl500 acceptance flagged). AR4 live-in, no post-inc.
 */
void rptb_math_4EBC(int **ppar2, int **ppar3, int *par4, int ar0_live, int asm_live)
{
    int i;
    int *ar2 = *ppar2;
    int *ar3 = *ppar3;
    for (i = 0; i < 57; i++) {                    /* stm #56,brc; rptb */
        long long a, b;
        long long shifted;
        *(volatile int *)0x13 = *ar2++;       /* mvdk *ar2+,0x13 */
        ar3 += ar0_live;                         /* mar *ar3+0 */
        b = ((long long)*ar3 << 16);             /* ld *ar3,16,b */
        b <<= 12; b <<= 8; b >>= 8; b >>= 11;    /* sfta chain */
        a = ((long long)1 << 16) + b;            /* ld #1,16,a; add b,a */
        b = (long long)*par4 * (int)(a >> 16);   /* mpya *ar4 */
        shifted = (asm_live >= 0) ? (b << asm_live) : (b >> -asm_live);
        *ar3 = (int)((shifted >> 16) & 0xFFFF);  /* sth b,asm,*ar3 */
    }
    *ppar2 = ar2;
    *ppar3 = ar3;
    /* ret */
}
