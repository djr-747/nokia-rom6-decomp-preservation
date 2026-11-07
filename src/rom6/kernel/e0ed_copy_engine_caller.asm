; ROM6 0xE0ED COPY_ENGINE_CALLER -- 87w, symbols.yaml data_word.
; Evidence: Entry 4812 0864 8812 771A 0013 4A12; caller F274 @E1CB; internal calld E532 @E0F5; first-RET @E143 (87w); HYPOTHESIS.
; ORIGIN 0xE0ED
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar2,a
	sub    0x64,a
	stlm   a,ar2
	stm    #19,brc
	pshm   ar2
	pshm   ar3
	pshm   ar4
	calld  0xe532
	stm    #4392,ar4
	stm    #4392,ar2
	stm    #4432,ar3
	ld     #-2,asm
	ld     *ar2+,16,a
	rpt    #38
	st     a,*ar3+ || ld     *ar2+,a
	st     a,*ar3 || ld     *ar2-,a
	ld     #1024,16,a
	neg    a
	rpt    #38
	squra  *ar2-,a
	squra  *ar2,a
	bcd    0xe111,aleq
	ld     #0,asm
	ld     #0,a
	mvmm   ar3,ar2
	ld     #-2,a
	mar    *+ar2(0xffd9)
	stl    a,0x6b
	mvmm   ar2,ar1
	stm    #4352,ar6
	ld     0x65,a
	sub    0x64,a
	stlm   a,ar7
	stm    #-39,ar0
	popm   ar4
	popm   ar3
	popm   ar5
	st     #1,0x66
	mar    *ar5-
	mar    *+ar3(0x27)
	squr   *ar2+,a
	rpt    #36
	squra  *ar2+,a
	calld  0xe54b
	squra  *ar2+,a
	squra  *ar2+,a
	mvmm   ar1,ar2
	sth    a,0x6c
	sub    0x6c,16,a
	stl    a,-1,0x6d
	mpy    *ar2+,*ar4+,a
	rpt    #37
	mac    *ar2+,*ar4+,a
	mac    *ar2,*ar4+0%,a
	sth    a,0x6e
	sub    0x6e,16,a
	stl    a,-1,0x6f
	ld     0x6e,t
	mpy    0x6c,b
	mpy    0x6d,a
	maca   0x66,b
	ld     0x6f,t
	mpy    0x6c,a
	maca   0x66,b
	ldm    ar7,a
	ld     b,15,b
	ld     b,1,b
	sth    b,*ar6+
	ld     0x6b,b
	xc     1,aeq
	ret
