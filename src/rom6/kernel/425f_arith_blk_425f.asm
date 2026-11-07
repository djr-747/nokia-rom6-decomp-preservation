; ROM6 0x425F ARITH_BLK_425F -- 89w, symbols.yaml data_word.
; Evidence: Entry F074 0606; first-RET FC00 @0x42B7; 3 calld callers 51F4 5806 7227; internal calld 4255->2C88; no port ops; HYPOTHESIS arith block.
; ORIGIN 0x425F
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x606
	pshm   ar7
	mvmm   ar2,ar7
	mar    *+ar7(0x5)
	ld     *ar2+,16,a
	or     *ar2-,a
	add    #1,a
	ld     #41,16,b
	or     #28672,b
	sub    a,b
	bc     0x4271,bneq
	ld     #0,a
	sth    a,*ar2+
	stl    a,*ar2+
	ld     #1,a
	add    *ar2,a
	sub    #26,a,b
	stl    b,*ar2+
	nop
	xc     2,bneq
	stl    a,*ar2(0xffff)
	ld     #1,a
	add    *ar2,a
	sub    #51,a,b
	stl    b,*ar2+
	nop
	xc     2,bneq
	stl    a,*ar2(0xffff)
	bc     0x4290,bneq
	ld     #1,a
	add    *ar2,a
	sub    #-12288,a,b
	stl    b,*ar2+
	nop
	xc     2,bneq
	stl    a,*ar2(0xffff)
	ld     #1,a
	add    *ar7,a
	sub    #102,a,b
	stl    b,*ar7+
	nop
	xc     2,bneq
	stl    a,*ar7(0xffff)
	ld     #1,a
	add    *ar7,a
	sub    #104,a,b
	stl    b,*ar7+
	nop
	xc     2,bneq
	stl    a,*ar7(0xffff)
	ld     #1,a
	add    *ar7,a
	sub    #1326,a,b
	stl    b,*ar7+
	nop
	xc     2,bneq
	stl    a,*ar7(0xffff)
	bc     0x42b6,bneq
	ld     #1,a
	add    *ar7,a
	sub    #2048,a,b
	stl    b,*ar7+
	nop
	xc     2,bneq
	stl    a,*ar7(0xffff)
	popm   ar7
	ret
