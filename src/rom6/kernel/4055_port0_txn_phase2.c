/* ROM6 0x4055 PORT0_TXN_PHASE2 -- 2w call slot, one EXPECT.
 * Verified encoding: src/rom6/kernel/4055_port0_txn_phase2.asm (recombine MATCH).
 * ORIGIN 0x4055
 * EXPECT: F074 0652
 *
 * Intent: Label inside PORT0_TXN, not an entry (per .asm header).
 * Runs dark SUB_0652 (call, C: sub_0652 per 40A1). Falls into 0x4057
 * exterior. Bound 4055-4056.
 */
extern void sub_0652(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void port0_txn_phase2_4055(void)
{
    sub_0652();                                        /* call 0x652 */
    /* falls into 0x4057 exterior */
}
