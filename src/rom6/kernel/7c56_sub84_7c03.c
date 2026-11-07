/* ROM6 0x7C56 SUB84_7C03 -- 1w.
 * Verified encoding: src/rom6/kernel/7c56_sub84_7c03.asm (recombine MATCH).
 * ORIGIN 0x7C56
 * EXPECT: FC00
 *
 * Intent: Single-word RET abut (prior span fall-through return abut (see asm header split record)). No independent entry;
 * the word executes as the return of the abutting function. Owned here
 * so one .asm owns every word.
 */
void sub84_7c03(void)
{
    /* ret: fall-through return abut, no C form of its own */
}
