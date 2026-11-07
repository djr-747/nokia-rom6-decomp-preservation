/* ROM6 0x68B7 ROUTINE_68B7 -- 19w.
 * Verified encoding: src/rom6/kernel/68b7_routine_68b7.asm (recombine MATCH).
 * ORIGIN 0x68B7
 * EXPECT: E900 1080 F844 68C9 1081 0886 7712 0915 0882 F846 68C9 1081 F000 0003 0882 F843 68C9 E901 FC00
 *
 * Intent: Range flag 14c. B = 0; A = *AR0 (live-in); nonzero returns 0 (bc 0x68c9,aneq). A = *AR1 minus *AR6 (live-ins) minus *(2325); positive returns 0 (bc agt). A = *AR1 + 3 minus *(2325); negative returns 0 (bc alt). Else B = 1, return. All three branches fan into the exit ret (bound 68B7-68C9).
 */
int routine_68B7(int *par0, int *par1, int *par6)
{
    int a = *par0;                               /* ld #0,b; ld *ar0,a */
    if (a != 0)                                  /* bc 0x68c9,aneq */
        return 0;
    a = *par1 - *par6;                           /* ld; sub *ar6,a */
    a -= *(volatile int *)2325;              /* stm; sub *ar2,a */
    if (a > 0)                                   /* bc 0x68c9,agt */
        return 0;
    a = *par1 + 3 - *(volatile int *)2325;   /* ld; add; sub */
    if (a < 0)                                   /* bc 0x68c9,alt */
        return 0;
    return 1;                                    /* ld #1,b; ret */
}
