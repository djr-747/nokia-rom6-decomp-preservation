; ROM6 0x691D FRAG_691D -- 11w, symbols.yaml data_word.
; Evidence: Bound 691D-6927 (11w; exit retd FE00@6925 + delays 6926-6927 included per convention; exit scan clean); entry bc F84E@6910->691D byte-verified (from FRAG_690E [690E-691C] interior,
; ORIGIN 0x691D
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    #33,a
	stlm   a,t
	nop
	bitt   *+ar1(0x4)
	bc     0x6928,tc
	retd
	orm    #256,*ar2
