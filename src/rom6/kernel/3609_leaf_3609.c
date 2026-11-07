/* ROM6 0x3609 LEAF_3609 -- 13w.
 * Verified encoding: src/rom6/kernel/3609_leaf_3609.asm (recombine MATCH).
 * ORIGIN 0x3609
 * EXPECT: 10F8 0011 7714 051C 6984 1000 F844 3616 6884 2FBF 6984 0020 FC00
 *
 * Intent: Flag-cell preset plus tail. A = MMR cell 0x11; AR4 = 1308; sets bit 12 at address 1308 (orm #4096); nonzero A tail-calls FRAG_3616 (bc 0x3616,aneq), else clears bits except 0x2FBF (andm #12223) and sets bit 5 (orm #32), returns.
 */
extern void frag_3616_fill(void);

void leaf_3609(void)
{
    int a = *(volatile int *)0x11;               /* ld *(0x11),a */
    /* stm #1308,ar4; orm #4096,*ar4: bit 12 set at address 1308 */
    *(volatile int *)1308 |= 4096;
    if (a != 0) {                                /* bc 0x3616,aneq */
        frag_3616_fill();                        /* tail call */
        return;
    }
    *(volatile int *)1308 &= 12223;          /* andm #12223,*ar4 */
    *(volatile int *)1308 |= 32;             /* orm #32,*ar4 */
    /* ret */
}
