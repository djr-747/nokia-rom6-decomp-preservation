/* ROM6 0xB5FF FRAG_B5FF -- 6w.
 * Verified encoding: src/rom6/kernel/b5ff_frag_b5ff.asm (recombine MATCH).
 * ORIGIN 0xB5FF
 * EXPECT: 76F8 04C5 0003 F074 06B4 FC00
 *
 * Intent: Cell preset plus helper call. Sets cell 0x4C5 = 3, calls 0x6B4, returns.
 */
extern void sub_06B4(void);

void frag_B5FF(void)
{
    *(volatile int *)0x4C5 = 3;              /* st #3,*(0x4c5) */
    sub_06B4();                                  /* call 0x6b4 */
    /* ret */
}
