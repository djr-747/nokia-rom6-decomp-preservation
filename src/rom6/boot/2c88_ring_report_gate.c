/* ROM6 0x2C88 RING_REPORT_GATE -- 2w.
 * Verified encoding: src/rom6/boot/2c88_ring_report_gate.asm (recombine MATCH).
 * ORIGIN 0x2C88
 * EXPECT: F074 0622
 *
 * Intent: Ring-report gate head: CALL 0x622 (RAM-resident mini-kernel, zeros
 * in-mask, forward extern); falls into the 2C8A ring-arith span (abuts at
 * 0x2C8A, owned by boot/2c8a_ring_arith_2c8a.asm). Entry: Block20 invokes with
 * 0x74/0x36 (SIML validation report) per asm evidence.
 */
extern void sub_0622(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void ring_report_2C88(void)
{
    sub_0622();                                            /* call 0x622 (RAM) */
    /* falls into 2c8a_ring_arith_2c8a (abuts at 0x2C8A) */
}
