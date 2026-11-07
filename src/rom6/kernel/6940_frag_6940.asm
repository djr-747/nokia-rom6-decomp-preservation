; ROM6 0x6940 FRAG_6940 -- 13w, symbols.yaml data_word.
; Evidence: Bound 6940-694C (13w; exit B F073@694B->6954 + operand 694C — branch-tailed into FRAG_6954 head; mirrors FRAG_690E head idiom F110 0020 / F84E 694D; exit scan clean); entry bc F84E
; ORIGIN 0x6940
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    #32,a,b
	bc     0x694d,bgt
	sub    #17,a
	stlm   a,t
	nop
	bitt   *+ar1(0x2)
	rc     tc
	b      0x6954
