/* ROM6 0xA806 LEAF_A806 -- 15w.
 * Verified encoding: src/rom6/kernel/a806_leaf_a806.asm (recombine MATCH).
 * ORIGIN 0xA806
 * EXPECT: F074 0660 10F8 0565 08F8 0915 FC44 61F8 2629 1000 FC20 71F8 022B 038A FC00
 *
 * Intent: Delta test plus bit move. Runs helper 0x660; A = cell 0x565 minus cell 0x915; nonzero skips ahead (rc aneq); when set, tests bit 12 of cell 0x2629 (bitf, TC = bit set); bit clear skips (rc ntc), else copies cell 0x22B to 0x38A (mvdk), returns.
 */
extern void helper_0660(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void leaf_A806(void)
{
    int a = *(volatile int *)0x565 -
              *(volatile int *)0x915;          /* ld, sub (after call) */
    helper_0660();                               /* call 0x660 */
    if (a != 0)                                  /* rc aneq */
        return;
    if ((*(volatile int *)0x2629 & 4096) == 0)   /* bitf, rc ntc */
        return;
    *(volatile int *)0x38A =
        *(volatile int *)0x22B;                /* mvdk */
    /* ret */
}
