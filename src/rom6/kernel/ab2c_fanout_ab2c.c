/* ROM6 0xAB2C FANOUT_AB2C -- 42w bit-guarded fanout.
 * Verified encoding: src/rom6/kernel/ab2c_fanout_ab2c.asm (recombine MATCH).
 * ORIGIN 0xAB2C
 * EXPECT: F074 068C 7712 051C 6182 0080 FA20 AB40 6982 0080 10F8 0914 F010 0004 FC42 F020 C000 1882 FC44 F4B9 4A06 4A06 F7B8 F074 AA7C 8A06 7719 0278 F274 AB56 7713 0243 F074 AAC7 8A06 F495 F5B9 F274 AB56 7713 054A FC00
 *
 * Intent: Calls sub_068C (low-zone unsourced, flagged); AR2 =
 * 0x51C; bit 7 of *(0x51C) clear exits via the bcd-ntc lane
 * to rc-aneq on entry A (dark, flagged; the orm #128 delay
 * runs on both lanes, so bit 7 is set regardless); bit set
 * loads A = *(0x914) (bcd fall-through; SXM dark here),
 * A -= 4, A >= 0 returns (rc ageq), A = -16384, A &=
 * *(0x51C) zero-extended (oracle op_and_smem), nonzero
 * returns (rc aneq). Tail: OVB clear (rsbx st0,ovb,
 * hardware), ST0 pushed twice (balanced popms), SXM = 1
 * (ssbx; observed by callees, flagged); calls SEQ_AA7C;
 * BK = 632; AR3 = 579 (calld delays) into PRED_AB56; calls
 * SEQ_AAC7; nop; OVB set (ssbx); AR3 = 1354 (delays) into
 * PRED_AB56; return. AR3 unread in C (implicit callee
 * state); out cells/ARs/BK/SXM.
 * EXPECT from the image.
 */
void fanout_AB2C(void)
{
    long a;  /* entry dark (bcd-taken lane) */
    int *ar2;
    int *ar3;
    int tc;

    sub_068C();                                               /* call 0x68c (low-zone, flagged) */
    ar2 = (int *)1308;                                        /* stm #1308,ar2 */
    tc = (*ar2 & 128) != 0;                                   /* bitf *ar2,#128 (any-bit TC) */
    *ar2 |= 128;                                              /* orm #128,*ar2 (bcd delay, always runs) */
    if (!tc) {                                                /* bcd 0xab40,ntc */
        if (a != 0)                                           /* rc aneq (A = entry, dark) */
            return;
    } else {
        a = (long)*(volatile int *)0x914;                     /* ld *(0x914),a (fall-through) */
        a -= 4;                                               /* sub #4,a */
        if (a >= 0)                                           /* rc ageq */
            return;
        a = -16384;                                           /* ld #-16384,a */
        a &= (unsigned int)*ar2;                              /* and *ar2,a (zero-extend) */
        if (a != 0)                                           /* rc aneq */
            return;
    }
    /* rsbx st0,ovb (hardware, no C form) */
    /* pshm st0; pshm st0 (balanced by popms; comment only) */
    /* ssbx st1,sxm (SXM = 1 for callees, flagged) */
    seq_AA7C();                                               /* call 0xaa7c */
    /* popm st0 */
    /* stm #632,bk */
    ar3 = (int *)579;                                         /* stm #579,ar3 (calld delays) */
    pred_AB56();                                              /* calld 0xab56 */
    seq_AAC7();                                               /* call 0xaac7 */
    /* popm st0 */
    /* nop */
    /* ssbx st0,ovb (hardware, no C form) */
    ar3 = (int *)1354;                                        /* stm #1354,ar3 (calld delays) */
    pred_AB56();                                              /* calld 0xab56 */
    /* ret */
    (void)ar3;
}
