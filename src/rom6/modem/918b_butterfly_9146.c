/* ROM6 0x918B BUTTERFLY_9146 -- 1w.
 * Verified encoding: src/rom6/modem/918b_butterfly_9146.asm (recombine MATCH).
 * ORIGIN 0x918B
 * EXPECT: FC00
 *
 * Intent: Single-word RET abut (the 9146 span fall-through return abut (see asm header split record)). No independent entry;
 * the word executes as the return of the abutting function. Owned here
 * so one .asm owns every word.
 */
void butterfly_9146(void)
{
    /* ret: fall-through return abut, no C form of its own */
}
