/* ROM6 0x573B SUB_573B -- 26w.
 * Verified encoding: src/rom6/kernel/573b_sub_573b.asm (recombine MATCH).
 * ORIGIN 0x573B
 * EXPECT: F074 059C 7712 0918 E8F0 18F8 250F 60F8 0008 0020 FA30 574F 11F8 2651 7712 0917 60F8 2510 0080 FC20 0982 FC4C 69F8 2628 0020 FC00
 *
 * Intent: Delayed-branch cell test. Runs 0x59C; AR2 = 2328; A = 240 AND cell 0x250F; TC = (AL == 32) (cmpm on the AL-alias cell 0x8, TC-on-equal per ti-c54x op_cmpm). The bcd delay slots always execute (B = cell 0x2651, AR2 = 2327); TC set enters at the sub (bcd 0x574f,tc, in-span). Else cell 0x2510 == 128 gates the same sub (rc ntc); then B != 0 skips the flag set (rc bneq); else sets bit 5 of cell 0x2628; return.
 */
extern void sub_059C(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void sub_573B(void)
{
    int b;
    int tc;
    sub_059C();                                  /* call 0x59c */
    /* stm #2328,ar2; ld #240,a; and *(0x250f),a */
    (void)(240 & *(volatile int *)0x250F);
    tc = (*(volatile int *)0x8 == 32);           /* cmpm */
    b = *(volatile int *)0x2651;             /* bcd delay slot 1: always */
    /* stm #2327,ar2 (bcd delay slot 2: always) */
    {
        int *ar2 = (int *)2327;
        if (tc || (*(volatile int *)0x2510 == 128)) { /* bcd / cmpm+rc */
            b -= *ar2;                          /* sub *ar2,b */
        }
        if (b != 0)                              /* rc bneq */
            return;
    }
    *(volatile int *)0x2628 |= 32;           /* orm #32 */
    /* ret */
}
