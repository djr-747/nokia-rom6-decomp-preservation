/* ROM6 0xA3E1 ROUTINE_A3E1 -- 15w.
 * Verified encoding: src/rom6/kernel/a3e1_routine_a3e1.asm (recombine MATCH).
 * ORIGIN 0xA3E1
 * EXPECT: F074 0656 10F8 262A FC45 7212 2628 11F8 2659 68F8 0012 0400 F074 AB82 FC00
 *
 * Intent: load cell 0x262A; when zero (rc aeq conditional prefix,
 * exact skip semantics in the .asm) preset AR2 from cell 0x2628.
 * Only the mvdm is skipped when nonzero -- the tail always runs:
 * B = cell 0x2659, clear cell 0x12 except bit 10 (andm #1024),
 * call 0xAB82, return. Callers 7x F074; abuts MEASUREMENT_A3F0.
 */
extern void helper_0656(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_AB82(void); /* joins ab82_shared_worker_596; see docs/evidence/extern-triage.md */

static int *G_AR2;

void routine_A3E1(void)
{
    int a, b;
    helper_0656();                               /* call 0x656 */
    a = *(volatile int *)0x262A;                /* ld */
    if (a == 0)                                  /* rc aeq */
        G_AR2 = (int *)(*(volatile int *)0x2628); /* mvdm, skipped when a != 0 */
    b = *(volatile int *)0x2659;                /* ld */
    *(volatile int *)0x12 &= 1024;              /* andm */
    (void)b;
    sub_AB82();                                  /* call 0xab82 */
    /* ret */
}
