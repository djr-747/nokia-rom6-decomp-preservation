/* ROM6 0x397B FRAG_397B -- 11w.
 * Verified encoding: src/rom6/kernel/397b_frag_397b.asm (recombine MATCH).
 * ORIGIN 0x397B
 * EXPECT: 4913 8092 8292 7713 3ED0 FF4C 7713 3E81 E598 E598 FC00
 *
 * Intent: Split store plus conditional move. B = AR3 (live-in, as value); A-low then A-high (stl/sth, STH high word src(31:16) per ti-c54x op_sth) stored through live-in AR2; B != 0 moves two words from 16001 (xc 2,bneq covers preset plus first move, exact), else one word from 16080; return.
 */
void frag_397B(int a_in, int **ppar2, int *par3)
{
    int *ar2 = *ppar2;
    int *src;
    int n;
    int i;
    int b = (int)par3;                           /* ldm ar3,b */
    *ar2++ = a_in & 0xFFFF;                      /* stl a,*ar2+ */
    *ar2++ = (a_in >> 16) & 0xFFFF;              /* sth a,*ar2+ */
    if (b != 0) {                                /* xc 2,bneq */
        src = (int *)16001; n = 2;               /* stm; mvdd */
    } else {
        src = (int *)16080; n = 1;               /* skip to 2nd mvdd */
    }
    for (i = 0; i < n; i++)
        *ar2++ = *src++;                         /* mvdd *ar3+,*ar2+ */
    *ppar2 = ar2;
    /* ret */
}
