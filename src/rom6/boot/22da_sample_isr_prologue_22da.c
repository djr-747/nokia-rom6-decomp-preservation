/* ROM6 0x22DA SAMPLE_ISR_PROLOGUE_22DA -- 23w.
 * Verified encoding: src/rom6/boot/22da_sample_isr_prologue_22da.asm (recombine MATCH).
 * ORIGIN 0x22DA
 * EXPECT: F074 05DA 4A07 4A08 4A09 4A0A 4A0B 4A0C 4A0D 4A0E 4A11 4A16 4A10 4A14 4A15 4A12 4A13 4A1A 4A1B 4A1C 4A19 771B 0000
 *
 * Intent: V16/INT0 SAMPLE_ISR entry prologue (runtime IVT V16 FB 0x22DA per
 * roms/rom6/ivt.md; mask vector FFC0 fb 0x22DA in kernel/ffc0_vectors_ffc0.asm).
 * Runs RAM-resident SUB_05DA first (mini-kernel, zeros in-mask, forward extern);
 * full pshm context save (ST1/AL/AH/AG/BL/BH/BG/T/AR1/AR6/AR0/AR4/AR5/AR2/AR3/
 * BRC/RSA/REA/BK -- caller-live, comments only per 2D5E precedent); STM #0,RSA
 * (MMR, no C form; 2-word form per oracle STM row (0x7700/0xFF00, 2 words);
 * operand word 0x22F0 is the 0x0000 immediate, not a dumped zero).
 * Span ends at the instruction boundary; the 22F1 slot abuts.
 */
extern void sub_05DA(void); /* RAM-resident, zero in mask dump; see docs/evidence/extern-triage.md */

void sample_prologue_22DA(void)
{
    sub_05DA();                                            /* call 0x5da (RAM) */
    /* pshm st1/al/ah/ag/bl/bh/bg/t/ar1/ar6/ar0/ar4/ar5/ar2/ar3/brc/rsa/rea/bk */
    /* stm #0,rsa (MMR, no C form; 2-word form, operand 0x22F0) */
}
