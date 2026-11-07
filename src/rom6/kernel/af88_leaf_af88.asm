; ROM6 0xAF88 LEAF_AF88 -- 10w, symbols.yaml data_word.
; Evidence: Bound AF88-AF91 (exit FC00@AF91); JTAB_AF57_6WAY leaf; HYPOTHESIS.
; ORIGIN 0xAF88
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0xa2c3
	call   0xa361
	rc     aneq
	calld  0xa2b9
	stm    #-8820,ar5
	ret
