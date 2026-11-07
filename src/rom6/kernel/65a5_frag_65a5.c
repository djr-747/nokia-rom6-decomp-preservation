/* ROM6 0x65A5 FRAG_65A5 -- 5w.
 * Verified encoding: src/rom6/kernel/65a5_frag_65a5.asm (recombine MATCH).
 * ORIGIN 0x65A5
 * EXPECT: 7712 0564 FF45 6B82 0008
 *
 * Intent: Conditional cell add with fall-through. AR2 = 1380; A-live-in == 0 runs cell 1380 += 8 (xc 2,aeq plus addm). NOTE: xc 2 names two conditional slots but only one is in-span; the second executes the next head word at runtime (boundary spill, flagged for decomp review). Falls into the next head. Bound 65A5-65A9.
 */
void frag_65A5(int a_live)
{
    /* stm #1380,ar2 */
    if (a_live == 0)                             /* xc 2,aeq */
        *(volatile int *)1380 += 8;          /* addm #8,*ar2 */
    /* (xc 2nd slot = next head word, unmodeled, flagged) */
    /* falls through (no exit in span) */
}
