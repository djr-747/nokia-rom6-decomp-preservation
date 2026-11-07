/* ROM6 0xACF3 FRAG_ACF3 -- 1w A-preset abut, one EXPECT.
 * Verified encoding: src/rom6/kernel/acf3_frag_acf3.asm (recombine MATCH).
 * ORIGIN 0xACF3
 * EXPECT: E850
 *
 * Intent: A = 80 (ld #80,a, single word), then falls into
 * ROUTINE_ACF4 head (abut, modeled as tail call per 66C5; C:
 * routine_ACF4 with A = 80 and AR2 threaded through from entry).
 * Entered via B @ACE2 (per .asm header). Bound ACF3-ACF3, no own exit.
 */
extern void routine_ACF4(int a_live, int **ppar2);

void frag_ACF3(int **ppar2)
{
    routine_ACF4(80, ppar2);                  /* ld #80,a; to ACF4 */
}
