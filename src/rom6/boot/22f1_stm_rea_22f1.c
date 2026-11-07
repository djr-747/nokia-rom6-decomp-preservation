/* ROM6 0x22F1 22F1_STM_REA_22F1 -- 2w.
 * Verified encoding: src/rom6/boot/22f1_stm_rea_22f1.asm (recombine MATCH).
 * ORIGIN 0x22F1
 * EXPECT: 771C 0000
 *
 * Intent: STM #0,REA (MMR write, no C form; 2-word form per oracle STM row (0x7700/0xFF00, 2 words); operand word 0x22F2 is the 0x0000 immediate, not a dumped zero). SAMPLE prologue template slot: 22DA prologue abuts before, 22F3 body abuts after; entry by fallthrough.
 */
void stm_rea_22F1(void)
{
    /* stm #0,rea (repeat-safe ISR entry convention per ivt.md) */
}
