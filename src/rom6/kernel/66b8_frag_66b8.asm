; ROM6 0x66B8 FRAG_66B8 -- 13w, symbols.yaml data_word.
; Evidence: Bound 66B8-66C4 (13w; exit B F073@66C3->66CB + operand 66C4, byte-verified; exit scan clean); entry bc F84B@66B3->66B8 byte-verified (cond blt, chained from FRAG_66AC interior); ve
; ORIGIN 0x66B8
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     *ar1,b
	sub    *ar0,b
	abs    b
	sub    #20,b
	sub    *ar6,b
	bc     0x66c5,blt
	add    #6,a,b
	add    *ar6,b
	b      0x66cb
