; ROM6 0x4DF0 FRAG_4DF0 -- 6w, symbols.yaml data_word.
; Evidence: Bound 4DF0-4DF5 (6w, exit BD@4DF2->4E00 + delays 4DF4/4DF5); head 7719 0016; chain-link 4/5; HYPOTHESIS.
; ORIGIN 0x4DF0
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #22,bk
	bd     0x4e00
	stm    #22,ar1
