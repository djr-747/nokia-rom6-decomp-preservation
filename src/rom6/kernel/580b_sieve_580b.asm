; ROM6 0x580B SIEVE_580B -- 24w, symbols.yaml data_word.
; Evidence: Entry F074 059C 7713 000B; bound 580B-5822 (ret; rsbx/ssbx tc pair 5822/5824 frag follows, bc- entered); callers F074@3699/5356/535C/73E6; cmpm/bc lane sieve; HYPOTHESIS.
; ORIGIN 0x580B
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	stm    #11,ar3
	cmpm   *ar3,#26
	bc     0x5821,tc
	cmpm   *ar3,#81
	bc     0x5821,tc
	and    #240,b
	cmpm   *ar3,#16
	bc     0x5823,tc
	cmpm   *ar3,#80
	bc     0x5823,tc
	rsbx   st0,tc
	ret
