/* ROM6 0x929E FRAG_929E -- 29w staged worker-call variant A.
 * Verified encoding: src/rom6/kernel/929e_frag_929e.asm (recombine MATCH).
 * ORIGIN 0x929E
 * EXPECT: F074 0594 F074 9217 E87F EC0B 7308 3224 771A 0097 F074 9071 7717 3224 771A 0003 F074 9071 771A 0097 F074 9315 F0E8 828B 8083 EC09 7193 2F80 FC00
 *
 * Intent: Staged setup/measurement variant A (twin of 92D7
 * with different counts/callee). Shared RAM head helper_0594
 * (low-region: zero in mask dump); late leaf
 * late_leaf_9217 (C entry exists, AR3 live-in dark); A =
 * 127 filled 12x into 0x3224 (rpt #11 mvmd); worker 0x9071
 * run with BRC = 151 then a short BRC = 3 pass (in-image
 * span 9071, asm-verified, no C entry yet -- provisional
 * link name); tail 0x9315 likewise (span 9315, asm-verified,
 * no C entry yet); result shifted left 8 into the *AR3 pair
 * (sth/stl); 10 words bulk-moved to 0x2F80 (rpt #9 mvdk);
 * return. AR7 = 12836 select for the worker legs.
 */
extern void helper_0594(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void late_leaf_9217(int ar3_live);
extern void sub_9071(void); /* in-image span 9071, asm-verified, no C entry yet */
extern void sub_9315(void); /* in-image span 9315, asm-verified, no C entry yet */

void frag_929E(void)
{
    long a;
    int *ar3;  /* live-in (dark, flagged) */
    int *ar7;
    int i;

    helper_0594();                                             /* call 0x594 (RAM) */
    late_leaf_9217((int)ar3);                                  /* call 0x9217 (AR3-value in, dark) */
    a = 127;                                                   /* ld #127,a */
    for (i = 0; i < 12; i++)                                   /* rpt #11 */
        *(volatile int *)0x3224 = (int)(a & 0xFFFFL);          /* mvmd al,0x3224 */
    /* stm #151,brc */
    sub_9071();                                                /* call 0x9071 */
    ar7 = (int *)12836;                                        /* stm #12836,ar7 */
    /* stm #3,brc */
    sub_9071();                                                /* call 0x9071 */
    /* stm #151,brc */
    sub_9315();                                                /* call 0x9315 */
    a <<= 8;                                                   /* sftl a,8 */
    *ar3-- = (int)((a >> 16) & 0xFFFFL);                       /* sth a,*ar3- */
    *ar3 = (int)(a & 0xFFFFL);                                 /* stl a,*ar3 */
    for (i = 0; i < 10; i++) {                                 /* rpt #9 */
        *(volatile int *)0x2F80 = *ar3++;                      /* mvdk *ar3+,0x2f80 */
    }
    /* ret */
    (void)ar7;
}
