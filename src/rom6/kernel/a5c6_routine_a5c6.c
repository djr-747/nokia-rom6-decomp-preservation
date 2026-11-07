/* ROM6 0xA5C6 ROUTINE_A5C6 -- 11w.
 * Verified encoding: src/rom6/kernel/a5c6_routine_a5c6.asm (recombine MATCH).
 * ORIGIN 0xA5C6
 * EXPECT: F074 065A 10F8 262D FC45 E900 F074 4BA8 76F8 262D 0000 FC00
 *
 * Intent: Cell test plus call. Runs helper 0x65A; A = cell 0x262D, zero returns at once (rc aeq: A == 0 returns, cell NOT cleared); else B = 0, calls 0x4BA8 with (A = cell, B = 0), clears cell 0x262D, returns.
 */
extern void helper_065A(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_4BA8(int a_live, int b_live);

void routine_A5C6(void)
{
    int a;
    helper_065A();                               /* call 0x65a */
    a = *(volatile int *)0x262D;                 /* ld *(0x262d),a */
    if (a == 0)                                  /* rc aeq */
        return;
    sub_4BA8(a, 0);                              /* ld #0,b; call 0x4ba8 */
    *(volatile int *)0x262D = 0;             /* st #0,*(0x262d) */
    /* ret */
}
