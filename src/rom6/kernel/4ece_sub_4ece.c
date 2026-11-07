/* ROM6 0x4ECE SUB_4ECE -- 18w.
 * Verified encoding: src/rom6/kernel/4ece_sub_4ece.asm (recombine MATCH).
 * ORIGIN 0x4ECE
 * EXPECT: 11F8 2F1D F84C 4ED5 69F8 264E 0200 61F8 2628 0010 81F8 09C7 E900 FD30 E901 FE00 81F8 09C6
 *
 * Intent: Conditional one-store with delayed return. B = cell 0x2F1D, nonzero jumps away to dark 0x4ED5 (bc bneq, forward extern). Else sets bit 9 of cell 0x264E; B = 0, or 1 when bit 4 of cell 0x2628 is set (bitf plus xc 1,tc pair, BITF any-bit TC per op_bitf; TC live in-span); stores B to cell 0x9C7; retd delay slot stores the same B to cell 0x9C6 (always runs); return. Bound 4ECE-4EDF.
 */
extern void frag_4ED5(void);

void sub_4ECE(void)
{
    int b = *(volatile int *)0x2F1D;         /* ld *(0x2f1d),b */
    if (b != 0) {                                /* bc 0x4ed5,bneq */
        frag_4ED5();                             /* away, dark */
        return;
    }
    *(volatile int *)0x264E |= 512;          /* orm #512 */
    /* bitf *(0x2628),#16; ld #0,b; xc 1,tc; ld #1,b */
    b = ((*(volatile int *)0x2628 & 16) != 0) ? 1 : 0;
    *(volatile int *)0x9C7 = b;              /* stl b,*(0x9c7) */
    /* retd delay: stl b,*(0x9c6) (always runs) */
    *(volatile int *)0x9C6 = b;
    /* retd */
}
