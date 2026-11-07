/* ROM6 0x4007 PORT0_TXN -- 2w call head, one EXPECT.
 * Verified encoding: src/rom6/kernel/4007_port0_txn.asm (recombine MATCH).
 * ORIGIN 0x4007
 * EXPECT: F074 0652
 *
 * Intent: Port-0 transaction head (the 2-word span is the entry call;
 * the strobe/poll body described in the .asm header lives in following
 * words outside this span). Runs dark SUB_0652 (call, C: sub_0652 per
 * 40A1). Falls into 0x4009 exterior. Bound 4007-4008.
 */
extern void sub_0652(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void port0_txn_4007(void)
{
    sub_0652();                                        /* call 0x652 */
    /* falls into 0x4009 exterior */
}
