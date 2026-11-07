/* ROM6 0xDBC3 SUB_DBC3 -- 17w.
 * Verified encoding: src/rom6/kernel/dbc3_sub_dbc3.asm (recombine MATCH).
 * ORIGIN 0xDBC3
 * EXPECT: E900 767A 1FFF 771A 0006 F272 DBD1 767B 1249 307A 2092 2892 2892 2892 357B F750 FC00
 *
 * Intent: Weighted-sum kernel. B = 0; cell0x7A = 8191;
 * cell0x7B = 4681 (rptbd delay slot, runs once); 7 passes
 * (BRC = 6; block [RSA = PC + 4 = 0xDBCC, REA = 0xDBD1]; RPTBD
 * execution stays deferred, flagged) of T = cell0x7A (reloaded per
 * pass, invariant), A = T x *AR2++ (MPY Smem, grounded per
 * op_mpy_smem), A += T x *AR2++ thrice (MAC Smem, same core),
 * B += cell0x7B x A-high, unrounded (MACA Smem with R = bit9 = 0
 * per the ROUND layout decode, fixed B per op_maca_smem; T
 * side-loaded, dead). B >>= 16 arithmetic (LD_SRC_SHIFT consumes
 * SXM, flagged); return (retd delays are the ret word only here;
 * AR2 dead, flagged). Products fit 32-bit long (T = 8191;
 * values assumed small, flagged). Bound DBC3-DBD3.
 */
void sub_DBC3(int *ar2_in)
{
    int *ar2 = ar2_in;
    long a;
    long b;
    int t;
    int i;
    b = 0;                                           /* ld #0,b */
    *(volatile int *)0x7A = 8191;                    /* st #8191,0x7a */
    /* stm #6,brc */
    *(volatile int *)0x7B = 4681;                    /* rptbd delay: st (once) */
    for (i = 0; i < 7; i++) {                        /* rptbd 0xdbd1 */
        t = *(volatile int *)0x7A;                   /* ld 0x7a,t */
        a = (long)t * *ar2++;                        /* mpy *ar2+,a */
        a += (long)t * *ar2++;                       /* mac *ar2+,a */
        a += (long)t * *ar2++;                       /* mac *ar2+,a */
        a += (long)t * *ar2++;                       /* mac *ar2+,a */
        b += (long)*(volatile int *)0x7B * (a >> 16); /* maca 0x7b,b (R=0) */
    }
    b = b >> 16;                                     /* ld b,-16,b (SXM arith, flagged) */
    /* ret */
    (void)b;                                         /* B dead at return (flagged) */
}
