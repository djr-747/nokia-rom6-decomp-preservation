/* ROM6 0xAC07 FRAG_AC07 -- 27w event-dispatch fragment.
 * Verified encoding: src/rom6/kernel/ac07_frag_ac07.asm (recombine MATCH).
 * ORIGIN 0xAC07
 * EXPECT: E750 7712 24B3 6DAA 6B82 0001 7714 24F2 6DAC 6DAC 5684 0083 4E84 11F8 0060 4A10 F274 7067 7713 3E9F 8A10 7712 03F8 6DAA FE00 7082 0060
 *
 * Intent: Event counter + 32-bit accumulator update, then a
 * deferred dispatch. AR5 saved to AR0; cell 9395 += 1
 * (addm); 32-bit cell *(9458) += *AR3 (DLD pair load, ADD,
 * DST pair store: MSW at *AR4, LSW at *(AR4+1)); B =
 * status MMR96 (plain LD, SXM-dark, flagged); deferred call
 * 0x7067 (in-image span, asm-verified, no C entry yet --
 * provisional link name sub_7067) with AR3 = 16031 selector
 * in the delay slots (stm fills both delay words; AR0
 * popped at the return address, after the call body runs);
 * then publish MMR96 to *(1016); return. (Wave-13: DLD
 * lane order, DST two-store, ADD Smem <<16, and CALLD
 * delay/return-address order corrected per the oracle
 * leaves and the 2-delay-word silicon rule.)
 */
extern void sub_7067(void); /* in-image span 7067, asm-verified, no C entry yet */

void frag_AC07(void)
{
    long a;  /* live-in (dark, flagged) */
    long b;
    int *ar0;
    int *ar2;
    int *ar3;  /* live-in (dark, flagged) */
    int *ar4;
    int *ar5;  /* live-in (dark, flagged) */

    ar0 = ar5;                                                 /* mvmm ar5,ar0 */
    ar2 = (int *)9395;                                         /* stm #9395,ar2 */
    /* mar *ar2-0 */
    (*ar2)++;                                                  /* addm #1,*ar2 */
    ar4 = (int *)9458;                                         /* stm #9458,ar4 */
    /* mar *ar4-0 */
    /* mar *ar4-0 */
    a = ((long)*ar4 << 16) | ((long)*(ar4 + 1) & 0xFFFFL);     /* dld *ar4,a */
    a += (long)*ar3 << 16;                                     /* add *ar3,a (ADD Smem: dst_old + Smem<<16) */
    *ar4 = (int)((a >> 16) & 0xFFFFL);                         /* dst a,*ar4+ (MSW) */
    *(ar4 + 1) = (int)(a & 0xFFFFL);                           /* (LSW) */
    ar4++;
    b = (long)*(volatile int *)0x60;                           /* ld *(0x60),b (SXM-dark, flagged) */
    /* pshm ar0 */
    ar3 = (int *)16031;                                        /* calld delay: stm #16031,ar3 (fills both delay words) */
    sub_7067();                                                /* calld 0x7067 */
    ar0 = ar5;                                                 /* return address: popm ar0 (restores entry AR5) */
    ar2 = (int *)1016;                                         /* stm #1016,ar2 */
    /* mar *ar2-0 */
    /* retd (delay words run, then return): */
    *ar2 = *(volatile int *)0x60;                               /* mvkd 0x60,*ar2 */
    /* retd */
    (void)a; (void)b;
}
