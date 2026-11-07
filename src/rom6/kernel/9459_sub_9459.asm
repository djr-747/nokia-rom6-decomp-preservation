; ROM6 0x9459 SUB_9459 -- 151w, symbols.yaml data_word.
; Evidence: Entry via 9451 F073 b verified; body CALLs 98AD @9460 + 2C88 @947A + 97A2 @948D + cc 9760 @94CE; first exit ret FC00 @94EF; bound 9459-94EF one routine; HYPOTHESIS.
; ORIGIN 0x9459
	.sect ".text"
	.mmregs
	.global _start
_start:
	bitf   *(0x2202),#2048
	bcd    0x9464,ntc
	stm    #8447,ar0
	call   0x98ad
	b      0x94d0
	ld     *(0x21fe),8,a
	bc     0x94a1,aeq
	ld     *(0x21fb),b
	sub    *(0x21fa),b
	bc     0x94d0,bneq
	ld     *(0x21fd),b
	sub    *(0x21fc),b
	bc     0x94d0,bneq
	stm    #8702,ar3
	stl    a,*ar3
	stm    #141,ar4
	calld  0x2c88
	stm    #1,ar5
	ssbx   st1,intm
	stm    #542,ar2
	portr  0,*ar2
	andm   #-17,*ar2
	nop
	portw  *ar2,0
	rpt    #18
	nop
	andm   #-2,*(0x20ff)
	call   0x97a2
	portr  0,*ar2
	orm    #16,*ar2
	nop
	portw  *ar2,0
	rpt    #22
	nop
	orm    #1,*(0x20ff)
	rsbx   st1,intm
	ld     #0,a
	bd     0x94d0
	stl    a,*(0x21fe)
	bitf   *ar0,#2048
	bc     0x94a9,ntc
	call   0x96bd
	b      0x94d0
	ldu    *(0x2203),a
	xor    #65535,a,b
	bcd    0x94d0,beq
	subs   *(0x20fb),a
	bitf   *(0x20ff),#128
	bc     0x94ce,ntc
	sub    #22,a,b
	bcd    0x94ce,bgt
	stm    #96,ar2
	ssbx   st1,intm
	portr  12,*ar2
	pshm   al
	pshm   ah
	pshm   ag
	ld     *(0x3eca),a
	cmpl   a
	and    *ar2,a
	stl    a,*ar2
	popm   ag
	popm   ah
	popm   al
	nop
	portw  *ar2,12
	rsbx   st1,intm
	cc     0x9760,aleq
	ld     #0,a
	bitf   *(0x20ff),#1
	rc     ntc
	addm   #1,*(0x21ff)
	addm   #1,*(0x20fb)
	addm   #1,*(0x20fa)
	ldu    *(0x20fa),b
	sub    #2,b
	rc     blt
	ld     *(0x20fd),b
	rc     beq
	portr  54,*(0xb)
	and    #2048,b
	rc     bneq
	orm    #64,*(0x20ff)
	ret
