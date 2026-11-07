/* ROM6 0x864E SUB_864E -- 5w (wave-13: lane annexed).
 * Verified encoding: src/rom6/kernel/864e_msg_builder_864e.asm (recombine MATCH).
 * ORIGIN 0x864E
 * EXPECT: F074 0592 F074 8A45 FC00
 *
 * Intent: MSG_BUILDER_864E -- 5w lane. Head-calls dark SUB_0592 then runs SUB_8A45 (routine_8A45, C), returns. Defines SUB_864E for the 5420-lane caller.
 */
extern void sub_0592(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void sub_864E(void)
{
    sub_0592();                                    /* call 0x592 */
}
