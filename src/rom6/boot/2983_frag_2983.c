/* ROM6 0x2983 FRAG_2983 -- 46w.
 * Verified encoding: src/rom6/boot/2983_frag_2983.asm (recombine MATCH).
 * ORIGIN 0x2983
 * EXPECT: F074 05B8 6182 0040 F820 2979 61F8 3EC8 0002 F830 2ACC 61F8 3EC8 0020 F820 2A73 7212 265E 7213 2660 60F8 13D0 0000 F830 2A8A 7713 13D0 6183 0001 F820 29B9 F074 3EE1 11E2 0001 F620 F846 29B1 09F8 126F F84E 29B1 7213 2660 F073 2A8A
 *
 * Intent: Flag chain with arithmetic tails. Runs dark 0x5B8 (call, forward extern); bit 6 of *AR2-live-in (entry pointer param) clear jumps away to dark 0x2979 (bitf plus bc ntc, forward extern). Bit 1 of cell 0x3EC8 set runs FRAG_2ACC (bc tc, C: frag_2ACC with A); bit 5 clear tail-enters FRAG_2A73 (bc ntc, C: frag_2A73 this turn). AR2 = cell 0x265E, AR3 = cell 0x2660 (mvdm locals); cell 0x13D0 == 0 tail-enters FRAG_2A73 (bc tc, C: frag_2A73... correction same, forward note). AR3 = 5072; bit 0 of cell 5072 clear tail-enters FRAG_29B9 (bc ntc, C: frag_29B9 with AR2 plus AR3 = 5072). Runs PORT13_STABLE_READ 0x3EE1 (A-OUT proven by the 3EE3 loop shape -- the stable reading overwrites entry A; the old preserve-A reading was wrong, fixed this wave); B = *(AR2+1); A(reading) -= B, > 0 tail-enters FRAG_29B1 (bc agt, C: frag_29B1 with AR3 = 5072). B -= cell 0x126F, > 0 tail-enters FRAG_29B1 too (bc bgt). Else AR3 = cell 0x2660 (mvdm), tail-enters FRAG_2A73 (b, forward extern). SUB per op_sub. Bound 2983-29B0.
 */
extern void sub_05B8(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void frag_2979(void); /* joins 296a_frag_296a interior @+0xF; see docs/evidence/extern-triage.md */
extern void frag_2ACC(int a_live);
extern void frag_2A73(void);
extern void frag_29B9(int *par2, int *par3);
extern int port13_stable_read(void);
extern void frag_29B1(int *par3);

void frag_2983(int a_live, int *par2_entry)
{
    int a = a_live;
    int b;
    int *ar2;
    sub_05B8();                                  /* call 0x5b8 */
    if ((*par2_entry & 64) == 0) {                 /* bitf *ar2,#64; bc ntc */
        frag_2979();                             /* away, dark */
        return;
    }
    if ((*(volatile int *)0x3EC8 & 2) != 0) {    /* bitf, bc tc */
        frag_2ACC(a);                            /* away, C: 2acc_frag_2acc.c */
        return;
    }
    if ((*(volatile int *)0x3EC8 & 32) == 0) {   /* bitf, bc ntc */
        frag_2A73();                             /* tail call */
        return;
    }
    ar2 = (int *)(long)*(volatile int *)0x265E; /* mvdm 0x265e,ar2 */
    /* mvdm 0x2660,ar3 (AR3 dead until stm below) */
    if (*(volatile int *)0x13D0 == 0) {          /* cmpm, bc tc */
        frag_2A73();                             /* tail call */
        return;
    }
    {
        int *ar3 = (int *)5072;                    /* stm #5072,ar3 */
        if ((*(volatile int *)5072 & 1) == 0) {    /* bitf, bc ntc */
            frag_29B9(ar2, ar3);                   /* tail call */
            return;
        }
        a = port13_stable_read();              /* call 0x3ee1 (A-out) */
        b = *(ar2 + 1);                            /* ld *ar2(0x1),b */
        a -= b;                                    /* sub b,a */
        if (a > 0) {                               /* bc 0x29b1,agt */
            frag_29B1(ar3);                        /* tail call */
            return;
        }
        b -= *(volatile int *)0x126F;          /* sub *(0x126f),b */
        if (b > 0) {                               /* bc 0x29b1,bgt */
            frag_29B1(ar3);                        /* tail call */
            return;
        }
        ar3 = (int *)(long)*(volatile int *)0x2660; /* mvdm 0x2660,ar3 */
        (void)ar3;
    }
    frag_2A73();                                 /* b 0x2a8a tail */
}
