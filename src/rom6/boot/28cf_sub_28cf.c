/* ROM6 0x28CF SUB_28CF -- 7w.
 * Verified encoding: src/rom6/boot/28cf_sub_28cf.asm (recombine MATCH).
 * ORIGIN 0x28CF
 * EXPECT: 7712 0488 60F8 250F 0022 F820 2917
 *
 * Intent: COBBA bring-up head, the hottest boot entry (10,681 trace
 * hits, 8210 boot-to-registration run). Point AR2 at 1160, compare
 * cell 0x250F against 34: mismatch chains to stage 0x2917, match
 * falls through to the next bring-up span.
 */
extern void stage_2917(void);   /* chained continuation, extern to link */

void sub_28CF_bringup(int **pp2)
{
    *pp2 = (int *)1160;                       /* stm #1160,ar2 */
    if (*(volatile int *)0x250F != 34)        /* cmpm, bc 0x2917 ntc */
        stage_2917();
    /* fall-through: next bring-up span */
}
