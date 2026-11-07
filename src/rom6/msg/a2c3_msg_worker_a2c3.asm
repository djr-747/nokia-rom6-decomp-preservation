; ROM6 0xA2C3 MSG_WORKER_A2C3 -- 158w, symbols.yaml data_word.
; Evidence: F074 0654 class; RET FC00 @0xA360; callers F074 @0xA269/0xA2AC (0xA269 verified). Bound A2C3-A360 (wave-5: exit + post-RET byte-verified; 18 F074 callers counted; joins A306/A311/A
; ORIGIN 0xA2C3
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x654
	ld     *(0x2628),b
	and    #1,b,a
	bc     0xa2e1,aeq
	bitf   *(0x22c),#1
	bc     0xa2e1,ntc
	and    #-16384,b
	bc     0xa2e1,bneq
	ssbx   st1,intm
	portr  3,*(0xb)
	and    #-2,b
	nop
	portw  *(0xb),3
	rpt    #22
	nop
	rsbx   st1,intm
	portr  16,*(0x8)
	stl    a,*(0x265a)
	orm    #512,*(0x2639)
	stm    #1347,ar2
	st     #0,*ar2-
	cmpm   *(0x250f),#34
	bc     0xa319,ntc
	bitf   *(0x2628),#1
	bc     0xa2fd,ntc
	st     #0,*(0x37dd)
	st     #0,*(0x37db)
	cmpm   *(0x34bf),#0
	bc     0xa308,ntc
	ld     #-20465,16,a
	ld     #-20444,16,b
	b      0xa31d
	cmpm   *(0x34bf),#4
	bc     0xa313,ntc
	ld     #-20452,16,a
	ld     #-20429,16,b
	b      0xa31d
	ld     #-20459,16,a
	ld     #-20437,16,b
	b      0xa31d
	ld     #-20480,16,a
	ld     #-20473,16,b
	stm    #1350,ar3
	sth    a,*ar3+
	sth    b,*ar3
	call   0x3ee1
	cmpm   *(0x250f),#34
	sub    #4178,a,b
	xc     2,tc
	sub    #4418,a,b
	ldu    *(0x547),a
	stlm   a,ar3
	st     #0,*ar2
	ldu    *ar3,a
	bc     0xa337,bleq
	mar    *ar3+
	st     #1,*ar2
	ldu    *ar3,a
	nop
	portw  *(0x8),15
	rpt    #15
	nop
	bitf   *ar2,#1
	cc     0x3986,ntc
	call   0xac4c
	ld     *(0x2628),b
	and    #1,b,a
	rc     aeq
	stm    #9785,ar3
	orm    #258,*ar3
	andm   #-9,*ar3
	ld     #0,a
	stl    a,*(0x262d)
	stl    a,*(0x262f)
	cmpm   *(0x250f),#34
	bc     0xa360,ntc
	stl    a,*(0x34c4)
	stl    a,*(0x34c5)
	stl    a,*(0x34c6)
	stl    a,*(0x34c7)
	ret
