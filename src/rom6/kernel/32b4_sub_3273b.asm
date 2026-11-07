; ROM6 0x32B4 SUB_3273B -- 58w, symbols.yaml program_word.
; Evidence: Bound 32B4-32ED (62w); entry TRACE (same histogram: 32B4 x2, continuation past 32B2 dispatch exit); ret FC00@32ED; HYPOTHESIS.
; ORIGIN 0x32B4
	.sect ".text"
	.global _start
_start:
	stm    #9787,ar4
	ldm    ar1,b
	and    #240,b,a
	andm   #-241,*ar4
	or     *ar4,a
	stl    a,*ar4
	bitf   *(0x3ec8),#16
	bc     0x32d3,ntc
	and    #240,a
	stlm   a,ar1
	sub    #80,a
	bc     0x32ce,aeq
	ldm    ar1,a
	sub    #48,a
	bc     0x32d3,aneq
	ld     #128,a
	andm   #-241,*ar4
	or     *ar4,a
	stl    a,*ar4
	and    #15,b
	ld     *(0x51f),a
	and    #-16,a
	or     b,a
	stl    a,*(0x51f)
	bitf   *ar4,#96
	ld     #13439,a
	ld     *(0x537),b
	and    #8,b
	bc     0x32eb,bneq
	ld     #3561,a
	xc     2,tc
	ld     #3909,a
	call   0x423b
	ret
