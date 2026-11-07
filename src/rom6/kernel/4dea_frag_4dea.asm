; ROM6 0x4DEA FRAG_4DEA -- 6w, symbols.yaml data_word.
; Evidence: Bound 4DEA-4DEF (6w, exit BD@4DEC->4E00 + delays 4DEE/4DEF); chain-link 3/5; HYPOTHESIS.
; ORIGIN 0x4DEA
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #22,bk
	bd     0x4e00
	mar    *+ar3(0xe)%
