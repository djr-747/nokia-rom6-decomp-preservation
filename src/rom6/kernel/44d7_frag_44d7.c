/* ROM6 0x44D7 FRAG_44D7 -- 16w.
 * Verified encoding: src/rom6/kernel/44d7_frag_44d7.asm (recombine MATCH).
 * ORIGIN 0x44D7
 * EXPECT: F074 2E2F 7713 2F00 F028 000D 1AF8 0568 7714 0074 8083 F274 2C88 7715 0002 FC00
 *
 * Intent: Dispatcher plus shifted-OR store. Runs the 0x2E2F dispatcher entry; AR3 = 12032; A = (13 << 8) | cell 0x568; AR4 = 116; stores A through AR3; calls 0x2C88 with AR5 = 2 in the calld delay slot (executes first), returns.
 */
extern void dispatcher_entry_2E2F(void);
extern void sub_2C88(void);

static int *G_AR3;
static int *G_AR4;
static int *G_AR5;

void frag_44D7(void)
{
    int a;
    dispatcher_entry_2E2F();                    /* call 0x2e2f */
    G_AR3 = (int *)12032;                        /* stm #12032,ar3 */
    a = (13 << 8) | *(volatile int *)0x568;  /* ld, or */
    G_AR4 = (int *)116;                          /* stm #116,ar4 */
    *G_AR3 = a;                                  /* stl a,*ar3 */
    G_AR5 = (int *)2;                            /* calld delay slot */
    sub_2C88();                                  /* calld 0x2c88 */
    /* ret */
}
