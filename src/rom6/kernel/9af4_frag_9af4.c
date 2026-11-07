/* ROM6 0x9AF4 FRAG_9AF4 -- 8w.
 * Verified encoding: src/rom6/kernel/9af4_frag_9af4.asm (recombine MATCH).
 * ORIGIN 0x9AF4
 * EXPECT: 76F8 20FA FFFF 10F8 20FE FE00 F010 001E
 *
 * Intent: FRAG_9AF4 constant-return sliver (8w, bcd-entered per symbols). Cell 0x20FA = -1; A = cell 0x20FE minus 30 in the retd delay slot (always runs); returns A (int out-channel per A482 precedent; the bcd callers' use is dark).
 */
int frag_9AF4(void)
{
    int a;
    *(volatile int *)0x20FA = -1;              /* st */
    a = *(volatile int *)0x20FE;               /* ld */
    a -= 30;                                       /* retd delay slot */
    return a;                                      /* retd */
}
