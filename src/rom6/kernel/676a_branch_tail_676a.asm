; ROM6 0x676A BRANCH_TAIL_676A -- 253w, symbols.yaml data_word.
; Evidence: Entry F074 0598 call; 27 branch-only refs (7xF073/18xF8xx/2xF273: 0x6420/0x6499/0x64A7/0x6508/0x6511 /0x6516/0x651B/0x6524/0x652C/0x65EA/0x65F6/0x6669/0x6688/0x66CD/0x66F6/0x66FC/0
; ORIGIN 0x676A
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x598
	ld     #5120,a
	and    *(0x263a),a
	cmpm   *(0x8),#4096
	bc     0x6777,ntc
	st     #0,*ar5
	ld     #1,a
	and    *(0x2628),a
	bcd    0x678b,aneq
	stm    #1378,ar2
	stm    #1359,ar0
	ld     *ar0,a
	and    #128,a,b
	bc     0x6791,beq
	and    #-129,a
	stl    a,*ar0
	orm    #8,*(0x2627)
	st     #0,*ar5
	bd     0x6799
	mvkd   0x3ec9,*ar2
	ld     *ar2,a
	bc     0x6799,aleq
	sub    #1,a
	stl    a,*ar2
	st     #0,*ar5
	call   0x598
	stm    #1310,ar2
	andm   #-2049,*ar2
	ld     *ar5,a
	sub    #1,a
	bc     0x6867,aleq
	bitf   *(0x58f),#15
	bc     0x6850,tc
	ld     *(0x85d),a
	and    #31,a
	bc     0x6850,aneq
	orm    #2048,*ar2
	ssbx   st1,intm
	portr  3,*(0xb)
	and    #-257,b
	nop
	portw  *(0xb),3
	rpt    #20
	nop
	rsbx   st1,intm
	ld     #259,b
	nop
	portw  *(0xb),48
	bitf   *(0x3ec8),#32
	bc     0x67d7,ntc
	st     #512,*(0x13d0)
	portr  12,*(0x8)
	ld     *(0x3ece),b
	cmpl   b
	and    b,a
	nop
	portw  *(0x8),12
	calld  0x3986
	ld     #4800,a
	ssbx   st1,intm
	bitf   *(0x4c2),#255
	bc     0x6809,tc
	portr  0,*(0x8)
	and    #-13,a
	nop
	portw  *(0x8),0
	rpt    #22
	nop
	portr  0,*(0x8)
	stm    #12254,ar5
	and    #16,a
	bc     0x6809,aneq
	bitf   *(0x866),#3
	bc     0x6809,tc
	bitf   *(0x264e),#64
	bc     0x6809,tc
	portr  14,*(0x8)
	and    #16383,a
	cmpm   *(0x8),#4999
	bc     0x6812,tc
	rsbx   st1,intm
	ld     #3800,a
	call   0x3986
	bd     0x6850
	stm    #12254,ar5
	call   0x598
	bitf   *(0x552),#2048
	bc     0x6809,tc
	ld     *ar5,a
	sub    #1,a
	stl    a,*(0x2fcf)
	pshm   ar5
	calld  0x2282
	stm    #9,ar2
	popm   ar5
	bc     0x6809,ntc
	pshm   ar5
	call   0x642
	popm   ar5
	stm    #9338,ar0
	st     #0,*ar0+
	ld     *ar5,b
	sub    #1,b
	sub    a,b
	bc     0x683c,bneq
	stl    a,*ar0
	orm    #128,*(0x263a)
	bd     0x6841
	st     #0,*ar5
	st     #2,*ar5
	sub    #1,a
	stl    a,*ar0
	call   0x56fc
	andm   #-5,*(0x866)
	stm    #12254,ar5
	ld     #511,a
	nop
	portw  *(0x8),18
	rpt    #15
	nop
	ld     *ar5,a
	sub    #1,a
	bc     0x6867,aleq
	andm   #-1025,*(0x51e)
	st     #0,*(0x56c)
	stm    #9748,ar2
	ld     *ar2,b
	cmpm   *(0xb),#0
	rc     tc
	stl    b,*(0x53c)
	retd
	st     #0,*ar2
