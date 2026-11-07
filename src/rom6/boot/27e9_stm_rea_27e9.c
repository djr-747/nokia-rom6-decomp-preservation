/* ROM6 0x27E9 27E9_STM_REA_27E9 -- 2w.
 * Verified encoding: src/rom6/boot/27e9_stm_rea_27e9.asm (recombine MATCH).
 * ORIGIN 0x27E9
 * EXPECT: 771C 0000
 *
 * Intent: STM #0,REA (MMR write, no C form; 2-word form per oracle STM row (0x7700/0xFF00, 2 words); operand word 0x27EA is the 0x0000 immediate, not a dumped zero). FRAME prologue template slot: 27CD prologue abuts before, 27EB head abuts after; entry by fallthrough.
 */
void stm_rea_27E9(void)
{
    /* stm #0,rea (repeat-safe ISR entry convention per ivt.md) */
}
