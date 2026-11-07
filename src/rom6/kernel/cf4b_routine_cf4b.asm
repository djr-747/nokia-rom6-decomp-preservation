; ROM6 0xCF4B ROUTINE_CF4B -- 99w, symbols.yaml data_word.
; Evidence: Entry EA00 7719 0000 4A07 7707 0740 + F074 0680; caller AA3E; first-RET FC00 @CFAD; calld E5D1/DA18/DD9B/E492 x2 + RPTBD; HYPOTHESIS ea00-family worker.
; ORIGIN 0xCF4B
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,dp
	stm    #0,bk
	pshm   st1
	stm    #1856,st1
	call   0x680
	ld     #3,a
	bitf   *(0xc4c),#4
	bc     0xcf7b,ntc
	stm    #4352,ar2
	rpt    #3
	mvdk   *ar2+,0x235c
	stm    #8,brc
	stm    #4362,ar2
	rptbd  0xcf68
	stm    #9034,ar3
	ld     *ar2+,16,a
	add    *ar2+,1,a
	dst    a,*ar3+
	pshm   st1
	calld  0xe5d1
	ld     *(0xed0),b
	popm   st1
	ld     *(0xc4c),a
	and    #-9,a
	or     b,3,a
	ld     #20,dp
	calld  0xda18
	stl    a,*(0xc4c)
	ld     0x5a,a
	ld     #0,dp
	st     #3798,*(0xecd)
	calld  0xdd9b
	stl    a,*(0xa5a)
	ld     #0,a
	stm    #3856,ar1
	stm    #3170,ar2
	stm    #3986,ar3
	stm    #3966,ar4
	calld  0xe492
	stm    #4376,ar5
	bitf   *(0xa5a),#1
	bcd    0xcfae,ntc
	stm    #3900,ar2
	ld     #1,a
	mvmm   ar2,ar1
	stm    #3180,ar2
	stm    #3996,ar3
	stm    #3976,ar4
	calld  0xe492
	stm    #4376,ar5
	stm    #3170,ar2
	stm    #3180,ar3
	rpt    #9
	mvkd   0xf7e,*ar2+
	rpt    #9
	mvkd   0xf88,*ar3+
	popm   st1
	ret
