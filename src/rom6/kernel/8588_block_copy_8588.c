/* ROM6 0x8588 BLOCK_COPY_8588 -- 37w.
 * Verified encoding: src/rom6/kernel/8588_block_copy_8588.asm (recombine MATCH).
 * ORIGIN 0x8588
 * EXPECT: E742 EC05 7192 30D0 7712 30D9 708A 0014 768A 30D4 768A 30D2 7682 30D0 F074 85AD 6B8A 0002 768A 30D0 768A 30D4 7682 30D2 F074 85AD 6B8A 0002 768A 30D2 768A 30D0 7682 30D4 F074 85AD FC00
 *
 * Intent: rolling crypto-block schedule feeding the 0x85AD fold.
 * Stream 6 source cells to register 0x30D0 (mvdk writes hit the
 * same cell; the register consumes the stream), spill one cell to
 * 0x14, lay a 3-cell constant block, call the fold, bump-and-step
 * the block down twice more with two more folds. All stores are
 * plain 16-bit cells; exact order in the .asm.
 */
extern void xor_fold_85AD(void); /* joins 85ad_xor_chain_85ad; see docs/evidence/extern-triage.md */

void block_copy_8588(int *src)
{
    int i, *ar2 = src;
    for (i = 0; i < 6; i++)                       /* rpt #5 */
        *(volatile int *)0x30D0 = *ar2++;        /* mvdk *ar2+,0x30d0 */
    ar2 = (int *)12505;                           /* stm #12505,ar2 */
    *(volatile int *)0x14 = *ar2--;               /* mvkd 0x14,*ar2- */
    *ar2-- = 12500;                               /* st #12500,*ar2- */
    *ar2-- = 12498;                               /* st #12498,*ar2- */
    *ar2 = 12496;                                 /* st #12496,*ar2 */
    xor_fold_85AD();                              /* call 0x85ad */
    *ar2 += 2; ar2--;                             /* addm #2,*ar2- */
    *ar2-- = 12496;
    *ar2-- = 12500;
    *ar2 = 12498;
    xor_fold_85AD();
    *ar2 += 2; ar2--;
    *ar2-- = 12498;
    *ar2-- = 12496;
    *ar2 = 12500;
    xor_fold_85AD();
    /* ret */
}
