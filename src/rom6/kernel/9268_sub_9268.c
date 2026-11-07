/* ROM6 0x9268 SUB_9268 -- 25w.
 * Verified encoding: src/rom6/kernel/9268_sub_9268.asm (recombine MATCH).
 * ORIGIN 0x9268
 * EXPECT: F074 0594 F074 9217 E87F EC07 7308 3224 771A 0026 F074 9042 7717 3224 771A 0003 F074 9042 771A 0026 F074 9315 F0E9 8083 FC00
 *
 * Intent: Constant spread plus triple call. Runs 0x594 then 0x9217; A = 127 with 8 stores (rpt #7) of AL to fixed cell 0x3224 (mvmd al); BRC = 38 feeds 0x9042; AR7 = 12836; BRC = 3 feeds 0x9042 again; BRC = 38 feeds 0x9315; A <<= 9 (sftl, logical barrel shift); store A-low through live-in AR3; return.
 */
extern void helper_0594(void);
extern void sub_9217(void);
extern void sub_9042(void);
extern void sub_9315(void);

void sub_9268(int *par3)
{
    int i;
    int a = 127;                                 /* ld #127,a */
    helper_0594();                               /* call 0x594 */
    sub_9217();                                  /* call 0x9217 */
    for (i = 0; i < 8; i++)                      /* rpt #7 */
        *(volatile int *)0x3224 = a;         /* mvmd al,0x3224 */
    /* stm #38,brc; call 0x9042 */
    sub_9042();
    /* stm #12836,ar7; stm #3,brc; call 0x9042 */
    sub_9042();
    /* stm #38,brc; call 0x9315 */
    sub_9315();
    a <<= 9;                                     /* sftl a,9 (logical) */
    *par3 = a;                                   /* stl a,*ar3 */
    /* ret */
}
