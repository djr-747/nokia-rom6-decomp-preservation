/* ROM6 0xDA35 FRAG_DA35 -- 11w.
 * Verified encoding: src/rom6/kernel/da35_frag_da35.asm (recombine MATCH).
 * ORIGIN 0xDA35
 * EXPECT: 6B58 FFFF 4458 3C59 F061 001E F842 DA40 FE00 765A 0020
 *
 * Intent: Countdown cell with threshold branch. Cell 0x58 decrements
 * (addm #-1); A = (cell0x58 << 16) + (cell0x59 << 16) - (30 << 16)
 * (LD/ADD/SUB Smem,16: sign-extend per SXM = 1, flagged; int->long
 * conversion models it exactly); A >= 0 tail-enters FRAG_DA40, else
 * cell 0x5A = 32 (retd delay, always runs) and far return. Cells
 * absolute per the da40 precedent (DP = 0 page assumed, flagged).
 * Bound DA35-DA3F.
 */
extern void frag_DA40(void);

void frag_DA35(void)
{
    int m58;
    long a;
    m58 = *(volatile int *)0x58 - 1;                 /* addm #-1,0x58 */
    *(volatile int *)0x58 = m58;
    a = (long)m58 << 16;                             /* ld 0x58,16,a */
    a += (long)*(volatile int *)0x59 << 16;          /* add 0x59,16,a */
    a -= (30L << 16);                                /* sub #30,16,a */
    if (a >= 0) {                                    /* bc 0xda40,ageq */
        frag_DA40();
        return;
    }
    *(volatile int *)0x5A = 32;                      /* retd delay: st (always runs) */
    /* retd */
}
