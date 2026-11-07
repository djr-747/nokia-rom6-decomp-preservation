; ROM6 0xA3F0 MEASUREMENT_A3F0 -- 146w, symbols.yaml data_word.
; Evidence: F074 0656 class; RET FC00 @0xA481; caller F074 @0xA271 (verified). Bound A3F0-A481 (wave-5: exit + post-RET byte-verified; joins A42E->A45C, bd A46A->A47D).
; ORIGIN 0xA3F0
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x656
	ld     *(0x262a),a
	rc     aeq
	mvdm   0x2628,ar2
	ld     *(0x2659),b
	andm   #1024,*(0x12)
	pshm   al
	sub    #160,a
	bc     0xa47d,aneq
	bitf   *(0x3ec8),#32
	bc     0xa430,ntc
	ld     *(0x38a),a
	sub    *(0x3e97),a
	sub    *(0x3ef3),a
	neg    a
	call   0x6fb1
	stl    a,*(0x2490)
	ld     *(0x2611),b
	sub    #124,b,a
	bcd    0xa41f,aleq
	ld     #1140,a
	sub    #975,b
	bc     0xa41f,bgeq
	ld     #1180,a
	ld     a,b
	add    *(0x2490),a
	stlm   a,ar2
	add    *(0x22d),b
	nop
	ld     *ar2,a
	stlm   b,ar2
	nop
	nop
	ld     *ar2,b
	sub    b,a
	stl    a,*(0x561)
	b      0xa45c
	ld     #32,b
	add    *(0x38a),b
	sfta   b,-6
	sub    *(0x3e97),b
	neg    b
	stm    #21845,t
	mpyr   *(0xb),b
	mpy    *(0xc),#3,b
	max    b
	stm    #16020,ar2
	bitf   *(0x51f),#128
	bc     0xa452,ntc
	ld     *(0x2611),a
	sub    #124,a
	bc     0xa452,aleq
	sub    #761,a
	bc     0xa452,agt
	stm    #16092,ar2
	ld     *ar2,a
	min    b
	stl    b,*(0x2490)
	ld     *(0x22d),a
	sub    a,b
	sfta   b,6
	stl    b,*(0x561)
	ld     *(0x36d),16,a
	sub    *(0x250d),16,a
	stm    #625,t
	mpya   b
	stm    #0,ar2
	bc     0xa46e,blt
	orm    #8,*(0x2639)
	bd     0xa47d
	mvmd   ar2,0x561
	add    #5000,b
	pshm   ar2
	pshm   bl
	pshm   bh
	pshm   bg
	st     #2,*(0x543)
	call   0x3986
	popm   bg
	popm   bh
	popm   bl
	popm   ar2
	ld     #0,a
	popm   al
	call   0xab82
	ret
