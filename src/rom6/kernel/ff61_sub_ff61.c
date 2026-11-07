/* ROM6 0xFF61 SUB_FF61 -- 8w.
 * Verified encoding: src/rom6/kernel/ff61_sub_ff61.asm (recombine MATCH).
 * ORIGIN 0xFF61
 * EXPECT: E724 4719 E518 E742 4719 E318 E742 FC00
 *
 * Intent: Copy plus distance-sum loop (audio). AR4 = AR2; 26 copies (rpt 0x19) of *AR3 (fixed source) through AR2; restore AR2; 26 ABDST steps (rpt 0x19): A = (X-Y) << 16 with X = *AR3, Y = *AR2++, B += |A-high| (ABS with -32768 edge per ti-c54x op_distance_dual, 40-bit); restore AR2; returns the distance sum (B live-in added).
 */
long sub_FF61(int *par3, int **ppar2, long b_in)
{
    int i;
    int *ar2 = *ppar2;
    int *ar4 = ar2;                              /* mvmm ar2,ar4 */
    long b = b_in;
    for (i = 0; i < 26; i++)                     /* rpt 0x19 */
        *ar2++ = *par3;                         /* mvdd *ar3,*ar2+ */
    ar2 = ar4;                                   /* mvmm ar4,ar2 */
    for (i = 0; i < 26; i++) {                   /* rpt 0x19 */
        int d = *par3 - *ar2++;                  /* abdst X-Y */
        int ad = (d == -32768) ? 32768 : (d < 0 ? -d : d);
        b += ad;                                 /* B += |A(32:16)| */
    }
    *ppar2 = ar4;                               /* mvmm ar4,ar2 */
    return b;                                    /* ret */
}
