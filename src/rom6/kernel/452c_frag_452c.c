/* ROM6 0x452C FRAG_452C -- 7w.
 * Verified encoding: src/rom6/kernel/452c_frag_452c.asm (recombine MATCH).
 * ORIGIN 0x452C
 * EXPECT: ED04 E801 F482 80F8 0537 F073 3028
 *
 * Intent: Shift-mode store plus join. ASM = 4 then ASM = A-low = 1 (ld pair; ASM is barrel-shift state, hardware, ends 1, noted); A = 1 stored to cell 0x537; tail-enters 0x3028 (b: has .asm, no C yet, forward extern). Bound 452C-4532.
 */
extern void frag_3028(void);

void frag_452C(void)
{
    /* ld #4,asm; ld #1,a; ld a,asm (ASM hardware state, ends 1) */
    *(volatile int *)0x537 = 1;              /* stl a,*(0x537) */
    frag_3028();                                 /* b 0x3028 tail */
}
