/* ROM6 0x6987 ROUTINE_6987 -- 4w.
 * Verified encoding: src/rom6/kernel/6987_routine.asm (recombine MATCH).
 * ORIGIN 0x6987
 * EXPECT: 7713 2617 E501 FC00
 *
 * Intent: copy one 16-bit cell from the caller pointer (AR2) to the
 * fixed DARAM cell 0x2617. Single mvdd, no loop. The stm word (2617)
 * is an address constant, not code.
 */
void daram_cell_store(int *src)
{
    *(volatile int *)0x2617 = *src;   /* stm #9751,ar3 / mvdd *ar2,*ar3 */
}
