/* ROM6 0x49F7 FRAG_49F7 -- 10w.
 * Verified encoding: src/rom6/kernel/49f7_frag_49f7.asm (recombine MATCH).
 * ORIGIN 0x49F7
 * EXPECT: 60F8 37B0 000F F820 4A4B 76F8 37B0 0000 F073 4A4B
 *
 * Intent: Clear-or-join gate. Cell 0x37B0 != 15 tail-enters FRAG_4A4B (bc 0x4a4b,ntc: has .asm, no C yet, forward extern). Else clears the cell, tail-enters FRAG_4A4B anyway (b). Bound 49F7-4A00.
 */
extern void frag_4A4B(void);

void frag_49F7(void)
{
    if (*(volatile int *)0x37B0 != 15) {         /* cmpm, bc ntc */
        frag_4A4B();                             /* tail, unbound C */
        return;
    }
    *(volatile int *)0x37B0 = 0;             /* st #0 */
    frag_4A4B();                                 /* b 0x4a4b tail */
}
