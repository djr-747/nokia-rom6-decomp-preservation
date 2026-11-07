/* ROM6 0x90B8 KERNEL_9071 -- 1w.
 * Verified encoding: src/rom6/kernel/90b8_kernel_9071.asm (recombine MATCH).
 * ORIGIN 0x90B8
 * EXPECT: FC00
 *
 * Intent: Single-word RET abut (9070-function fall-through abut; 9070 span ends 90B7 (see asm header)). No independent entry;
 * the word executes as the return of the abutting function. Owned here
 * so one .asm owns every word.
 */
void kernel_9071(void)
{
    /* ret: fall-through return abut, no C form of its own */
}
