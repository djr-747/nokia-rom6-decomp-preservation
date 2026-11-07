/* ROM6 0x5301 DISPATCH_SLED_A -- 53w.
 * Verified encoding: src/rom6/rf/5301_dispatch_sled_a.asm (recombine MATCH).
 * ORIGIN 0x5301
 * EXPECT: 7712 2650 7711 250F 6081 0080 F830 5312 7712 264F E8F0 1881 60F8 0008 0020 F820 5315 1082 F844 56B9 60F8 2476 0005 F820 5336 7712 250E 7713 2545 EC0C E598 7712 2552 7713 251B EC1F E589 61F8 3EC8 0040 F495 F495 FF30 EC03 E589 68F8 2627 FFF7 69F8 2512 0080 F073 56B7
 *
 * Intent: Table-copy sled with conditional extra block. AR2 = 0x2650, AR1 = 0x250F; *AR1 == 128 skips the mask lane (bc tc to the shared load at 0x5312). Else AR2 = 0x264F, A = 240 AND *AR1 (ld plus AND Smem,src); AL-alias cell != 32 rejoins at 0x5315 (cmpm ntc); shared load A = *AR2, nonzero runs dark 0x56B9 (bc aneq, forward extern). Cell 0x2476 != 5 runs unbound FRAG_5336 (bc ntc, has .asm, forward extern; AR1/AR2 live, intake unobservable). Else copies 13 words 0x2545 to 0x250E (rpt/mvdd) and 32 words 0x2552 to 0x251B (rpt/mvdd); TC = bit 6 of cell 0x3EC8 (bitf, settle nops) also copies 4 more words (xc 2,tc over rpt/mvdd, exact skip per 4EBC); clears bit 3 of cell 0x2627, sets bit 7 of 0x2512; tail-enters C MSG_PRODUCER_CONVERGE_56B7 (b, C-bound). Bound 5301-5335.
 */
extern void frag_56B9(void);
extern void frag_5336(void);
extern void msg_producer_converge_56B7(void);

void frag_5301(void)
{
    int a, i;
    int *ar1, *ar2, *ar3;
    ar2 = (int *)(long)0x2650;                     /* stm */
    ar1 = (int *)(long)0x250F;                     /* stm */
    if (*ar1 != 128) {                             /* cmpm, bc tc skips */
        ar2 = (int *)(long)0x264F;                 /* stm #9807,ar2 */
        a = 240 & (unsigned short)*ar1;             /* ld #240,a; and *ar1,a (Smem zero-ext) */
        if (*(volatile int *)0x8 != 32) {      /* cmpm *(0x8), bc ntc */
            goto l5315;
        }
        /* fall into the shared load (0x5312 join) */
    }
/* l5312: shared load */
    a = *ar2;                                      /* ld *ar2,a */
    if (a != 0) {                                  /* bc 0x56b9,aneq */
        frag_56B9();                               /* away, dark */
        return;
    }
l5315:
    if (*(volatile int *)0x2476 != 5) {        /* cmpm, bc ntc */
        frag_5336();                               /* away, unbound C */
        return;
    }
    ar2 = (int *)(long)0x250E;                     /* stm */
    ar3 = (int *)(long)0x2545;                     /* stm */
    for (i = 0; i < 13; i++) {                     /* rpt #12 */
        *ar2++ = *ar3++;                           /* mvdd *ar3+,*ar2+ */
    }
    ar2 = (int *)(long)0x2552;                     /* stm */
    ar3 = (int *)(long)0x251B;                     /* stm */
    for (i = 0; i < 32; i++) {                     /* rpt #31 */
        *ar3++ = *ar2++;                           /* mvdd *ar2+,*ar3+ */
    }
    {
        int tc = (*(volatile int *)0x3EC8 & 64) != 0; /* bitf */
        /* nop; nop */
        if (tc) {                                  /* xc 2,tc */
            for (i = 0; i < 4; i++) {              /* rpt #3 */
                *ar3++ = *ar2++;                   /* mvdd */
            }
        }
    }
    *(volatile int *)0x2627 &= -9;             /* andm */
    *(volatile int *)0x2512 |= 128;            /* orm */
    msg_producer_converge_56B7();                   /* b 0x56b7 tail */
}
