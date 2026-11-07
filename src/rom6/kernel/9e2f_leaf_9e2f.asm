; ROM6 0x9E2F LEAF_9E2F -- 86w, symbols.yaml data_word.
; Evidence: Entry F074 06C4 4A07 4A06 F7B6 F7B8 F7B9 10F8; caller F074@A981; first-RET @0x9E84 (86w); HYPOTHESIS.
; ORIGIN 0x9E2F
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6c4
	pshm   st1
	pshm   st0
	ssbx   st1,frct
	ssbx   st1,sxm
	ssbx   st1,ovm
	ld     *(0x85d),a
	cmpm   *(0x573),#-20649
	bc     0x9e59,ntc
	and    #4,a
	bcd    0x9e46,aeq
	stm    #12854,ar3
	rpt    #159
	mvdk   *ar3+,0x29c9
	ld     *(0x85d),a
	and    #1,a
	bc     0x9e82,aeq
	ld     #1,b
	mvdm   0x57d,ar2
	calld  0x9d2d
	stm    #12854,ar3
	ld     *(0x85d),a
	and    #2,a
	b      0x9e75
	call   0x6c4
	and    #8,a
	bcd    0x9e64,aeq
	stm    #12694,ar3
	rpt    #159
	mvdk   *ar3+,0x29c9
	ld     *(0x85d),a
	and    #2,a
	bc     0x9e82,aeq
	ld     #1,b
	mvdm   0x57d,ar2
	calld  0x9d2d
	stm    #12694,ar3
	ld     *(0x85d),a
	and    #1,a
	bc     0x9e82,aneq
	mvmd   ar2,0x57d
	ld     *(0x57c),a
	and    #4095,a
	bc     0x9e82,aleq
	addm   #-1,*(0x57c)
	popm   st0
	popm   st1
	ret
