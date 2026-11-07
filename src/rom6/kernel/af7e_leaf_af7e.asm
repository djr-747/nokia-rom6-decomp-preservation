; ROM6 0xAF7E LEAF_AF7E -- 5w, symbols.yaml data_word.
; Evidence: Bound AF7E-AF82 (exit FC00@AF82); JTAB_AF57_6WAY leaf; HYPOTHESIS.
; ORIGIN 0xAF7E
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0xa2b9
	stm    #-8845,ar5
	ret
