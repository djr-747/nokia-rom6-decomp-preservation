/* ROM6 0xA3D5 ROUTINE_A3D5 -- 12w.
 * Verified encoding: src/rom6/kernel/a3d5_routine_a3d5.asm (recombine MATCH).
 * ORIGIN 0xA3D5
 * EXPECT: F074 0654 10F8 262A 1AF8 262B FC45 10F8 2512 FE00 F030 0200
 *
 * Intent: OR-combine cells 0x262A/0x262B into A; when the result is
 * zero (rc aeq conditional prefix, exact skip semantics in the .asm),
 * reload A from cell 0x2512 instead. Mask to bit 9 (and #512 runs in
 * the retd delay slot, so it applies on both paths), then return.
 * Callers F074 @A3C5/@A3CE/@B35A.
 */
extern void helper_0654(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

int routine_A3D5(void)
{
    int a;
    helper_0654();                               /* call 0x654 */
    a = *(volatile int *)0x262A |
        *(volatile int *)0x262B;                /* ld, or */
    if (a == 0)                                  /* rc aeq */
        a = *(volatile int *)0x2512;            /* ld */
    a &= 512;                                    /* retd delay slot */
    return a;                                    /* retd */
}
