; ROM6 0xAF79 LEAF_AF79 -- 5w, symbols.yaml data_word.
; Evidence: Bound AF79-AF7D (exit FC00@AF7D); JTAB_AF57_6WAY leaf; HYPOTHESIS.
; ORIGIN 0xAF79
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0xa2b9
	stm    #-8857,ar5
	ret
