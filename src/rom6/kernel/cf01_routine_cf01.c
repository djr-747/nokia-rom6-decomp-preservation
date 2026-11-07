/* ROM6 0xCF01 ROUTINE_CF01 -- 36w init-and-dispatch sequence.
 * Verified encoding: src/rom6/kernel/cf01_routine_cf01.asm (recombine MATCH).
 * ORIGIN 0xCF01
 * EXPECT: EA00 7719 0000 4A07 7707 0740 F074 0680 7711 0D42 7713 FD99 F274 E276 7714 110A 7712 FE89 F274 E2B4 7713 110C F274 E2C3 7711 0F1B 7663 0C62 7662 0F92 F274 E395 7611 0F1B 8A07 FC00
 *
 * Intent: DP = 0, BK = 0, ST1 saved (pshm) and loaded with
 * 1856 (0x740, field split dark, flagged), then a four-call
 * dispatch chain with CALLD pre-call delays: call 0x680
 * (low-zone unsourced, flagged) with AR1 = 3394, AR3 = -615
 * preset and AR4 = 4362 (calld delay word, runs pre-call);
 * calld BLK_E276; AR2 = -375, AR3 = 4364 (delays); calld
 * BLK_E2B4 (interior entry of BLK_E276's E276-E2C2 span,
 * flagged); AR1 = 3867 (delays); calld BLK_E2C3 with cells
 * *(0x63) = 3170, *(0x62) = 3986 preset and *(0x11) = 3867
 * (delays); calld ROUTINE_E395; ST1 restored (popm),
 * return. DP/BK/ST1/pshm are CPU state (comment only, values
 * recorded); AR/cell stores are the modeled intent.
 * EXPECT from the image.
 */
void routine_CF01(void)
{
    int *ar1;
    int *ar2;
    int *ar3;
    int *ar4;

    /* ld #0,dp (CPU register, comment only) */
    /* stm #0,bk (CPU register, comment only) */
    /* pshm st1 (balanced by popm st1; caller-live, comment only) */
    /* stm #1856,st1 (CPU register, 0x740; field split dark, flagged) */
    sub_0680();                                          /* call 0x680 (low-zone unsourced, flagged) */
    ar1 = (int *)3394;                                   /* stm #3394,ar1 */
    ar3 = (int *)-615;                                   /* stm #-615,ar3 */
    ar4 = (int *)4362;                                   /* stm #4362,ar4 (calld delays) */
    blk_E276();                                          /* calld 0xe276 */
    ar2 = (int *)-375;                                   /* stm #-375,ar2 */
    ar3 = (int *)4364;                                   /* stm #4364,ar3 (calld delays) */
    blk_E2B4();                                          /* calld 0xe2b4 (interior of BLK_E276, flagged) */
    ar1 = (int *)3867;                                   /* stm #3867,ar1 (calld delays) */
    blk_E2C3();                                          /* calld 0xe2c3 */
    *(volatile int *)0x63 = 3170;                        /* st #3170,0x63 */
    *(volatile int *)0x62 = 3986;                        /* st #3986,0x62 */
    *(volatile int *)0x11 = 3867;                        /* st #3867,0x11 (calld delays) */
    routine_E395();                                      /* calld 0xe395 */
    /* popm st1 (balanced; comment only) */
    /* ret */
    (void)ar1;
    (void)ar2;
    (void)ar3;
    (void)ar4;
}
