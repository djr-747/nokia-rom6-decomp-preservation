/* ROM6 0x7F74 SUB32_7F55 -- 1w.
 * Verified encoding: src/rom6/kernel/7f74_sub32_7f55.asm (recombine MATCH).
 * ORIGIN 0x7F74
 * EXPECT: FC00
 *
 * Intent: Single-word RET abut (prior span fall-through return abut (see asm header split record)). No independent entry;
 * the word executes as the return of the abutting function. Owned here
 * so one .asm owns every word.
 */
void sub32_7f55(void)
{
    /* ret: fall-through return abut, no C form of its own */
}
