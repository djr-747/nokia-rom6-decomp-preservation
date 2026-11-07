/* ROM6 0x924C SUB_924C -- 28w.
 * Verified encoding: src/rom6/kernel/924c_sub_924c.asm (recombine MATCH).
 * ORIGIN 0x924C
 * EXPECT: F074 0594 F074 9217 E87F EC07 7308 3224 771A 00E3 F074 9042 7717 3224 771A 0003 F074 9042 771A 00E3 F074 9315 F0EC 8083 EC0E 7193 2F80 FC00
 *
 * Intent: Constant spread plus triple call (9268 twin, BRC 227).
 * Runs 0x594 then 0x9217 (late_leaf_9217, entry AR3 value passed
 * through; 9217 zeroes A after, noted); A = 127 with 8 stores
 * (rpt #7) of AL to fixed cell 0x3224 (mvmd al); BRC = 227 feeds
 * 0x9042 (dark HYPOTHESIS leaf, extern); AR7 = 12836; BRC = 3
 * feeds 0x9042 again; BRC = 227 feeds 0x9315 (dark, extern);
 * A <<= 12 (sftl, logical barrel shift); store A-low through
 * live-in AR3; 15 copies (rpt #14) of successive *AR3++ into
 * fixed cell 0x2F80 (mvdk AR->cell, last wins); return.
 * A assumed preserved through the dark callees (flagged,
 * 9268 convention). Bound 924C-9267.
 */
extern void helper_0594(void);
extern void late_leaf_9217(int ar3_live);
extern void sub_9042(void);
extern void sub_9315(void);

void sub_924C(int *par3)
{
    int i;
    int a = 127;                                 /* ld #127,a */
    helper_0594();                               /* call 0x594 */
    late_leaf_9217((int)par3);                   /* call 0x9217 */
    for (i = 0; i < 8; i++)                      /* rpt #7 */
        *(volatile int *)0x3224 = a;             /* mvmd al,0x3224 */
    /* stm #227,brc; call 0x9042 */
    sub_9042();
    /* stm #12836,ar7; stm #3,brc; call 0x9042 */
    sub_9042();
    /* stm #227,brc; call 0x9315 */
    sub_9315();
    a <<= 12;                                    /* sftl a,12 (logical) */
    *par3 = a;                                   /* stl a,*ar3 */
    for (i = 0; i < 15; i++)                     /* rpt #14 */
        *(volatile int *)0x2F80 = *par3++;       /* mvdk *ar3+,0x2f80 */
    /* ret */
}
