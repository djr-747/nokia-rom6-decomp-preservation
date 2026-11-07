/* ROM6 0x399E FRAG_399E -- 6w.
 * Verified encoding: src/rom6/kernel/399e_frag_399e.asm (recombine MATCH).
 * ORIGIN 0x399E
 * EXPECT: 3997 F6BB 68F8 263A FFFD FC00
 *
 * Intent: Interrupt-unlock plus mask clear. Reserved leading word 0x3997, clears INTM (rsbx st1,intm, hardware state), clears low 2 bits of cell 0x263A (andm -3), returns.
 */
void frag_399E(void)
{
    /* +0 reserved word 0x3997 */
    /* rsbx st1,intm: INTM clear (hardware state, no C form) */
    *(volatile int *)0x263A &= -3;           /* andm #-3,*(0x263a) */
    /* ret */
}
