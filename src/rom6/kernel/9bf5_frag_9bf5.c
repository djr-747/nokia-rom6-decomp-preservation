/* ROM6 0x9BF5 FRAG_9BF5 -- 3w.
 * Verified encoding: src/rom6/kernel/9bf5_frag_9bf5.asm (recombine MATCH).
 * ORIGIN 0x9BF5
 * EXPECT: 6D97 F073 9C15
 *
 * Intent: FRAG_9BF5 step tail (3w). AR7-entry steps once (mar *ar7+, plain post-increment, linear); tail-enters dark 0x9C15 (b, forward extern; stepped AR7 live into it, noted).
 */
extern void frag_9C15(void);

void frag_9BF5(int *par7)
{
    par7++;                                        /* mar *ar7+ */
    (void)par7;                                   /* live into frag_9C15 */
    frag_9C15();                                   /* b 0x9c15 tail */
}
