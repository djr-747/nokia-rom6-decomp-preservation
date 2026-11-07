/* ROM6 0x80FC SUB_80FC -- 12w.
 * Verified encoding: src/rom6/kernel/80fc_sub_80fc.asm (recombine MATCH).
 * ORIGIN 0x80FC
 * EXPECT: F074 059E 8815 F274 2282 7712 0005 F830 06F8 F274 7C9E 7712 264F FC00
 *
 * Intent: Helper pair with trap edge. A = sub_059E result into AR5; AR2 = 5 feeds sub_2282 (calld delay slot). TC as left by sub_2282 (modeled live-in): set jumps to 0x6F8, which reads all-zero reserved words (unprogrammed trap, no return modeled); clear runs the 0x7C9E counter step with AR2 = 9807 in its calld delay slot, returns.
 */
extern int sub_059E(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_2282(void); /* unowned @0x2282; see docs/evidence/extern-triage.md */
extern void trap_06F8(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern int counter_step_7C9E(int *par2);

static int *G_AR2;
static int *G_AR5;

void sub_80FC(int tc_live)
{
    int a = sub_059E();                          /* call 0x59e */
    G_AR5 = (int *)a;                            /* stlm a,ar5 */
    G_AR2 = (int *)5;                            /* calld delay slot */
    sub_2282();                                  /* calld 0x2282 */
    if (tc_live)                                 /* bc 0x6f8,tc */
        trap_06F8();                             /* zero-fill area: no return */
    G_AR2 = (int *)9807;                         /* calld delay slot */
    counter_step_7C9E(G_AR2);                    /* calld 0x7c9e */
    /* ret */
}
