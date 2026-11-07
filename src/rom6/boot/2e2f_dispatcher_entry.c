/* ROM6 0x2E2F DISPATCHER_ENTRY -- 10w.
 * Verified encoding: src/rom6/boot/2e2f_dispatcher_entry.asm (recombine MATCH).
 * ORIGIN 0x2E2F
 * EXPECT: F074 05A0 61F8 054D 0004 FC30 70F8 0853 054C FC00
 *
 * Intent: dispatcher head. Helper call, then a flag-gated register
 * move: if bit 2 of 0x54D is set (bitf + rc tc conditional prefix,
 * exact skip semantics in the .asm), copy cell 0x54C to *(0x853).
 * Return either way.
 */
extern void helper_05A0(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void dispatcher_entry_2E2F(void)
{
    helper_05A0();                               /* call 0x5a0 */
    if (*(volatile int *)0x54D & 4)             /* bitf, rc tc */
        *(volatile int *)0x853 =
            *(volatile int *)0x54C;             /* mvdk 0x54c,*(0x853) */
    /* ret */
}
