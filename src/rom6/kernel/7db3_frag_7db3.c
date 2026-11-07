/* ROM6 0x7DB3 FRAG_7DB3 -- 2w B-preset abut, one EXPECT.
 * Verified encoding: src/rom6/kernel/7db3_frag_7db3.asm (recombine MATCH).
 * ORIGIN 0x7DB3
 * EXPECT: F120 1000
 *
 * Intent: B = 4096 (ld #4096,b), then falls into FRAG_7DB5 head (abut
 * 7DB3+2 = 7DB5, modeled as tail call per 66C5; 7DB5 is asm-only, so the
 * entry is a forward extern carrying live B). Entered via B @7DAE from
 * SUB_7D74 (per .asm header). Bound 7DB3-7DB4, no own exit.
 */
extern void frag_7DB5(long b_live);

void frag_7DB3(void)
{
    frag_7DB5(4096L);                     /* ld #4096,b; to 7DB5 */
}
