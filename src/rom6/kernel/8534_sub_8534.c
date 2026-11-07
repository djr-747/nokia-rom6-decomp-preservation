/* ROM6 0x8534 SUB_8534 -- 7w.
 * Verified encoding: src/rom6/kernel/8534_sub_8534.asm (recombine MATCH).
 * ORIGIN 0x8534
 * EXPECT: 7715 B743 7716 B76D F074 853B FC00
 *
 * Intent: Fanout launcher. AR5 preset -18621, AR6 preset -18579, then the 0x853B 26-way fanout, return.
 */
extern void fanout26_853B(void);

static int *G_AR5;
static int *G_AR6;

void sub_8534(void)
{
    G_AR5 = (int *)-18621;                      /* stm #-18621,ar5 */
    G_AR6 = (int *)-18579;                      /* stm #-18579,ar6 */
    fanout26_853B();                             /* call 0x853b */
    /* ret */
}
