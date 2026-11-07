/* ROM6 0x92BB ROUTINE_92BB -- 28w.
 * Verified encoding: src/rom6/kernel/92bb_routine_92bb.asm (recombine MATCH).
 * ORIGIN 0x92BB
 * EXPECT: F074 0594 F074 9217 E87F EC0B 7308 3224 771A 004B F074 9071 7717 3224 771A 0003 F074 9071 771A 004B F074 9315 F0E4 8083 EC04 7193 2F80 FC00
 *
 * Intent: Constant spread plus triple call (9268 twin, BRC 75,
 * 9071 callee). Runs 0x594 then 0x9217 (late_leaf_9217, entry
 * AR3 value passed through; 9217 zeroes A after, noted);
 * A = 127 with 12 stores (rpt #11) of AL to fixed cell 0x3224
 * (mvmd al); BRC = 75 feeds 0x9071 (dark HYPOTHESIS wrapper,
 * extern); AR7 = 12836; BRC = 3 feeds 0x9071 again; BRC = 75
 * feeds 0x9315 (dark, extern); A <<= 4 (sftl, logical barrel
 * shift); store A-low through live-in AR3; 5 copies (rpt #4)
 * of successive *AR3++ into fixed cell 0x2F80 (mvdk AR->cell,
 * last wins); return. A assumed preserved through the dark
 * callees (flagged, 9268 convention). Bound 92BB-92D6.
 */
extern void helper_0594(void);
extern void late_leaf_9217(int ar3_live);
extern void sub_9071(void);
extern void sub_9315(void);

void routine_92BB(int *par3)
{
    int i;
    int a = 127;                                 /* ld #127,a */
    helper_0594();                               /* call 0x594 */
    late_leaf_9217((int)par3);                   /* call 0x9217 */
    for (i = 0; i < 12; i++)                     /* rpt #11 */
        *(volatile int *)0x3224 = a;             /* mvmd al,0x3224 */
    /* stm #75,brc; call 0x9071 */
    sub_9071();
    /* stm #12836,ar7; stm #3,brc; call 0x9071 */
    sub_9071();
    /* stm #75,brc; call 0x9315 */
    sub_9315();
    a <<= 4;                                     /* sftl a,4 (logical) */
    *par3 = a;                                   /* stl a,*ar3 */
    for (i = 0; i < 5; i++)                      /* rpt #4 */
        *(volatile int *)0x2F80 = *par3++;       /* mvdk *ar3+,0x2f80 */
    /* ret */
}
