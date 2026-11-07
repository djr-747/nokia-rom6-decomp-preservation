/* ROM6 0x4590 ROUTINE_4590 -- 16w.
 * Verified encoding: src/rom6/kernel/4590_routine_4590.asm (recombine MATCH).
 * ORIGIN 0x4590
 * EXPECT: F074 0594 7713 30E5 7693 3200 F348 0001 818B 7715 0004 F274 2C88 7714 0074 FC00
 *
 * Intent: Shifted-store pair plus call. Runs helper 0x594; AR3 = 12517; stores 12800 with post-increment; B = B | (1 << 8), stored with post-decrement; AR5 = 4 feeds 0x2C88 with AR4 = 116 in the calld delay slot (executes first), returns.
 */
extern void helper_0594(void);
extern void sub_2C88(void);

static int *G_AR3;
static int *G_AR5;
static int *G_AR4;

void routine_4590(int b_in)
{
    int b = b_in;
    helper_0594();                               /* call 0x594 */
    G_AR3 = (int *)12517;                        /* stm #12517,ar3 */
    *G_AR3++ = 12800;                            /* st #12800,*ar3+ */
    b |= (1 << 8);                               /* or #1,8,b */
    *G_AR3-- = b;                                /* stl b,*ar3- */
    G_AR5 = (int *)4;                            /* stm #4,ar5 */
    G_AR4 = (int *)116;                          /* calld delay slot */
    sub_2C88();                                  /* calld 0x2c88 */
    /* ret */
}
