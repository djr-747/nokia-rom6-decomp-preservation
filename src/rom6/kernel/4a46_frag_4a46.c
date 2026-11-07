/* ROM6 0x4A46 FRAG_4A46 -- 5w.
 * Verified encoding: src/rom6/kernel/4a46_frag_4a46.asm (recombine MATCH).
 * ORIGIN 0x4A46
 * EXPECT: 76EA FFFF 0000 F073 4ADF
 *
 * Intent: B-lane chain tail. Clears the cell below live-in AR2 (st #0,*+ar2(0xffff)), tail-enters FRAG_4ADF (b 0x4adf, C: frag_4ADF). Same symbols.yaml target caveat as FRAG_4A12 (ROM verifies 4ADF). Bound 4A46-4A4A.
 */
extern void frag_4ADF(void);

void frag_4A46(int *par2)
{
    par2[-1] = 0;                                /* st #0,*+ar2(0xffff) */
    frag_4ADF();                                 /* b 0x4adf tail */
}
