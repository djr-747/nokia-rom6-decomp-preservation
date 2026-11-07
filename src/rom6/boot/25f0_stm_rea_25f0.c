/* ROM6 0x25F0 25F0_STM_REA_25F0 -- 2w.
 * Verified encoding: src/rom6/boot/25f0_stm_rea_25f0.asm (recombine MATCH).
 * ORIGIN 0x25F0
 * EXPECT: 771C 0000
 *
 * Intent: STM #0,REA (MMR write, no C form; 2-word form per oracle STM row (0x7700/0xFF00, 2 words); operand word 0x25F1 is the 0x0000 immediate, not a dumped zero). STATE prologue template slot: 25DF prologue abuts before, 25F2 body abuts after; entry by fallthrough.
 */
void stm_rea_25F0(void)
{
    /* stm #0,rea (repeat-safe ISR entry convention per ivt.md) */
}
