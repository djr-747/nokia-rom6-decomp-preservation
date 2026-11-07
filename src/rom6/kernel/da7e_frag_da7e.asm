; ROM6 0xDA7E FRAG_DA7E -- 75w, symbols.yaml data_word.
; Evidence: Bound DA7E-DAC8 (75w; exit retd FE00@DAC6 + delays DAC7-DAC8 included per convention; 2x interior F273 joins DA86->DA8A + DAAD->DAB3; exit scan otherwise clean); post-RET head only
; ORIGIN 0xDA7E
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #7,0x5e
	bitf   0x60,#4
	bc     0xda8a,ntc
	st     #0,0x62
	bd     0xda8a
	st     #23,0x61
	bitf   0x60,#8
	bcd    0xda9d,ntc
	ld     #1,a
	sub    *ar4,a
	st     #0,0x62
	xc     1,aeq
	stl    a,0x61
	ld     #23,b
	sub    0x61,b
	cmpm   *ar4,#2
	bc     0xda9d,ntc
	xc     2,bgt
	addm   #1,0x61
	bitf   0x60,#512
	bcd    0xdaba,ntc
	ld     #23,a
	sub    0x61,a
	ld     #8,b
	and    *(0xb68),b
	xc     2,agt
	addm   #1,0x61
	bc     0xdab1,beq
	orm    #16,0x60
	bd     0xdab3
	addm   #1,0x62
	orm    #64,0x60
	ld     #1,a
	sub    0x62,a
	nop
	nop
	xc     2,alt
	orm    #128,0x60
	ld     #30,b
	sub    0x5f,b
	bc     0xdac9,bgeq
	orm    #2,0x60
	st     #0,0x5f
	st     #28801,0x64
	st     #26968,0x65
	retd
	st     #0,0x5e
