; ROM6 0x9DF4 LEAF_9DF4 -- 59w, symbols.yaml data_word.
; Evidence: Entry F074 06C2 4A07 4A06 F7B6 F7B8 F7B9; callers F074@A779/AA15/AFEE; first-RET @0x9E2E (59w); HYPOTHESIS.
; ORIGIN 0x9DF4
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6c2
	pshm   st1
	pshm   st0
	ssbx   st1,frct
	ssbx   st1,sxm
	ssbx   st1,ovm
	cmpm   *(0x573),#-20649
	bc     0x9e0e,ntc
	calld  0x9d9a
	stm    #12694,ar3
	ld     *(0x85d),a
	and    #2,a
	bc     0x9e2c,aeq
	stm    #12694,ar3
	b      0x9e1c
	call   0x6c2
	calld  0x9d9a
	stm    #12854,ar3
	ld     *(0x85d),a
	and    #1,a
	bc     0x9e2c,aeq
	stm    #12854,ar3
	ld     #1,b
	mvdm   0x57d,ar2
	call   0x9d2d
	mvmd   ar2,0x57d
	ld     *(0x57c),a
	and    #4095,a
	bc     0x9e2c,aleq
	addm   #-1,*(0x57c)
	popm   st0
	popm   st1
	ret
