; ROM6 0xC85D STATE_DISPATCH_WORKER -- 191w, symbols.yaml program_word.
; Evidence: BACC jump-table dispatch, pa1/pa2 transactions, pa54 poll, two CALL 0x4007, CALLD chain, RET at 0xC91B. Entry corrected from 0xC86C.
; ORIGIN 0xC85D
	.sect ".text"
	.mmregs
	.global _start
_start:
	stl    b,*(0x20f5)
	stl    b,*(0x20f6)
	stl    b,*(0x20f9)
	st     #0,*(0x20fa)
	st     #-1,*(0x2203)
	portr  0,*(0x8)
	or     #28,a
	nop
	portw  *(0x8),0
	rpt    #20
	nop
	ld     #8,b
	call   0xb461
	ret
	call   0x5ea
	stm    #1308,ar2
	andm   #-8989,*ar2
	orm    #4,*ar2
	andm   #-65,*ar2
	ld     #768,b
	nop
	portw  *(0xb),1
	rpt    #22
	nop
	portr  2,*(0xb)
	and    #-769,b
	nop
	portw  *(0xb),2
	ld     *ar6,a
	andm   #-257,*ar6
	and    #1536,a
	sth    a,*(0x20f9)
	sth    a,*(0x20f5)
	sth    a,*ar7
	sfta   a,-8
	add    #-14175,a
	bacc   a
	b      0xc8a9
	b      0xc8b6
	b      0xc8b8
	b      0xc8ba
	pshm   ar4
	call   0xb6e6
	call   0xc717
	call   0x9fa8
	orm    #7328,*(0x577)
	popm   ar4
	b      0xc8d4
	b      0xc8d4
	b      0xc8d4
	call   0xc717
	andm   #-7329,*(0x577)
	st     #0,*(0x2b08)
	cmpm   *(0x573),#-23991
	bc     0xc8d4,ntc
	ld     #8,b
	call   0xb461
	ld     #1538,a
	ld     #8,b
	call   0x4007
	ld     #2372,a
	ld     #9,b
	call   0x4007
	stm    #8439,ar2
	stm    #8441,ar3
	ld     *ar6,a
	and    #512,a,b
	sth    b,*ar2(0x1)
	sth    b,*ar2(0x0)
	xc     2,beq
	st     #2,*ar3
	portr  54,*(0xb)
	and    #8192,b
	bc     0xc8ef,beq
	nop
	portw  *(0x8),52
	b      0xc7f8
	addm   #1,*ar3
	stl    a,*ar2(0x1)
	st     #-1,*(0x20f5)
	b      0xc7f8
	st     #2048,*(0x2202)
	stl    a,*ar6
	b      0xc8d4
	st     #2076,*(0x2202)
	stl    a,*ar6
	b      0xc8d4
	stm    #3234,ar1
	calld  0xc91c
	stm    #4256,ar6
	calld  0xc965
	stm    #3394,ar2
	call   0xc9e3
	call   0xca69
	stm    #4216,ar2
	ld     #0,a
	calld  0xce05
	rpt    #39
	stl    a,*ar2+
	call   0xceb4
	ret
