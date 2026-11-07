/* ROM6 0xE837 BLK_E837 -- 30w SQDST energy block, far exit.
 * Verified encoding: src/rom6/kernel/e837_blk_e837.asm (recombine MATCH).
 * ORIGIN 0xE837
 * EXPECT: 4A13 7713 3DEE 7714 3E06 E900 A29A EC16 E29A E212 70F8 3E22 3E20 F765 83F8 3E20 44F8 3E23 F487 82F8 3E23 44F8 3E21 F600 82F8 3E21 8A13 8A0C 8A0B F5E6
 *
 * Intent: 24-tap difference-energy (SQDST) block. Save AR3
 * (pshm); AR3/AR4 = 15854/15878; B = 0; seed A =
 * ((*AR3+) - (*AR4+)) << 16 (SUB dual MOD0 = X - Y per
 * op_dual_arithmetic); 23x RPT + 1x SQDST (d = X - Y,
 * A = d << 16, B += d * d per the 22f3 convention,
 * FRCT-doubling flagged); copy *(0x3E20) to *(0x3E22)
 * (mvkd); B <<= 5 published MSW-first to *(0x3E20); A =
 * *(0x3E23) << 16 clamped by MIN to B (A = min(A,B) signed
 * full-width per oracle MIN_ACC in op_compare); store back;
 * A = *(0x3E21) << 16 accumulated with B and stored back;
 * restore AR3/BH/BL (popm); far return via FBACC to
 * restored B -- computed exit, permanently dark (target in
 * caller B), modeled as a plain return with the note. Out:
 * energy/mix cells 0x3E20-0x3E23.
 * (Wave-13: dual-SUB <<16 with X-first order corrected per
 * the oracle leaf.)
 */
void blk_E837(void)
{
    long a;
    long b;
    long d;
    int *ar3;
    int *ar4;
    int i;

    /* pshm ar3 (entry AR3 saved, restored before return) */
    ar3 = (int *)15854;                                        /* stm #15854,ar3 */
    ar4 = (int *)15878;                                        /* stm #15878,ar4 */
    b = 0;                                                     /* ld #0,b */
    a = ((long)*ar3++ - (long)*ar4++) << 16;                   /* sub *ar3+,*ar4+,a (dual) */
    for (i = 0; i < 23; i++) {                                 /* rpt #22 */
        d = (long)*ar3++ - (long)*ar4++;                       /* sqdst *ar3+,*ar4+ */
        a = d << 16;
        b += d * d;                                            /* (FRCT-doubling flagged) */
    }
    d = (long)*ar3 - (long)*ar4;                               /* sqdst *ar3,*ar4 */
    a = d << 16;
    b += d * d;
    *(volatile int *)0x3E22 = *(volatile int *)0x3E20;         /* mvkd 0x3e20,*(0x3e22) */
    b <<= 5;                                                   /* sfta b,5 */
    *(volatile int *)0x3E20 = (int)((b >> 16) & 0xFFFFL);     /* sth b,*(0x3e20) */
    a = (long)*(volatile int *)0x3E23 << 16;                   /* ld *(0x3e23),16,a */
    if (b < a)                                                 /* min a (A = min(A,B) per oracle MIN_ACC) */
        a = b;
    *(volatile int *)0x3E23 = (int)((a >> 16) & 0xFFFFL);     /* sth a,*(0x3e23) */
    a = (long)*(volatile int *)0x3E21 << 16;                   /* ld *(0x3e21),16,a */
    a += b;                                                    /* add b,a */
    *(volatile int *)0x3E21 = (int)((a >> 16) & 0xFFFFL);     /* sth a,*(0x3e21) */
    /* popm ar3; popm bh; popm bl (caller state restored) */
    /* fbacc b (computed far exit, permanently dark) */
    /* (modeled as return) */
    (void)a; (void)b; (void)d;
}
