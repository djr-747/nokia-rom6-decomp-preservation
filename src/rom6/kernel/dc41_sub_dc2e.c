/* ROM6 0xDC41 SUB_DC2E -- 2w low-store, one EXPECT.
 * Verified encoding: src/rom6/kernel/dc41_sub_dc2e.asm (recombine MATCH).
 * ORIGIN 0xDC41
 * EXPECT: 80F8 0C4C
 *
 * Intent: *(0xC4C) = A-low (stl a,*(0xc4c)). A rides in from entry.
 * Called via calld @DFE6 (per .asm header). Bound DC41-DC42 (the span
 * is the RETD @DC40 delay pair; falls into DC43 exterior).
 */
void sub_DC2E(long a_live)
{
    *(volatile int *)0xC4C = (int)(a_live & 0xFFFF);     /* stl */
}
