; ROM6 0x40BC MEMSCAN_SETUP -- 138w, symbols.yaml data_word.
; Evidence: Entry F074 0602 61F8...; first-RET FC00 @0x4145 (bound 40BC-4145); 2 calld callers A36B A3B0; no port ops; internal call 40DA->4146; HYPOTHESIS memscan setup.
; ORIGIN 0x40BC
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x602
	bc     0x40c9,aeq
	stm    #12118,ar0
	st     #-1,*(0x3044)
	bd     0x40da
	st     #20,*ar0
	st     #256,*(0x2f51)
	st     #-1,*(0x2f49)
	ld     #0,a
	stl    a,*(0x233)
	stl    a,*(0x2f48)
	st     #18,*(0x2f56)
	st     #-1,*(0x3044)
	call   0x4146
	stm    #563,ar2
	sub    *(0x3eb0),a,b
	bcd    0x40ed,bleq
	stm    #12104,ar3
	sub    *ar2,a,b
	addm   #1,*(0x55c)
	xc     2,bgt
	stl    a,*ar2+
	mvdd   *ar3,*ar2
	sub    *(0x3eb1),a
	stm    #12356,ar1
	cmpm   *ar1,#0
	bc     0x40fb,tc
	xc     2,agt
	st     #20,*ar1
	xc     2,aleq
	addm   #-1,*ar1
	stm    #12118,ar1
	addm   #1,*ar1
	ld     *ar1,a
	sub    *(0x56f),a
	bcd    0x40da,alt
	addm   #1,*ar3
	stm    #562,ar0
	ld     *ar0+,a
	sub    *ar0,a
	bcd    0x4115,ageq
	ld     *ar0+,a
	ld     *ar0+,b
	stl    b,*ar0
	stl    a,*(0x232)
	dld    *(0x912),a
	dst    a,*(0x236)
	ld     *(0x3044),a
	nop
	nop
	xc     2,aeq
	stl    a,*(0x2634)
	bc     0x4126,alt
	ld     #2,a
	add    *(0x2634),a
	bc     0x4126,agt
	st     #-2,*(0x2634)
	ld     *(0x2634),a
	rcd    alt
	stm    #565,ar2
	ld     *(0x232),a
	rcd    aleq
	ld     *(0x250f),b
	ld     *ar2+,a
	sfta   a,5
	and    #240,b
	sub    #32,b
	stl    a,*(0x2615)
	bc     0x413d,bneq
	dld    *ar2,a
	dst    a,*(0x2456)
	ld     *(0x55c),a
	sub    #500,a
	rc     ageq
	orm    #128,*(0x2627)
	ret
