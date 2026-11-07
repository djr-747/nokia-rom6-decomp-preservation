; ROM6 0xAF92 HELPER_AF92 -- 25w, symbols.yaml data_word.
; Evidence: Entry 10F8 0914 (called entry); bound AF92-AFAA (exit FC00@AFAA); 3x F074 callers @AF59/B11E/B16C (survey-verified); cond bc/bd only; out-calls into B11C/B16C runs; HYPOTHESIS.
; ORIGIN 0xAF92
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x914),a
	sub    #13,a,b
	nop
	nop
	xc     1,blt
	ld     a,b
	stlm   b,ar2
	sub    #12,b
	andm   #3,*(0x12)
	bc     0xafaa,bneq
	sub    *(0x2652),a,b
	stm    #4,ar2
	xc     2,beq
	stm    #5,ar2
	ret
