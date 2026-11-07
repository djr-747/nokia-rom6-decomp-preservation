/* ROM6 0xA4D5 MSG_SETUP_B -- 9w.
 * Verified encoding: src/rom6/msg/a4d5_msg_setup_b.asm (recombine MATCH).
 * ORIGIN 0xA4D5
 * EXPECT: F074 0658 7712 262B 1082 FC45 F074 4944 FC00
 *
 * Intent: setup gate B. Helper call, load status cell 9771; when it
 * reads zero (rc aeq conditional prefix, exact skip semantics in the
 * .asm), call 0x4944, then return.
 */
extern void helper_0658(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_4944(void); /* joins 4944_sub_4944; see docs/evidence/extern-triage.md */

void msg_setup_b_A4D5(void)
{
    int v;
    helper_0658();                               /* call 0x658 */
    v = *(volatile int *)9771;                  /* stm, ld *ar2,a */
    if (v == 0)                                  /* rc aeq */
        sub_4944();                              /* call 0x4944 */
    /* ret */
}
