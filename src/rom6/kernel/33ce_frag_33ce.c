/* ROM6 0x33CE FRAG_33CE -- 10w.
 * Verified encoding: src/rom6/kernel/33ce_frag_33ce.asm (recombine MATCH).
 * ORIGIN 0x33CE
 * EXPECT: 7714 2512 11F8 0011 6884 FFDF FF4C 6984 0020 FC00
 *
 * Intent: Flag-cell preset. AR4 = 9490; B = MMR cell 0x11; clears bit 5 there (andm -33); B != 0 sets bit 5 then returns, B == 0 returns with bit clear. The xc 2,bneq skip covers the 2-word orm only (per ti-c54x op_xc); the ret always runs, so 0x33D8 is NOT reached from here (correction: earlier revision tail-called it past the ret).
 */

void frag_33CE(void)
{
    int b = *(volatile int *)0x11;               /* stm; ld *(0x11),b */
    *(volatile int *)9490 &= -33;            /* andm #-33,*ar4 */
    if (b != 0)                                  /* xc 2,bneq */
        *(volatile int *)9490 |= 32;         /* orm #32,*ar4 */
    /* ret (both paths) */
}
