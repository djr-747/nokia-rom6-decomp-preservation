; ROM6 0x3938 FRAG_3938 -- 67w, symbols.yaml data_word.
; Evidence: Bound 3938-397A (67w; exit RET FC00@397A byte-verified, exit scan clean); post-RET head only (FC00@3937, zero exterior refs); interior joins 3x F073@3941/394C/3955->395E + bc F84E@
; ORIGIN 0x3938
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    #125,a,b
	bc     0x394e,bgt
	sftl   a,2
	add    #20160,a
	stm    #1,ar3
	b      0x395e
	sub    #125,a,b
	bc     0x3957,bgt
	sftl   a,2
	add    #20200,a
	stm    #1,ar3
	b      0x395e
	sub    #512,a
	sftl   a,1
	add    #19982,a
	stm    #0,ar3
	b      0x395e
	sub    #512,a
	sftl   a,1
	add    #19502,a
	stm    #0,ar3
	call   0x5a0
	ld     a,-1,b
	and    #63,b
	and    #-128,a
	or     b,a
	sftl   a,2
	or     #3,a
	sftl   a,10
	cmpm   *(0x12),#49
	bc     0x397b,ntc
	nop
	portw  *(0x8),49
	nop
	nop
	portw  *(0x9),50
	mar    *+ar2(0x2)
	ret
