; ROM6 0x3C00 PORT_SEQ_WRITER -- 201w, symbols.yaml data_word.
; Evidence: Entry F074 0636; bound 3C00-3CC8 (terminal RET raw+full-disasm); callers F074@7B13 + F274@7B35; portw pa5/pa47/pa6/pa3; HYPOTHESIS.
; ORIGIN 0x3C00
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x636
	sfta   a,2
	neg    a
	add    *(0x3ea0),a
	cmpm   *(0x250f),#34
	bc     0x3c3b,ntc
	cmpm   *(0x34bf),#3
	bc     0x3c2d,ntc
	bitf   *(0x3490),#256
	bc     0x3c1c,ntc
	bitf   *(0x3490),#512
	bc     0x3c39,ntc
	b      0x3cc9
	bitf   *(0x3490),#512
	bc     0x3c3b,tc
	cmpm   *(0x262b),#224
	bc     0x3c2d,ntc
	bitf   *(0x34cc),#1
	bc     0x3c39,tc
	b      0x3c3b
	cmpm   *(0x34bf),#1
	bc     0x3c39,tc
	cmpm   *(0x34bf),#4
	bc     0x3c39,tc
	b      0x3c3b
	add    #625,a
	nop
	portw  *(0x8),5
	rpt    #20
	nop
	stlm   a,ar3
	call   0x3be4
	bc     0x3c5d,tc
	call   0x72c
	ld     *(0x34be),a
	sub    *(0x2636),a
	bc     0x3c5b,aeq
	ldm    ar3,a
	add    b,a
	add    #5,a
	nop
	portw  *(0x8),47
	rpt    #19
	nop
	ldm    ar3,a
	bd     0x3c66
	add    #625,b
	ld     #15000,a
	nop
	portw  *(0x8),47
	rpt    #20
	nop
	ldm    ar3,a
	add    b,a
	nop
	portw  *(0x8),6
	rpt    #21
	nop
	ssbx   st1,intm
	portr  3,*(0xb)
	or     #80,b
	nop
	portw  *(0xb),3
	rpt    #11
	nop
	rsbx   st1,intm
	bitf   *(0x51d),#32
	bc     0x3cc9,ntc
	ldm    ar3,b
	stm    #16037,ar3
	sub    *ar3+,b
	add    *ar3,a
	nop
	xc     2,blt
	add    #4999,b
	nop
	portw  *(0xb),7
	rpt    #16
	nop
	sub    #4999,a,b
	nop
	nop
	xc     1,bgeq
	ld     b,a
	nop
	portw  *(0x8),8
	rpt    #17
	nop
	ld     *(0x2613),b
	sub    #975,b,a
	bitf   *(0x51f),#128
	bc     0x3cc8,ntc
	sub    #512,b
	xc     2,ageq
	ld     #-1,b
	stm    #16014,ar3
	xc     2,bgeq
	stm    #16094,ar3
	nop
	portw  *ar3,37
	stm    #16015,ar3
	bc     0x3cbd,blt
	ld     *(0x2636),a
	sub    *(0x3ee6),a
	stm    #16090,ar3
	xc     2,ageq
	stm    #16100,ar3
	nop
	portw  *ar3,38
	ld     *(0x581),a
	xc     2,bgeq
	ld     *(0x582),a
	ld     #12,b
	call   0x4007
	ret
