/* ROM6 0x4A01 FRAG_4A01 -- 17w.
 * Verified encoding: src/rom6/kernel/4a01_frag_4a01.asm (recombine MATCH).
 * ORIGIN 0x4A01
 * EXPECT: 60F8 34BF 0001 F830 4A12 60F8 34BF 0004 F830 4A12 60F8 366F 000F F830 4A1E F073 4A4B
 *
 * Intent: B-lane chain head. Cell 0x34BF == 1 or == 4 tail-enters FRAG_4A12 (bc tc pair, C: frag_4A12). Cell 0x366F == 15 tail-enters dark 0x4A1E (bc tc, forward extern). Else tail-enters FRAG_4A4B (b: has .asm, no C yet, forward extern). CMPM TC-on-equal per op_cmpm. Bound 4A01-4A11.
 */
extern void frag_4A12(void);
extern void frag_4A1E(void);
extern void frag_4A4B(void);

void frag_4A01(void)
{
    if (*(volatile int *)0x34BF == 1) {          /* cmpm, bc tc */
        frag_4A12();                             /* tail call */
        return;
    }
    if (*(volatile int *)0x34BF == 4) {          /* cmpm, bc tc */
        frag_4A12();                             /* tail call */
        return;
    }
    if (*(volatile int *)0x366F == 15) {         /* cmpm, bc tc */
        frag_4A1E();                             /* tail, dark */
        return;
    }
    frag_4A4B();                                 /* b 0x4a4b tail */
}
