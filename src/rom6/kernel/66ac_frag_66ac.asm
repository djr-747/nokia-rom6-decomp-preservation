; ROM6 0x66AC FRAG_66AC -- 12w, symbols.yaml data_word.
; Evidence: Bound 66AC-66B7 (12w; exit B F073@66B6->66CB + operand 66B7, byte-verified; exit scan clean); entry bc F830@669D->66AC byte-verified (cond tc, chained from FRAG_6693 interior); ves
; ORIGIN 0x66AC
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar1,a
	stm    #12252,ar0
	ld     *ar0,b
	min    a
	sub    #14,a,b
	bc     0x66b8,blt
	ld     #0,b
	b      0x66cb
