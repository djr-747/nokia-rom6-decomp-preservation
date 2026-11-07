; ROM6 0x66CB FRAG_66CB -- 23w, symbols.yaml data_word.
; Evidence: Bound 66CB-66E1 (23w, exit F073@66E0->676A + operand); callers 4x F073 b @66A5/66AA/66B6/66C3 (branch-joins, not call entries); interior calld 697F@66DC; RECLASSIFIED branch-entere
; ORIGIN 0x66CB
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    *ar5,b,a
	bc     0x676a,ageq
	stl    b,*ar5
	add    *(0x2fd7),b,a
	sub    #51,a,b
	stm    #9751,ar2
	xc     1,bgeq
	ld     b,a
	stl    a,*ar2
	stm    #9749,ar2
	calld  0x697f
	st     #0,*ar2
	b      0x676a
