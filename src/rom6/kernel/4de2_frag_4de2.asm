; ROM6 0x4DE2 FRAG_4DE2 -- 8w, symbols.yaml data_word.
; Evidence: Bound 4DE2-4DE9 (8w, exit BD@4DE6->4E00 + delays); gap-internal; chain-link 2/5; HYPOTHESIS.
; ORIGIN 0x4DE2
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #8,bk
	stm    #4,ar1
	bd     0x4e00
	mar    *+ar3(0x4)%
