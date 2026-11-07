; ROM6 0x5B9E FRAG_5B9E -- 59w, symbols.yaml data_word.
; Evidence: Bound 5B9E-5BD8 (59w; exit RET FC00@5BD8 byte-verified, exit scan clean; abuts SUB_5BD9 head — pre-word F074@5BD9 is next routine, not operand); entries B F073@5B5A->5BC6 (exterior
; ORIGIN 0x5B9E
	.sect ".text"
	.mmregs
	.global _start
_start:
	ssbx   st1,ovm
	add    *(0x1d3),16,a
	sth    a,*(0x2621)
	rsbx   st1,ovm
	st     #0,*(0x2622)
	stm    #11036,ar1
	bcd    0x5b68,ageq
	stm    #11093,ar0
	st     #1,*(0x2ef5)
	b      0x5b68
	mvmd   ar0,0x264c
	st     #0,*(0x9c6)
	ld     *(0x2eff),a
	bc     0x5bc6,aeq
	cmpm   *(0x2f02),#192
	bc     0x5bc6,ntc
	st     #1,*(0x9c6)
	st     #0,*(0x2eff)
	ld     #1,a
	add    *(0x264d),a
	and    #3,a
	stl    a,*(0x264d)
	ssbx   st1,cpl
	ld     *(0x2620),t
	mpy    *(0x2f02),a
	rc     aeq
	ld     #0,a
	stl    a,*(0x2f02)
	stl    a,*(0x2620)
	ret
