; ROM6 0x5993 FRAG_5993 -- 73w, symbols.yaml data_word.
; Evidence: Bound 5993-59DB (early cond retd@59BE + tail FE00@59D9 + delays 59DA/59DB, abuts existing SUB_59DC); zero callers; calls F074 59DC@5995 byte-verified; tail via interior bc/bd joins
; ORIGIN 0x5993
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59c
	call   0x59dc
	stm    #9760,ar1
	stm    #9758,ar2
	stm    #466,ar3
	stm    #9761,ar4
	stm    #9762,ar5
	ld     *ar1,a
	ssbx   st1,ovm
	bc     0x59c1,aeq
	addm   #1,*ar1
	sub    #4,a,b
	bc     0x59c6,blt
	bc     0x59ca,beq
	sub    #7,a,b
	bc     0x59d0,blt
	add    *ar5,*ar3+,a
	sth    a,*ar5
	add    *ar4,*ar3,a
	sth    a,*ar4
	bcd    0x59d4,ageq
	st     #4,*ar1
	ld     #0,a
	stl    a,*ar4
	stm    #12034,ar0
	rsbx   st1,ovm
	retd
	st     #176,*ar0
	ld     #1,b
	bd     0x59d4
	stl    b,*ar1
	mvdd   *ar3,*ar5
	bd     0x59d4
	add    *ar3,*ar5,a
	sth    a,*ar5
	ld     *ar3+,a
	add    *ar3,*ar5,b
	bd     0x59d4
	sth    b,*ar4
	stl    a,*ar5
	add    *ar5,*ar3+,a
	sth    a,*ar5
	add    *ar4,*ar3,a
	sth    a,*ar4
	rsbx   st1,ovm
	ld     *ar2,a
	rcd    aeq
	stm    #12034,ar0
	retd
	ld     #0,a
	stl    a,*ar0
