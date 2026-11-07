/* ROM6 0x44A6 FRAG_44A6 -- 9w.
 * Verified encoding: src/rom6/kernel/44a6_frag_44a6.asm (recombine MATCH).
 * ORIGIN 0x44A6
 * EXPECT: 8A0A 8A09 8A08 1194 F330 000F 81F8 022D FC00
 *
 * Intent: Accumulator-restore plus nibble store. Restores the full 40-bit A from stack (popm ag/ah/al, no C form); B = low nibble of *AR4++ (live-in), stored to cell 0x22D, returns it.
 */
int frag_44A6(int **ppar4)
{
    int b;
    /* popm ag/ah/al: 40-bit A restore (hardware state, no C form) */
    b = **ppar4 & 15;                           /* ld *ar4+,b; and #15 */
    (*ppar4)++;
    *(volatile int *)0x22D = b;              /* stl b,*(0x22d) */
    return b;                                    /* ret */
}
