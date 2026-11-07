/* ROM6 0x93CE MSG_CLASSIFY_BY_CALLER -- 70w TC-result classifier, one EXPECT.
 * Verified encoding: src/rom6/msg/93ce_msg_classify_by_caller.asm (recombine MATCH).
 * ORIGIN 0x93CE
 * EXPECT: F074 05BC 61F8 3EC8 0002 F820 9414 61F8 054D 0060 E783 F820 9414 6083 2D5D F830 93E3 6083 2DDB F820 9414 E723 4A08 4A09 4A0A 6D93 1083 F030 00FF 7713 0008 61F8 054D 0040 F820 93FE 6083 004D F830 9410 6083 009A F830 9410 6083 0005 F830 9410 61F8 054D 0020 F820 940B 6083 0050 F830 9410 6083 009C F830 9410 8A0A 8A09 8A08 F073 9414 8A0A 8A09 8A08 FC00
 *
 * Intent: Caller-sensitive flag gate with a TC result. Runs dark SUB_05BC
 * (call). Entry A rides the whole span untouched (pshm al/ah/ag balanced
 * by popm ag/ah/al on every pushed path; A-out = A-in, noted -- the int
 * return below is the TC result, not A). Lanes, all TC-threaded:
 * bit 1 of cell 0x3EC8 clear exits 0 (bitf + bc ntc to exterior 0x9414);
 * bits 5:6 of cell 0x54D (mask 96) clear exits 0. AR3 = SP (mvmm);
 * stacked word == 0x2D5D continues (cmpm *ar3 + bc tc to 93E3),
 * == 0x2DDB falls through (bc ntc exits 0 on mismatch): return-PC match
 * decides the deep lanes (stack layout HYPOTHESIS -- SP points at the
 * caller return word, trace-confirmable). AR3 = AR2 (mvmm); push A
 * triple; AR3++; A = *(AR2+1) & 255 (ld/and -- DEAD: AR3 is reassigned
 * to 8 before the compares below, so the masked A is never read;
 * transcribed hand-asm fossil, flagged). AR3 = 8 (stm): the low-byte
 * lanes test MMR cell *(8): bit 6 of 0x54D clear detours to the 32-lane
 * (bc ntc to 93FE); *(8) == 77/154/5 returns 1 (cmpm + bc tc converge
 * on the 9410 pop triple). 32-lane at 93FE: bit 5 of 0x54D clear exits
 * via the 940B pop triple (b to exterior 0x9414, TC = 0); *(8) == 80/156
 * returns 1 (9410 triple); all-mismatch falls through the main pop
 * triple (b to exterior, TC = 0). Every pushed path pops balanced, then
 * exits to exterior 0x9414 or the span RET (bound 93CE-9413: final FC00
 * @0x9413, exterior 0x9414 = next routine head per listing).
 * BITF any-bit TC per op_bitf; CMPM TC-only per op_cmpm_smem_lk.
 */
extern void sub_05BC(void);

int msg_classify_by_caller(int *par2, int *sp_live, long a_live)
{
    int tc;
    int *par3;
    long a;

    (void)a_live;                            /* rides via pshm/popm */
    (void)par2;
    sub_05BC();                                        /* call 0x5bc */
    tc = (*(volatile int *)0x3EC8 & 2) != 0;           /* bitf */
    if (!tc)                                           /* bc 9414,ntc */
        return 0;
    tc = (*(volatile int *)0x54D & 96) != 0;           /* bitf */
    par3 = sp_live;                                    /* mvmm sp,ar3 */
    if (!tc)                                           /* bc 9414,ntc */
        return 0;
    tc = (*par3 == 11613);                    /* cmpm *ar3,#0x2d5d */
    if (tc) {                                          /* bc 93e3,tc */
        /* fall into the push lane below */
    } else {
        tc = (*par3 == 11739);                /* cmpm *ar3,#0x2ddb */
        if (!tc)                                       /* bc 9414,ntc */
            return 0;
    }
    par3 = par2;                                       /* mvmm ar2,ar3 */
    /* pshm al/ah/ag (balanced by the popm triples below) */
    par3++;                                            /* mar *ar3+ */
    a = (unsigned long)(unsigned)*par3;                /* ld *ar3,a */
    a &= 255;                               /* and #255,a (DEAD, noted) */
    par3 = (int *)8;                         /* stm #8,ar3 */
    tc = (*(volatile int *)0x54D & 64) != 0;           /* bitf */
    if (!tc) {                                         /* bc 93fe,ntc */
        tc = (*(volatile int *)0x54D & 32) != 0;       /* 93FE: bitf */
        if (!tc)                                       /* bc 940b,ntc */
            return 0;                     /* 940B pop triple; b 9414 */
        if (*par3 == 80)                               /* cmpm */
            return 1;                                  /* bc 9410,tc */
        return (*par3 == 156) ? 1 : 0;       /* cmpm; fallthrough */
    }
    if (*par3 == 77)                                   /* cmpm */
        return 1;                                      /* bc 9410,tc */
    if (*par3 == 154)                                  /* cmpm */
        return 1;
    return (*par3 == 5) ? 1 : 0;              /* cmpm; fallthrough */
}
