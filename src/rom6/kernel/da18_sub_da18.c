/* ROM6 0xDA18 SUB_DA18 -- 9w.
 * Verified encoding: src/rom6/kernel/da18_sub_da18.asm (recombine MATCH).
 * ORIGIN 0xDA18
 * EXPECT: F310 0001 FA4C DA23 6B59 0001 765A 0003 FE00
 *
 * Intent: Countdown plus mid-span entry. B decrements (live-in); the cell 0x59 tick and cell 0x5A = 3 preset run in the bcd delay slots (always execute); then a nonzero result enters FRAG_DA21 mid-span at DA23 (skips its st #7,0x58 init), else delayed return. DA23 target has no C binding yet -- forward extern per convention.
 */
extern void frag_DA21_at_DA23(void);

void sub_DA18(int b_in)
{
    int b = b_in - 1;                            /* sub #1,b */
    *(volatile int *)0x59 += 1;                /* bcd delay slot: always */
    *(volatile int *)0x5A = 3;                 /* bcd delay slot: always */
    if (b != 0)                                  /* bcd 0xda23,bneq */
        frag_DA21_at_DA23();                     /* tail entry, no C yet */
    /* retd */
}
