/* ROM6 0x457F ROUTINE_457F -- 17w.
 * Verified encoding: src/rom6/kernel/457f_routine_457f.asm (recombine MATCH).
 * ORIGIN 0x457F
 * EXPECT: F074 0594 6FF8 0529 0D58 F330 00FF FC4D 7713 0527 7714 2F00 EC02 E59A F074 4533 FC00
 *
 * Intent: Shifted test plus copy-call. Runs 0x594; B = cell 0x529 >> 8 (arithmetic, ld shift -8) masked to a byte; zero returns early (rc beq); else AR3 = 1319, AR4 = 12032, 3 words (rpt #2) AR3 to AR4 (mvdd *ar3+,*ar4+), call 0x4533, return.
 */
extern void helper_0594(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_4533(void); /* joins 4533_frag_4533; see docs/evidence/extern-triage.md */

static int *G_AR3;
static int *G_AR4;

void routine_457F(void)
{
    int b = (*(volatile int *)0x529 >> 8) & 255; /* ld, and */
    helper_0594();                               /* call 0x594 */
    if (b == 0)                                  /* rc beq */
        return;
    G_AR3 = (int *)1319;                         /* stm #1319,ar3 */
    G_AR4 = (int *)12032;                        /* stm #12032,ar4 */
    {
        int i;
        int *src = G_AR3, *dst = G_AR4;
        for (i = 0; i < 3; i++)                  /* rpt #2 */
            *dst++ = *src++;                    /* mvdd */
    }
    sub_4533();                                  /* call 0x4533 */
    /* ret */
}
