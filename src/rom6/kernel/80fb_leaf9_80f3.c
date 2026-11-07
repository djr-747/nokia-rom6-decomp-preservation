/* ROM6 0x80FB LEAF9_80F3 -- 1w.
 * Verified encoding: src/rom6/kernel/80fb_leaf9_80f3.asm (recombine MATCH).
 * ORIGIN 0x80FB
 * EXPECT: FC00
 *
 * Intent: Single-word RET abut (prior-span fall-through return abut; 80F3 head-fill falls into it (see asm header)). No independent entry;
 * the word executes as the return of the abutting function. Owned here
 * so one .asm owns every word.
 */
void leaf9_80f3(void)
{
    /* ret: fall-through return abut, no C form of its own */
}
