/* ROM6 0x85E4 BLOCK_COPY_85E4 -- 18w.
 * Verified encoding: src/rom6/kernel/85e4_block_copy_85e4.asm (recombine MATCH).
 * ORIGIN 0x85E4
 * EXPECT: E743 7712 30D0 EC05 E598 EC05 E5A8 7712 30D9 7713 30D7 771A 0005 F072 85F4 F074 85F6 FC00
 *
 * Intent: build a 12-cell block at 12496 from two source runs
 * (6 cells each via mvdd), then run 6 sub-rounds (rptb + BRC with
 * call 0x85F6). Pointers AR2/AR3 are re-seeded before the rounds.
 */
extern void sub_85F6(void);

void block_copy_85E4(int *src3, int *src4)
{
    int i, *ar2 = (int *)12496;
    for (i = 0; i < 6; i++)                       /* rpt #5 */
        *ar2++ = *src3++;                         /* mvdd *ar3+,*ar2+ */
    for (i = 0; i < 6; i++)                       /* rpt #5 */
        *ar2++ = *src4++;                         /* mvdd *ar4+,*ar2+ */
    for (i = 0; i < 6; i++)                       /* stm #5,brc; rptb */
        sub_85F6();                               /* call 0x85f6 */
    /* ret */
}
