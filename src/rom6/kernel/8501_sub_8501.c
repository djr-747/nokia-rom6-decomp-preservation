/* ROM6 0x8501 SUB_8501 -- 7w.
 * Verified encoding: src/rom6/kernel/8501_sub_8501.asm (recombine MATCH).
 * ORIGIN 0x8501
 * EXPECT: 7715 B75B 7716 B76D F074 853B FC00
 *
 * Intent: fanout launcher. Point AR5/AR6 at the high-memory
 * buffers 0xB75B/0xB76D (stm with negative immediates), run the
 * 0x853B fanout driver, return. AR4 (the other fanout input)
 * arrives from the caller.
 */
extern void fanout26_853B(int **pp1, int *ar4, int *ar6);

void sub_8501(int **pp1, int *ar4)
{
    int *ar5 = (int *)0xB75B;              /* stm #-18597,ar5 */
    int *ar6 = (int *)0xB76D;              /* stm #-18579,ar6 */
    (void)ar5;                             /* consumed downstream */
    fanout26_853B(pp1, ar4, ar6);          /* call 0x853b */
    /* ret */
}
