; ROM6 0x692C SUB_692C -- 20w, symbols.yaml data_word.
; Evidence: Bound 692C-693F (exit F073@693E->6954 + operand 693F); caller F074@65AF + B-join 695F->692C; preceded by FC00@692B; HYPOTHESIS.
; ORIGIN 0x692C
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *(0x60),a
	stm    #908,ar1
	sub    *ar1,a,b
	rc     bgt
	sub    #16,a,b
	bc     0x6940,bgt
	sub    #1,a
	stlm   a,t
	nop
	bitt   *+ar1(0x1)
	rc     tc
	b      0x6954
