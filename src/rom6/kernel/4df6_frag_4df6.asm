; ROM6 0x4DF6 FRAG_4DF6 -- 4w, symbols.yaml data_word.
; Evidence: Bound 4DF6-4DF9 (4w, exit BD@4DF6->4E00 + delays, bare BD); chain-link 5/5; HYPOTHESIS.
; ORIGIN 0x4DF6
	.sect ".text"
	.mmregs
	.global _start
_start:
	bd     0x4e00
	stm    #8,bk
