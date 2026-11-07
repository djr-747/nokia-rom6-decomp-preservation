/* ROM6 0xAA2F FRAG_AA2F -- 18w.
 * Verified encoding: src/rom6/kernel/aa2f_frag_aa2f.asm (recombine MATCH).
 * ORIGIN 0xAA2F
 * EXPECT: F074 0688 61F8 263A 0200 FC30 10F8 0B67 FC44 61F8 051C 0003 FC30 F074 CF25 F074 CF4B FC00
 *
 * Intent: Bit-test call chain. Runs 0x688; bit 9 of cell 0x263A set skips the load (rc tc); else A = cell 0xB67, nonzero skips the next test (rc aneq); bits 0-1 of cell 0x51C set skip 0xCF25 (rc tc); else call 0xCF25; always call 0xCF4B, return. BITF any-bit TC per ti-c54x op_bitf.
 */
extern void sub_0688(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */
extern void sub_CF25(void); /* joins cf25_routine_cf25; see docs/evidence/extern-triage.md */
extern void sub_CF4B(void); /* joins cf4b_routine_cf4b; see docs/evidence/extern-triage.md */

void frag_AA2F(void)
{
    sub_0688();                                  /* call 0x688 */
    if ((*(volatile int *)0x263A & 512) != 0)    /* bitf, rc tc */
        goto L_CF4B;
    if (*(volatile int *)0xB67 != 0)             /* ld, rc aneq */
        goto L_CF4B;
    if ((*(volatile int *)0x51C & 3) != 0)       /* bitf, rc tc */
        goto L_CF4B;
    sub_CF25();                                  /* call 0xcf25 */
L_CF4B:
    sub_CF4B();                                  /* call 0xcf4b */
    /* ret */
}
