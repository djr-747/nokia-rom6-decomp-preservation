/* ROM6 0x92F4 SUB_92F4 -- 33w.
 * Verified encoding: src/rom6/kernel/92f4_sub_92f4.asm (recombine MATCH).
 * ORIGIN 0x92F4
 * EXPECT: F074 0676 F074 9233 7711 004E F074 90B9 7711 3140 76F8 0061 000F F074 90D6 76F8 0061 0002 F074 90E7 76F8 0061 0005 F074 90D6 F074 9331 F0EE 8083 EC06 7193 2F80 FC00
 *
 * Intent: Cell preset plus fold. Runs 0x676 (dark, extern) then
 * 0x9233 (frag_9233, entry AR3 passed through; the callee
 * leaves AR3 = 12128 per its stm #12128, so the model reloads
 * that constant after the call); AR1 = 78 then 12608 (dead
 * after, noted); cell 0x61 = 15; runs 0x90D6 (dark wrapper,
 * extern); cell 0x61 = 2; runs 0x90E7 (dark wrapper, extern);
 * cell 0x61 = 5; runs 0x90D6 again then 0x9331 (dark, extern);
 * A <<= 14 (sftl, logical barrel shift); store A-low through
 * AR3 (= 12128); 7 copies (rpt #6) of successive *AR3++ into
 * fixed cell 0x2F80 (mvdk AR->cell, last wins); return.
 * A is entry-live (never written in span) and assumed
 * preserved through the six dark callees (flagged); BRC is
 * caller-live and any dark-callee BRC use is unbound
 * (flagged). Bound 92F4-9314.
 */
extern void sub_0676(void);
extern void frag_9233(int *par3);
extern void sub_90B9(void);
extern void sub_90D6(void);
extern void sub_90E7(void);
extern void sub_9331(void);

void sub_92F4(int *par3_in, long a_live)
{
    int *ar3;
    int i;
    sub_0676();                                  /* call 0x676 */
    frag_9233(par3_in);                          /* call 0x9233 */
    ar3 = (int *)12128;                          /* callee leaves AR3 = 12128 */
    /* stm #78,ar1 (dead, noted) */
    sub_90B9();                                  /* call 0x90b9 */
    /* stm #12608,ar1 (dead, noted) */
    *(volatile int *)0x61 = 15;                  /* st #15,*(0x61) */
    sub_90D6();                                  /* call 0x90d6 */
    *(volatile int *)0x61 = 2;                   /* st #2,*(0x61) */
    sub_90E7();                                  /* call 0x90e7 */
    *(volatile int *)0x61 = 5;                   /* st #5,*(0x61) */
    sub_90D6();                                  /* call 0x90d6 */
    sub_9331();                                  /* call 0x9331 */
    a_live <<= 14;                               /* sftl a,14 (logical) */
    *ar3 = (int)(a_live & 0xFFFF);               /* stl a,*ar3 */
    for (i = 0; i < 7; i++)                      /* rpt #6 */
        *(volatile int *)0x2F80 = *ar3++;       /* mvdk *ar3+,0x2f80 */
    /* ret */
}
