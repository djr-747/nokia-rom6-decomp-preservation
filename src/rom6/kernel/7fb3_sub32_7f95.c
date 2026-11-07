/* ROM6 0x7FB3 FRAG_7FB3 -- 2w.
 * Verified encoding: src/rom6/kernel/7fb3_sub32_7f95.asm (recombine MATCH).
 * ORIGIN 0x7FB3
 * EXPECT: F073 7F54
 *
 * Intent: SUB32_7F95 branch tail (2w). Tail-enters C FRAG_7F54 (b, C-bound).
 */
extern void frag_7F54(void);

void frag_7FB3(void)
{
    frag_7F54();                                   /* b 0x7f54 tail */
}
