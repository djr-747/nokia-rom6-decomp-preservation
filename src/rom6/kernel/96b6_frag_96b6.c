/* ROM6 0x96B6 FRAG_96B6 -- 7w.
 * Verified encoding: src/rom6/kernel/96b6_frag_96b6.asm (recombine MATCH).
 * ORIGIN 0x96B6
 * EXPECT: 76F8 20FC 0006 E803 FE00 80F8 2201
 *
 * Intent: Delayed-return cell preset. Writes 6 to cell 0x20FC; A = 3 into cell 0x2201 in the retd delay slot (always runs); return. No params. Bound 96B6-96BC.
 */
void frag_96B6(void)
{
    *(volatile int *)0x20FC = 6;             /* st #6 */
    /* ld #3,a; retd delay: stl a,*(0x2201) (always runs) */
    *(volatile int *)0x2201 = 3;
    /* retd */
}
