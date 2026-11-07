/* ROM6 0xDA40 FRAG_DA40 -- 8w.
 * Verified encoding: src/rom6/kernel/da40_frag_da40.asm (recombine MATCH).
 * ORIGIN 0xDA40
 * EXPECT: E804 185A 765A 000D FF45 765A 0005 FC00
 *
 * Intent: Cell test plus preset. A = 4 AND cell 0x5A; cell 0x5A = 13; A == 0 stores 5 instead, then returns either way. The xc 2,aeq skip covers the 2-word st only (per ti-c54x op_xc: taken executes, not-taken skips exactly 2 words); the ret always runs, so 0xDA48 is NOT reached from here (correction: earlier revision tail-called it past the ret).
 */

void frag_DA40(void)
{
    int a = 4 & (unsigned short)*(volatile int *)0x5A; /* ld #4,a; and (Smem zero-ext) */
    *(volatile int *)0x5A = 13;              /* st #13,0x5a */
    if (a == 0)                                  /* xc 2,aeq */
        *(volatile int *)0x5A = 5;           /* st #5,0x5a */
    /* ret (both paths) */
}
