/* ROM6 0x92D7 ROUTINE_92D7 -- 29w staged worker-call variant B.
 * Verified encoding: src/rom6/kernel/92d7_routine_92d7.asm (recombine MATCH).
 * ORIGIN 0x92D7
 * EXPECT: F074 0594 F074 9217 E87F EC07 7308 3224 771A 00F3 F074 9042 7717 3224 771A 0003 F074 9042 771A 00F3 F074 9315 F0EC 828B 8083 EC0F 7193 2F80 FC00
 *
 * Intent: Staged setup/measurement variant B (twin of 929E).
 * Shared RAM head helper_0594; late leaf late_leaf_9217
 * (AR3 dark); A = 127 filled 8x into 0x3224 (rpt #7 mvmd);
 * worker 0x9042 run with BRC = 243 then a short BRC = 3
 * pass (in-image span 9042: its C file is Pool, no C entry
 * yet -- provisional link name); tail 0x9315 likewise;
 * result shifted left 12 into the *AR3 pair; 16 words
 * bulk-moved to 0x2F80 (rpt #15 mvdk); return. AR7 = 12836.
 * Entries: calld F274@494->92D7 byte-verified (from
 * 8210-setB block08) + post-RET.
 */
extern void helper_0594(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void late_leaf_9217(int ar3_live);
extern void sub_9042(void); /* in-image span 9042 (C file Pool), no C entry yet */
extern void sub_9315(void); /* in-image span 9315, asm-verified, no C entry yet */

void routine_92D7(void)
{
    long a;
    int *ar3;  /* live-in (dark, flagged) */
    int *ar7;
    int i;

    helper_0594();                                             /* call 0x594 (RAM) */
    late_leaf_9217((int)ar3);                                  /* call 0x9217 (AR3-value in, dark) */
    a = 127;                                                   /* ld #127,a */
    for (i = 0; i < 8; i++)                                    /* rpt #7 */
        *(volatile int *)0x3224 = (int)(a & 0xFFFFL);          /* mvmd al,0x3224 */
    /* stm #243,brc */
    sub_9042();                                                /* call 0x9042 */
    ar7 = (int *)12836;                                        /* stm #12836,ar7 */
    /* stm #3,brc */
    sub_9042();                                                /* call 0x9042 */
    /* stm #243,brc */
    sub_9315();                                                /* call 0x9315 */
    a <<= 12;                                                  /* sftl a,12 */
    *ar3-- = (int)((a >> 16) & 0xFFFFL);                       /* sth a,*ar3- */
    *ar3 = (int)(a & 0xFFFFL);                                 /* stl a,*ar3 */
    for (i = 0; i < 16; i++) {                                 /* rpt #15 */
        *(volatile int *)0x2F80 = *ar3++;                      /* mvdk *ar3+,0x2f80 */
    }
    /* ret */
    (void)ar7;
}
