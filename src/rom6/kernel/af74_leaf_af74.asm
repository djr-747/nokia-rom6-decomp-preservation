; ROM6 0xAF74 LEAF_AF74 -- 5w, symbols.yaml data_word.
; Evidence: Bound AF74-AF78 (exit FC00@AF78); JTAB_AF57_6WAY leaf, same idiom as AF6A; HYPOTHESIS.
; ORIGIN 0xAF74
	.sect ".text"
	.mmregs
	.global _start
_start:
	calld  0xa2b9
	stm    #-8869,ar5
	ret
