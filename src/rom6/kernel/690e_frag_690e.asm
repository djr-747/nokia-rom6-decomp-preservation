; ROM6 0x690E FRAG_690E -- 15w, symbols.yaml data_word.
; Evidence: Bound 690E-691C (15w; exit retd FE00@691A + delays 6982/0100 691B-691C included per convention; exit scan clean); entry bc F84E@6901->690E byte-verified (from SUB_68CA); interior c
; ORIGIN 0x690E
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    #32,a,b
	bc     0x691d,bgt
	sub    #17,a
	stlm   a,t
	nop
	bitt   *+ar1(0x3)
	bc     0x6928,tc
	retd
	orm    #256,*ar2
