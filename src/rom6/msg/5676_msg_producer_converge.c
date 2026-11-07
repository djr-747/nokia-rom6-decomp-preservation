/* ROM6 0x5676 MSG_PRODUCER_CONVERGE_5676 -- 13w.
 * Verified encoding: src/rom6/msg/5676_msg_producer_converge.asm (recombine MATCH).
 * ORIGIN 0x5676
 * EXPECT: 60F8 250F 0050 F820 5683 7682 0001 68F8 2512 FDFF 68F8 2549 FDFF
 *
 * Intent: Flag gate plus double mask. Cell 0x250F != 80 jumps away to 0x5683 (bc ntc: has .asm, no C yet, forward extern). Else stores 1 through live-in AR2, clears bit 9 of cells 0x2512/0x2549 (andm #-513); falls into the next convergence head. 13w per .asm header (no yaml bound entry; recombine MATCH).
 */
extern void frag_5683(void);

void frag_5676(int *par2)
{
    if (*(volatile int *)0x250F != 80) {         /* cmpm, bc ntc */
        frag_5683();                             /* away, unbound C */
        return;
    }
    *par2 = 1;                                   /* st #1,*ar2 */
    *(volatile int *)0x2512 &= -513;         /* andm #-513 */
    *(volatile int *)0x2549 &= -513;         /* andm #-513 */
    /* falls through (no exit in span) */
}
