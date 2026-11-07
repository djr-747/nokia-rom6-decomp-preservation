/* ROM6 0x697F DARAM_SAVE_RESTORE -- 8w.
 * Verified encoding: src/rom6/kernel/697f_daram_save_restore.asm (recombine MATCH).
 * ORIGIN 0x697F
 * EXPECT: 7713 053C 7712 2614 E510 7683 0000 FC00
 *
 * Intent: copy the 16-bit DARAM cell 0x053C to 0x2614, then clear the
 * source cell. Single mvdd plus clear, no loop.
 */
void daram_save_restore(void)
{
    *(volatile int *)0x2614 = *(volatile int *)0x053C;   /* stm/stm/mvdd */
    *(volatile int *)0x053C = 0;                          /* st #0,*ar3 */
}
