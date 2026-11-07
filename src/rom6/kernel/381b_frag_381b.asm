; ROM6 0x381B FRAG_381B -- 12w, symbols.yaml data_word.
; Evidence: Bound 381B-3826 (12w; exit B F073@3825->37DF + operand 3826, byte-verified; exit scan clean); entry bc F84D@37FA->381B byte-verified (exterior, FRAG_37D8 interior); vestibule arm 3
; ORIGIN 0x381B
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar2,a
	sftl   a,-8
	sub    #0,a,b
	bc     0x3827,beq
	sub    #1,a,b
	bc     0x382e,beq
	b      0x37df
