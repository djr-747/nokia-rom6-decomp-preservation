; ROM6 0xDBFA SUB_DBFA -- 30w, symbols.yaml data_word.
; Evidence: Entry 5682 7683 0000 after ret DBF9; callers F274 @DBE9/@DBF0 (same parent); first-RET retd @DC15 cross-chunk (bound DBFA-DC17); HYPOTHESIS.
; ORIGIN 0xDBFA
	.sect ".text"
	.mmregs
	.global _start
_start:
	dld    *ar2,a
	st     #0,*ar3
	and    #1,a,b
	rsbx   st0,tc
	nop
	xc     1,bneq
	ssbx   st0,tc
	and    #4096,16,a,b
	bc     0xdc0b,beq
	xc     1,ntc
	ssbx   st0,tc
	xc     1,tc
	rsbx   st0,tc
	and    #1,a,b
	sfta   a,-1
	xc     2,tc
	or     #-32768,15,a
	banzd  0xdbfd,*ar7-
	or     *ar3,b
	stl    b,1,*ar3
	retd
	dst    a,*ar2
	ld     *ar3,15,a
