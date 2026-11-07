; ROM6 0xCF25 ROUTINE_CF25 -- 38w, symbols.yaml data_word.
; Evidence: Entry EA00 7719 0000 4A07 7707 0740 BK=0 prologue + F074 0680; caller AA3C; first-RET FC00 @CF4A; calld E276/E2B4/E2C3/E395; HYPOTHESIS ea00-family leaf.
; ORIGIN 0xCF25
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #0,dp
	stm    #0,bk
	pshm   st1
	stm    #1856,st1
	call   0x680
	stm    #3394,ar1
	stm    #-855,ar3
	calld  0xe276
	stm    #4362,ar4
	stl    a,*(0xed0)
	stm    #-375,ar2
	calld  0xe2b4
	stm    #4364,ar3
	calld  0xe2c3
	stm    #3889,ar1
	st     #3986,0x63
	st     #3966,0x62
	calld  0xe395
	st     #3889,0x11
	popm   st1
	ret
