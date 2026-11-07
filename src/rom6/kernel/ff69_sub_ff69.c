/* ROM6 0xFF69 SUB_FF69 -- 15w.
 * Verified encoding: src/rom6/kernel/ff69_sub_ff69.asm (recombine MATCH).
 * ORIGIN 0xFF69
 * EXPECT: 7713 000E 770E 5555 F074 FF61 770E AAAA F074 FF61 7713 0012 F074 FF61 FC00
 *
 * Intent: Triple-call driver. AR3 = 14 with T = 21845 feeds first 0xFF61 call, T = -21846 feeds the second, AR3 = 18 feeds the third, returns.
 */
extern void sub_FF61(void);

static int *G_AR3;
static int G_T;

void sub_FF69(void)
{
    G_AR3 = (int *)14;                           /* stm #14,ar3 */
    G_T = 21845;                                 /* stm #21845,t */
    sub_FF61();                                  /* call 0xff61 */
    G_T = -21846;                                /* stm #-21846,t */
    sub_FF61();                                  /* call 0xff61 */
    G_AR3 = (int *)18;                           /* stm #18,ar3 */
    sub_FF61();                                  /* call 0xff61 */
    /* ret */
}
