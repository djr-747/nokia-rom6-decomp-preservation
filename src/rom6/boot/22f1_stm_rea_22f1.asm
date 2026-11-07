; ROM6 0x22F1 STM_REA_22F1 -- 2w, symbols.yaml program_word.
; Evidence: STM #0,REA (2-word form per oracle STM row (0x7700/0xFF00, 2 words); operand word is the 0x0000 immediate, not a dumped zero); SAMPLE prologue template slot: 22DA prologue abuts before, 22F3 body abuts after; entry by fallthrough.
; ORIGIN 0x22F1
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #0,rea ; @0x22F1 771c
