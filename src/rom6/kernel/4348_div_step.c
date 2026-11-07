/* ROM6 0x4348 DIV_STEP_4348 -- 7w.
 * Verified encoding: src/rom6/kernel/4348_div_step.asm (recombine MATCH).
 * ORIGIN 0x4348
 * EXPECT: F074 0606 EC0E 1E84 FE00 F030 7FFF
 *
 * Intent: one nonrestoring-divide iteration block. The boot-page helper
 * at 0x0606 runs first (opaque precondition, extern until boot/ links),
 * then 15 SUBC conditional-subtract steps of A against *AR4 (rpt #14),
 * return-delayed with an AND #32767 spill in the delay slots that keeps
 * A nonnegative on exit.
 */
extern void helper_0606(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern int subc_step(int a, int divisor);   /* one SUBCDop, exact carry
                                             * semantics in the .asm */

int div_step(int a, int divisor)
{
    int i;
    helper_0606();                        /* call 0x606 */
    for (i = 0; i < 15; i++)              /* rpt #14 / subc *ar4,a */
        a = subc_step(a, divisor);
    return a & 32767;                     /* retd / and #32767,a */
}
