; ROM6 0x6FFA AR7MAP_6FFA -- 109w, symbols.yaml data_word.
; Evidence: Entry F074 05B4; bound 6FFA-7066 (FE00 retd@7064 + delays 7317/050C verified); callers F074 6F61/6F72; *(0x17) range-map into ar7; HYPOTHESIS.
; ORIGIN 0x6FFA
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5b4
	ld     *(0x50c),a
	stl    a,*ar3
	add    #1,a
	stlm   a,ar7
	bitf   *(0x263b),#128
	bc     0x703a,ntc
	bitf   *(0x3ec8),#64
	nop
	nop
	bc     0x701b,tc
	cmpm   *(0x17),#125
	sub    #885,a
	xc     2,tc
	stm    #512,ar7
	xc     2,agt
	stm    #1,ar7
	b      0x7064
	cmpm   *(0x17),#125
	sub    #1023,a
	xc     2,tc
	stm    #975,ar7
	cmpm   *(0x17),#886
	xc     2,agt
	stm    #512,ar7
	xc     2,tc
	stm    #0,ar7
	ld     *(0x3ec8),a
	and    #4096,a
	cmpm   *(0x17),#811
	bc     0x7038,aeq
	xc     2,tc
	stm    #0,ar7
	b      0x7064
	bitf   *(0x263b),#96
	bc     0x705c,tc
	bitf   *(0x3ec8),#64
	nop
	nop
	bc     0x7053,ntc
	cmpm   *(0x17),#125
	sub    #1023,a
	xc     2,tc
	stm    #975,ar7
	xc     2,agt
	stm    #0,ar7
	b      0x7064
	cmpm   *(0x17),#125
	bc     0x7064,ntc
	stm    #1,ar7
	b      0x7064
	sub    *(0x50d),a
	sub    #511,a
	bc     0x7064,aleq
	stm    #512,ar7
	retd
	mvmd   ar7,0x50c
