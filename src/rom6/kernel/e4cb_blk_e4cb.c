/* ROM6 0xE4CB BLK_E4CB -- 18w.
 * Verified encoding: src/rom6/kernel/e4cb_blk_e4cb.asm (recombine MATCH).
 * ORIGIN 0xE4CB
 * EXPECT: 771A 0009 F272 E4DB F120 FB1C 6F82 0E18 8814 E8FF 1892 880E 448C 4084 F48C 9029 9A97 FC00
 *
 * Intent: T-seeded dot-product tap. BRC = 9; the rptbd delay slot
 * B = -1252 runs once; 10 passes of A = B + (sext(*AR2) arith>>8)
 * (ADD Smem,SHFT,src,dst per ti-c54x op_add_smem_shift: SXM
 * sign-extends, shift raw5 24 = right 8; OVM saturation needs
 * unbound OVM state, values assumed small, flagged), AR4 = A-low,
 * A = 255 & *AR2++ (16-bit AND, upper already zero, exact), T =
 * A-low, A = (*AR4-- << 16) - (*AR4 << 16) (LD/SUB Smem,16:
 * int->long models SXM = 1 exactly, flagged), B = T x A-high
 * (MPYA dst overwrites B per op_mpya_dst), A += *AR4 << 9
 * (ADD Smem,SHFT, SXM = 1 flagged), *(AR3++) = HIGH of (A<<7) =
 * (A>>9) & 0xFFFF (STH_SHIFT per op_sth_shift_smem; exact for
 * 32-bit-long A, flagged) (block [RSA = PC + 4 = 0xE4D2,
 * REA = 0xE4DB]; RPTBD execution stays deferred, flagged); return
 * (ARs dead, flagged). Bound E4CB-E4DB.
 */
void blk_E4CB(int *ar2_in, int *ar3_in)
{
    int *ar2 = ar2_in;
    int *ar3 = ar3_in;
    int ar4;
    long a;
    long b;
    long t;
    int i;
    /* stm #9,brc */
    b = -1252;                                       /* rptbd delay: ld (once) */
    for (i = 0; i < 10; i++) {                       /* rptbd 0xe4db */
        a = b + ((long)*ar2 >> 8);                   /* add *ar2,-8,b,a */
        ar4 = (int)(a & 0xFFFF);                     /* stlm a,ar4 */
        a = 255;                                     /* ld #255,a */
        a &= (long)*ar2++;                           /* and *ar2+,a */
        t = (int)(a & 0xFFFF);                       /* stlm a,t */
        a = (long)*(int *)ar4 << 16;                 /* ld *ar4-,16,a */
        ar4--;
        a -= (long)*(int *)ar4 << 16;                /* sub *ar4,16,a */
        b = t * (a >> 16);                           /* mpya a (B = T x A-hi) */
        a += (long)*(int *)ar4 << 9;                 /* add *ar4,9,a */
        *ar3++ = (int)((a >> 9) & 0xFFFF);           /* sth a,7,*ar3+ */
    }
    /* ret */
    (void)b;                                         /* B dead at return (flagged) */
}
