/* ROM6 0xA3C5 ROUTINE_A3C5 -- 9w.
 * Verified encoding: src/rom6/kernel/a3c5_routine_a3c5.asm (recombine MATCH).
 * ORIGIN 0xA3C5
 * EXPECT: F074 A3D5 7712 0914 FB44 39A4 7713 2514 FC00
 *
 * Intent: OR-measure plus conditional call. Runs ROUTINE_A3D5; AR2 = 2324 preset, then calls 0x39A4 only when the measure is nonzero (ccd aneq, AR3 = 9492 preset in the delay slot, always executes), return.
 */
extern int routine_A3D5(void);
extern void sub_39A4(void); /* joins 39a4_routine_pa60_57; see docs/evidence/extern-triage.md */

static int *G_AR2;
static int *G_AR3;

void routine_A3C5(void)
{
    int a = routine_A3D5();                      /* call 0xa3d5 */
    G_AR2 = (int *)2324;                         /* stm #2324,ar2 */
    G_AR3 = (int *)9492;                         /* ccd delay slot: always */
    if (a != 0)                                  /* ccd 0x39a4,aneq */
        sub_39A4();
    /* ret */
}
