; ROM6 0x4883 FRAG_4883 -- 193w, symbols.yaml data_word.
; Evidence: Entry F074 059E (post-legacy head, abuts SUM_RPTB_4858 ends 4882); bound 4883-4943 (exit FE00@4941 + delays 4942/4943); zero F074/F274 callers whole-ROM (gap-internal references on
; ORIGIN 0x4883
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	bitf   *(0x3ec8),#32
	bc     0x48cf,ntc
	stm    #9786,ar2
	orm    #96,*ar2
	portr  0,*(0xb)
	and    #-1,b
	nop
	portw  *(0xb),0
	rpt    #22
	nop
	portr  3,*(0xb)
	or     #256,b
	nop
	portw  *(0xb),3
	rpt    #20
	nop
	stm    #16124,ar5
	nop
	portw  *ar5+,49
	nop
	nop
	portw  *ar5,50
	st     #512,*(0x13d0)
	ssbx   st1,intm
	portr  2,*(0xb)
	and    #-4097,b
	nop
	portw  *(0xb),2
	rsbx   st1,intm
	ld     #256,16,b
	or     #4350,b
	nop
	portw  *(0xc),48
	nop
	nop
	portw  *(0xb),4
	rpt    #14
	nop
	stl    b,*(0x58e)
	st     #1,*(0x22d)
	ld     *(0x55f),a
	pshm   al
	st     #1,*(0x55f)
	ld     #0,a
	stm    #500,ar4
	stl    a,*ar4+
	stl    a,*ar4-
	calld  0x3986
	ld     #4400,a
	stm    #0,ar1
	ld     #1,a
	bitf   *(0x51f),#96
	ld     #512,b
	xc     1,ntc
	ld     #1,b
	bitf   *(0x3ec8),#64
	nop
	nop
	xc     1,tc
	ld     #0,b
	calld  0x3d79
	stm    #12032,ar3
	stm    #4,brc
	rptb   0x48fa
	calld  0x3986
	ld     #4400,a
	call   0x3e53
	popm   al
	nop
	nop
	stl    a,*(0x55f)
	st     #0,*(0x2490)
	stm    #21,ar2
	stm    #1000,ar1
	ld     #2,a
	bitf   *(0x51f),#96
	ld     #512,b
	xc     1,ntc
	ld     #1,b
	bitf   *(0x3ec8),#64
	nop
	nop
	xc     1,tc
	ld     #0,b
	calld  0x3d79
	stm    #12062,ar3
	bitf   *(0x3ec8),#32
	bc     0x4925,ntc
	stm    #4728,ar2
	andm   #-2,*ar2
	calld  0x3986
	ld     #4400,a
	ld     #0,a
	ld     #0,b
	stm    #63,brc
	rptbd  0x4932
	stm    #12232,ar2
	add    *ar2+,a
	add    *ar2+,b
	stm    #502,ar2
	sfta   a,-2
	stl    a,*ar2+
	sfta   b,-2
	stl    b,*ar2
	stm    #500,ar2
	add    #8,a
	sfta   a,-4
	add    #8,b
	sfta   b,-4
	retd
	stl    a,*ar2+
	stl    b,*ar2
