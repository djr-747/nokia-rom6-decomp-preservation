; ROM6 0x27E9 STM_REA_27E9 -- 2w, symbols.yaml program_word.
; Evidence: STM #0,REA (2-word form per oracle STM row (0x7700/0xFF00, 2 words); operand word is the 0x0000 immediate, not a dumped zero); FRAME prologue template slot: 27CD prologue abuts before, 27EB head abuts after; entry by fallthrough.
; ORIGIN 0x27E9
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #0,rea ; @0x27E9 771c
