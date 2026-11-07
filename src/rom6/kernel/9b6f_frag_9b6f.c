/* ROM6 0x9B6F FRAG_9B6F -- 3w.
 * Verified encoding: src/rom6/kernel/9b6f_frag_9b6f.asm (recombine MATCH).
 * ORIGIN 0x9B6F
 * EXPECT: 1192 6D8C FE00
 *
 * Intent: Post-increment load with pointer adjust. B = *AR2++ then steps AR4 back (mar); delayed return whose two delay slots fall through into the next module words (not part of this span).
 */
int frag_9B6F(int **ppar2, int **ppar4)
{
    int b = **ppar2;                           /* ld *ar2+,b */
    (*ppar2)++;
    (*ppar4)--;                                 /* mar *ar4- */
    /* retd: delay slots execute the following module words (out of span) */
    return b;
}
