; ROM6 0x5886 FRAG_5886 -- 90w, symbols.yaml data_word.
; Evidence: Bound 5886-58DF (FC00@58DF); post-ret abut, zero F074/F274 callers; interior 2x calld 58E0 @5895/58A1 (objdump calld) + bd@58BC->58DD interior; HYPOTHESIS fragment.
; ORIGIN 0x5886
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	cmpm   *(0x2510),#176
	bc     0x5890,ntc
	st     #193,*(0x2f02)
	mpy    *(0x261e),#57,a
	mvdm   0x264c,ar0
	calld  0x58e0
	stm    #352,ar4
	ld     #4,a
	add    *(0x261e),a
	mpy    *(0x8),#57,a
	mvdm   0x264d,ar0
	calld  0x58e0
	stm    #353,ar4
	ssbx   st1,ovm
	ld     *(0x1d2),16,a
	add    *(0x2622),16,a
	sth    a,*(0x2622)
	ld     *(0x1d3),16,a
	add    *(0x2621),16,a
	sth    a,*(0x2621)
	rsbx   st1,ovm
	ld     #1,a
	add    *(0x261e),a
	sub    #3,a,b
	bcd    0x58c0,bgt
	stm    #12034,ar2
	bd     0x58dd
	st     #0,*ar2
	stm    #9805,ar2
	ld     *ar2-,a
	delay  *ar2
	stl    a,*ar2
	ld     *(0x2620),a
	bc     0x58d0,aeq
	ld     #0,a
	stl    a,*(0x2620)
	bd     0x58d7
	stl    a,*(0x2f02)
	ld     *(0x2621),b
	bc     0x58d7,bgeq
	st     #176,*(0x2f02)
	stm    #9762,ar2
	mvdk   *ar2,0x2621
	ld     #0,a
	stl    a,*ar2
	stl    a,*(0x261e)
	ret
