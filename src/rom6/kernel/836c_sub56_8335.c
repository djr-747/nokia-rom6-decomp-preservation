/* ROM6 0x836C SUB56_8335 -- 1w.
 * Verified encoding: src/rom6/kernel/836c_sub56_8335.asm (recombine MATCH).
 * ORIGIN 0x836C
 * EXPECT: FC00
 *
 * Intent: Single-word RET abut (8335-function exit; 8334 span ends 836B (see asm header)). No independent entry;
 * the word executes as the return of the abutting function. Owned here
 * so one .asm owns every word.
 */
void sub56_8335(void)
{
    /* ret: fall-through return abut, no C form of its own */
}
