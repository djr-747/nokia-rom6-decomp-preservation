/* ROM6 0x712D FLAG_GATE_712D -- 19w.
 * Verified encoding: src/rom6/kernel/712d_flag_gate_712d.asm (recombine MATCH).
 * ORIGIN 0x712D
 * EXPECT: F074 05B4 60F8 34BF 0000 FC30 61F8 3490 0002 FC30 60F8 34BF 0004 F830 7140 61F8 3490 0001 FC00
 *
 * Intent: Flag gate with tail-call. Runs 0x5B4; cell 0x34BF == 0 skips the first test (cmpm sets TC on equal per ti-c54x op_cmpm; rc tc); bit 1 of cell 0x3490 set skips the second compare (rc tc); cell == 4 tail-calls FRAG_7140 (bc 0x7140,tc, exact); else tests bit 0 of cell 0x3490 (bitf, TC result unused in span), returns.
 */
extern void helper_05B4(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void frag_7140(void);

void flag_gate_712D(void)
{
    int tc;
    helper_05B4();                               /* call 0x5b4 */
    if (*(volatile int *)0x34BF != 0) {          /* cmpm, rc tc */
        tc = (*(volatile int *)0x3490 & 2) != 0; /* bitf */
        if (tc)                                  /* rc tc */
            return;
    }
    if (*(volatile int *)0x34BF == 4) {          /* cmpm */
        frag_7140();                             /* bc 0x7140,tc tail call */
        return;
    }
    /* bitf *(0x3490),#1: TC set, unused; ret */
}
