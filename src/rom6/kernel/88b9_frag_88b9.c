/* ROM6 0x88B9 FRAG_88B9 -- 33w init + block-copy, branch tail.
 * Verified encoding: src/rom6/kernel/88b9_frag_88b9.asm (recombine MATCH).
 * ORIGIN 0x88B9
 * EXPECT: 7714 09C8 F274 86FB 7713 3090 7714 051E 7719 0000 6884 FFFE 7319 055A 6884 FFF9 F274 89C4 6984 0002 7713 119C EC07 7093 3090 7710 0011 7712 309B EC03 E5C9 F073 88AD

 *
 * Intent: Peripheral/init preset plus two block copies,
 * exiting by branch into the HEAD_8854 zone. AR4 = 2504;
 * deferred call 0x86FB (in-image span, asm-verified, no C
 * entry -- provisional link name) with AR3 = 12432 in the
 * delay slots; AR4 = 1310 at the return address; BK = 0;
 * cell 1310 &= ~2 then &= ~7 (ANDM pair); cell 0x55A = BK
 * (MVMD, BK = 0); deferred call 0x89C4 likewise (ORM
 * #2,*AR4 in the delay slots) with AR3 = 4508 at the
 * return address; 8x copy of cell 0x3090 to *AR3+ (rpt #7
 * mvkd); AR0 = 17 (dead after, flagged); AR2 = 12443; 4x
 * copy *AR2+0% to *AR3+ (rpt #3 mvdd, circular BK = 0,
 * flagged); tail branch to 0x88AD (mid-8854-span join,
 * asm-verified, no C entry -- provisional join extern,
 * transfer, no return). No live entry state.
 * (Wave-13: EXPECT taken from the image word map, not
 * hand-composed; CALLD delay/return-address order per the
 * 2-delay-word silicon rule.)
 */
extern void sub_86FB(void); /* in-image span 86FB, asm-verified, no C entry yet */
extern void sub_89C4(void); /* in-image span 89C4, asm-verified, no C entry yet */
extern void frag_88AD(void); /* joins HEAD_8854 zone at 88AD, asm-verified, no C entry yet */

void frag_88B9(void)
{
    int *ar0;
    int *ar2;
    int *ar3;
    int *ar4;
    int i;

    ar4 = (int *)2504;                                         /* stm #2504,ar4 */
    ar3 = (int *)12432;                                        /* calld delay: stm #12432,ar3 (fills both delay words) */
    sub_86FB();                                                /* calld 0x86fb */
    ar4 = (int *)1310;                                         /* return address: stm #1310,ar4 */
    /* stm #0,bk (BK = 0) */
    *ar4 &= -2;                                                /* andm #-2,*ar4 */
    *(volatile int *)0x55A = 0;                                /* mvmd bk,0x55a (BK = 0) */
    *ar4 &= -7;                                                /* andm #-7,*ar4 */
    *ar4 |= 2;                                                 /* calld delay: orm #2,*ar4 (fills both delay words) */
    sub_89C4();                                                /* calld 0x89c4 */
    ar3 = (int *)4508;                                         /* return address: stm #4508,ar3 */
    for (i = 0; i < 8; i++)                                    /* rpt #7 */
        *ar3++ = *(volatile int *)0x3090;                      /* mvkd 0x3090,*ar3+ */
    ar0 = (int *)17;                                           /* stm #17,ar0 (dead after, flagged) */
    ar2 = (int *)12443;                                        /* stm #12443,ar2 */
    for (i = 0; i < 4; i++)                                    /* rpt #3 */
        *ar3++ = *ar2++;                                       /* mvdd *ar2+0%,*ar3+ (circular BK = 0, flagged) */
    frag_88AD();                                               /* b 0x88ad (tail transfer, not a call) */
    /* (transfer, no return) */
    (void)ar0;
}
