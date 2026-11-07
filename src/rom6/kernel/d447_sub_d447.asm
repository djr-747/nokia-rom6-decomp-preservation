; ROM6 0xD447 SUB_D447 -- 82w, symbols.yaml data_word.
; Evidence: Entry E802 18F8 0A60 after retd D444; caller F274 @D885; first-RET retd @D496 (bound D447-D498 incl delay); in-span routine, not external callee (critic correction); HYPOTHESIS.
; ORIGIN 0xD447
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #2,a
	and    *(0xa60),a
	bc     0xd456,aeq
	banz   0xd456,*ar5
	ld     #0,dp
	calld  0xdbc3
	stm    #2836,ar2
	ld     #22,dp
	sfta   b,4
	stl    b,0x5f
	ld     *(0xa60),a
	and    #112,a,b
	bc     0xd499,beq
	and    #64,a
	bc     0xd476,aeq
	stm    #12290,ar6
	banzd  0xd480,*ar5
	mvkd   0xb5e,*ar6
	ld     #-879,a
	add    *(0xa61),a
	stlm   a,ar2
	stm    #2913,ar3
	ld     #16384,1,b
	mpy    *ar2,*ar3+,a
	sub    *ar2,b
	stlm   b,t
	bd     0xd480
	macr   0x60,a
	sth    a,*ar6
	ld     0x61,a
	stl    a,0x60
	stl    a,*(0x3002)
	stm    #3096,ar2
	ld     #-2381,a
	rpt    #3
	stl    a,*ar2+
	ld     #128,a
	and    *(0xa60),a
	bcd    0xd48d,aeq
	stm    #12290,ar6
	mpy    0x62,#30057,b
	bd     0xd48f
	sth    b,0x62
	sth    b,*ar6
	mvkd   0xb61,0x62
	ld     *ar6,a
	stl    a,0x5d
	stm    #3119,ar2
	rpt    #3
	mvkd   0xc30,*ar2+
	retd
	stl    a,*ar2
	stl    a,0x5e
