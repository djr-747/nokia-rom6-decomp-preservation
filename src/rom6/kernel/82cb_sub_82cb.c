/* ROM6 0x82CB SUB_82CB -- 9w.
 * Verified encoding: src/rom6/kernel/82cb_sub_82cb.asm (recombine MATCH).
 * ORIGIN 0x82CB
 * EXPECT: F274 82D4 7716 DD33 F274 82FF 7716 DD33 FC00
 *
 * Intent: Twin delayed-call launcher. AR6 preset -8909 (each calld delay slot, executes before its call takes effect), calls 0x82D4 then 0x82FF, returns.
 */
extern void sub_82D4(void); /* joins 82d4_head_82d4; see docs/evidence/extern-triage.md */
extern void sub_82FF(void); /* joins 82fe_leaf43_82d4 interior @+0x1; see docs/evidence/extern-triage.md */

static int *G_AR6;

void sub_82CB(void)
{
    G_AR6 = (int *)-8909;                       /* calld delay slot */
    sub_82D4();                                  /* calld 0x82d4 */
    G_AR6 = (int *)-8909;                       /* calld delay slot */
    sub_82FF();                                  /* calld 0x82ff */
    /* ret */
}
