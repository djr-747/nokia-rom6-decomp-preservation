; ROM6 0x25F0 STM_REA_25F0 -- 2w, symbols.yaml program_word.
; Evidence: STM #0,REA (2-word form per oracle STM row (0x7700/0xFF00, 2 words); operand word is the 0x0000 immediate, not a dumped zero); STATE prologue template slot: 25DF prologue abuts before, 25F2 body abuts after; entry by fallthrough.
; ORIGIN 0x25F0
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #0,rea ; @0x25F0 771c
