; ROM6 0xAF83 LEAF_AF83 -- 5w, symbols.yaml data_word.
; Evidence: Bound AF83-AF87 (exit FC00@AF87); JTAB_AF57_6WAY leaf; HYPOTHESIS.
; ORIGIN 0xAF83
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0xa2b9
	stm    #-8831,ar5
	ret
