; ROM6 0x694D FRAG_694D -- 7w, symbols.yaml data_word.
; Evidence: Bound 694D-6953 (7w; NO own unconditional exit: ends cond-return rc FC30@6953 + falls into 6954's span — tail-frag abut, not a routine); entry bc F84x@6942->694D byte-verified (con
; ORIGIN 0x694D
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    #33,a
	stlm   a,t
	nop
	bitt   *+ar1(0x3)
	rc     tc
