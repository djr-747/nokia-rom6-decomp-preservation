; ROM6 0x382E FRAG_382E -- 17w, symbols.yaml data_word.
; Evidence: Bound 382E-383E (17w; exit B F073@383D->37DF + operand 383E, byte-verified; exit scan clean); entry bc F84D@3823->382E byte-verified (chained from FRAG_381B interior); vestibule ar
; ORIGIN 0x382E
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldu    *ar2,a
	and    #255,a
	sub    #0,a,b
	bc     0x383f,beq
	sub    #1,a,b
	bc     0x3844,beq
	sub    #2,a,b
	bc     0x3849,beq
	b      0x37df
