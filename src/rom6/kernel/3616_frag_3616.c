/* ROM6 0x3616 FRAG_3616 -- 4w.
 * Verified encoding: src/rom6/kernel/3616_frag_3616.asm (recombine MATCH).
 * ORIGIN 0x3616
 * EXPECT: 7714 0504 EC06 7694
 *
 * Intent: fill 7 DARAM cells at 1284 with the constant 64
 * (stm + rpt #6 + st #64,*ar4+).
 */
void frag_3616_fill(void)
{
    int i, *p = (int *)1284;              /* stm #1284,ar4 */
    for (i = 0; i < 7; i++)               /* rpt #6 */
        *p++ = 64;                        /* st #64,*ar4+ */
}
