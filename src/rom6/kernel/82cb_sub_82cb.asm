; ROM6 0x82CB SUB_82CB -- 9w, symbols.yaml data_word.
; Evidence: Entry F274 82D4 7716 DD33 F274 82FF (calld pair to existing 82D4/82FF); zero callers; first exit ret @82D3; bound 82CB-82D3; HYPOTHESIS.
; ORIGIN 0x82CB
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0x82d4
	stm    #-8909,ar6
	calld  0x82ff
	stm    #-8909,ar6
	ret
