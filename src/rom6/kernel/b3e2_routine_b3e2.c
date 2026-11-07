/* ROM6 0xB3E2 ROUTINE_B3E2 -- 58w three-phase cell/motor setup.
 * Verified encoding: src/rom6/kernel/b3e2_routine_b3e2.asm (recombine MATCH).
 * ORIGIN 0xB3E2
 * EXPECT: F074 05A8 7712 3490 1082 F030 FFF0 F040 0008 8082 76F8 348F 2667 71F8 2639 34C9 F074 B41C 10F8 34BF FC45 7712 3490 1082 F030 FFF0 F040 0001 8082 76F8 348F 279F 71F8 34C9 2639 F074 B41C 60F8 34BF 0004 FC20 7712 3490 1082 F030 FFF0 F040 0002 8082 76F8 348F 28D7 71F8 34C9 2639 F074 B41C FC00
 *
 * Intent: Entry via 5x call (B1B0/B1F7/B25D/B2D0/B312) with no live
 * regs (void). Runs dark SUB_05A8 (low-zone mini-kernel, no symbol,
 * opaque). Three straight-line phases (no branches; rc only) over cell
 * 13456: clear low 4 bits (and #-16), set one bit (or #8/#1/#2), store
 * low back (stl). Phase 1: cell 0x348F = 9831, save cell 0x2639 into
 * 0x34C9 (mvdk dmad=source), run frag_B41C. Phase 2: A = cell 0x34BF,
 * rc aeq clears carry when zero; cell 0x348F = 10143, restore cell
 * 0x2639 from 0x34C9, run frag_B41C. Phase 3: TC = (cell 0x34BF == 4)
 * (cmpm, TC = equality per op_cmpm); rc ntc clears carry when unequal;
 * cell 0x348F = 10455, restore cell 0x2639, run frag_B41C; ret. B never
 * set (dark in/out, noted); T untouched (dark, noted); carry modeled
 * 0-in (dark, 7e88 precedent), never read in-span (noted). Out
 * cells/A/AR2/TC/C. EXPECT from the image.
 */
extern void sub_05A8(void);   /* dark, no symbol (low-zone mini-kernel) */
extern void frag_B41C(void);  /* joins b41c_frag_b41c */

void routine_B3E2(void)
{
    long a;
    int carry = 0;  /* C54x carry in (dark, flagged); never read in-span */
    int tc;
    int *ar2;

    sub_05A8();                                              /* call 0x5a8 */
    ar2 = (int *)(long)13456;                                /* stm #13456,ar2 */
    a = (long)*ar2;                                          /* ld *ar2,a */
    a &= -16L;                                               /* and #-16,a */
    a |= 8L;                                                 /* or #8,a */
    *ar2 = (int)(a & 0xFFFFL);                               /* stl a,*ar2 */
    *(volatile int *)0x348F = 9831;                          /* st #9831,*(0x348f) */
    *(volatile int *)0x34C9 = *(volatile int *)0x2639;       /* mvkd *(0x2639),0x34c9 */
    frag_B41C();                                             /* call 0xb41c */
    a = (long)*(volatile int *)0x34BF;                       /* ld *(0x34bf),a */
    if (a == 0)                                              /* rc aeq */
        carry = 0;
    ar2 = (int *)(long)13456;                                /* stm #13456,ar2 */
    a = (long)*ar2;                                          /* ld *ar2,a */
    a &= -16L;                                               /* and #-16,a */
    a |= 1L;                                                 /* or #1,a */
    *ar2 = (int)(a & 0xFFFFL);                               /* stl a,*ar2 */
    *(volatile int *)0x348F = 10143;                         /* st #10143,*(0x348f) */
    *(volatile int *)0x2639 = *(volatile int *)0x34C9;       /* mvkd *(0x34c9),0x2639 */
    frag_B41C();                                             /* call 0xb41c */
    tc = (*(volatile int *)0x34BF == 4);                      /* cmpm *(0x34bf),#4 */
    if (!tc)                                                 /* rc ntc */
        carry = 0;
    ar2 = (int *)(long)13456;                                /* stm #13456,ar2 */
    a = (long)*ar2;                                          /* ld *ar2,a */
    a &= -16L;                                               /* and #-16,a */
    a |= 2L;                                                 /* or #2,a */
    *ar2 = (int)(a & 0xFFFFL);                               /* stl a,*ar2 */
    *(volatile int *)0x348F = 10455;                         /* st #10455,*(0x348f) */
    *(volatile int *)0x2639 = *(volatile int *)0x34C9;       /* mvkd *(0x34c9),0x2639 */
    frag_B41C();                                             /* call 0xb41c */
    (void)carry;
}
