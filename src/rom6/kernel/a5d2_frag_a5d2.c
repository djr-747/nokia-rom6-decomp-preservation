/* ROM6 0xA5D2 FRAG_A5D2 -- 15w.
 * Verified encoding: src/rom6/kernel/a5d2_frag_a5d2.asm (recombine MATCH).
 * ORIGIN 0xA5D2
 * EXPECT: F074 065A 60F8 262A 00A0 FC20 10F8 036D 08F8 250D FC42 69F8 2639 0008 FC00
 *
 * Intent: Measure-delta flag. Runs helper 0x65A; when cell 0x262A reads 160 (cmpm sets TC on equal per ti-c54x op_cmpm; rc ntc skips only when unequal), A = cell 0x36D minus cell 0x250D; when negative (rc ageq skips when A >= 0) sets bit 3 of cell 0x2639, returns.
 */
extern void helper_065A(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void frag_A5D2(void)
{
    int a;
    helper_065A();                               /* call 0x65a */
    if (*(volatile int *)0x262A != 160)          /* cmpm, rc ntc */
        return;
    a = *(volatile int *)0x36D -
        *(volatile int *)0x250D;               /* ld, sub */
    if (a >= 0)                                  /* rc ageq */
        return;
    *(volatile int *)0x2639 |= 8;            /* orm #8 */
    /* ret */
}
