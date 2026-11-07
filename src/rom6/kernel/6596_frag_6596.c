/* ROM6 0x6596 FRAG_6596 -- 15w.
 * Verified encoding: src/rom6/kernel/6596_frag_6596.asm (recombine MATCH).
 * ORIGIN 0x6596
 * EXPECT: F110 0001 F84B 65AA F110 0004 F84A 65AA 61F8 2627 0100 F820 65B1 F073 65AA
 *
 * Intent: Range gate with three tails. B = A-live-in - 1, negative tail-enters FRAG_65AA (bc 0x65aa,blt: has .asm, no C yet, forward extern). B = A - 4, non-negative tail-enters FRAG_65AA too (bc bgeq). Bit 8 of cell 0x2627 clear jumps away to dark 0x65B1 (bc ntc, forward extern). Else tail-enters FRAG_65AA anyway (b). SUB dst = src minus operand per op_sub; B dead after (noted). Bound 6596-65A4.
 */
extern void frag_65AA(void); /* joins 65aa_frag_65aa; see docs/evidence/extern-triage.md */
extern void frag_65B1(void); /* joins 65aa_frag_65aa interior @+0x7; see docs/evidence/extern-triage.md */

void frag_6596(int a_live)
{
    /* sub #1,a,b (B dead); bc blt */
    if (a_live - 1 < 0) {
        frag_65AA();                             /* tail, unbound C */
        return;
    }
    /* sub #4,a,b (B dead); bc bgeq */
    if (a_live - 4 >= 0) {
        frag_65AA();                             /* tail, unbound C */
        return;
    }
    if ((*(volatile int *)0x2627 & 256) == 0) {  /* bitf, bc ntc */
        frag_65B1();                             /* away, dark */
        return;
    }
    frag_65AA();                                 /* b 0x65aa tail */
}
