/* ROM6 0x7EA6 SUB31_7E88 -- 1w.
 * Verified encoding: src/rom6/kernel/7ea6_sub31_7e88.asm (recombine MATCH).
 * ORIGIN 0x7EA6
 * EXPECT: FC00
 *
 * Intent: Single-word RET abut (the 7E88 span fall-through return abut (see asm header split record)). No independent entry;
 * the word executes as the return of the abutting function. Owned here
 * so one .asm owns every word.
 */
void sub31_7e88(void)
{
    /* ret: fall-through return abut, no C form of its own */
}
