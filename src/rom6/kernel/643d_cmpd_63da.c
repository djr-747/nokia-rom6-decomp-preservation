/* ROM6 0x643D CMPD_63DA -- 1w.
 * Verified encoding: src/rom6/kernel/643d_cmpd_63da.asm (recombine MATCH).
 * ORIGIN 0x643D
 * EXPECT: FC00
 *
 * Intent: Single-word RET abut (the 63DA span fall-through return abut (see asm header split record)). No independent entry;
 * the word executes as the return of the abutting function. Owned here
 * so one .asm owns every word.
 */
void cmpd_63da(void)
{
    /* ret: fall-through return abut, no C form of its own */
}
