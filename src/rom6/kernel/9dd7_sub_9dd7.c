/* ROM6 0x9DD7 SUB_9DD7 -- 6w.
 * Verified encoding: src/rom6/kernel/9dd7_sub_9dd7.asm (recombine MATCH).
 * ORIGIN 0x9DD7
 * EXPECT: FC4D F074 06C8 F074 9ED0 FC00
 *
 * Intent: Flag-gated double call. B is live-in; when zero (rc beq conditional prefix, exact skip semantics in the .asm) run helpers 0x6C8 then 0x9ED0, return.
 */
extern void helper_06C8(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_9ED0(void); /* joins 9ed0_wrap_9ed0; see docs/evidence/extern-triage.md */

void sub_9DD7(int b_in)
{
    if (b_in == 0) {                             /* rc beq */
        helper_06C8();                           /* call 0x6c8 */
        sub_9ED0();                              /* call 0x9ed0 */
    }
    /* ret */
}
