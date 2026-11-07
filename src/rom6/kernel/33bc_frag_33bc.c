/* ROM6 0x33BC FRAG_33BC -- 18w.
 * Verified encoding: src/rom6/kernel/33bc_frag_33bc.asm (recombine MATCH).
 * ORIGIN 0x33BC
 * EXPECT: 4811 7714 054F F130 0001 6884 7FFF FF4C 6984 8000 F030 0002 6884 FEFF FF44 6984 0100 FC00
 *
 * Intent: Two-bit flag pack. A = AR1 (live-in, as value); AR4 = 1359; B = A & 1; clears bit 15 there (andm #32767); B != 0 sets bit 15 and folds A &= 2 (xc 2,bneq covers orm plus and, exact); clears bit 8 (andm -257); A != 0 sets bit 8 (xc 2,aneq covers the 2-word orm); return.
 */
void frag_33BC(int *par1)
{
    int a = (int)par1;                           /* ldm ar1,a */
    int b = a & 1;                               /* and #1,a,b */
    *(volatile int *)1359 &= 32767;          /* stm; andm */
    if (b != 0) {                                /* xc 2,bneq */
        *(volatile int *)1359 |= 0x8000;     /* orm #-32768 */
        a &= 2;                                  /* and #2,a */
    }
    *(volatile int *)1359 &= -257;           /* andm #-257 */
    if (a != 0) {                                /* xc 2,aneq */
        *(volatile int *)1359 |= 256;        /* orm #256; ret */
        return;
    }
    /* ret */
}
