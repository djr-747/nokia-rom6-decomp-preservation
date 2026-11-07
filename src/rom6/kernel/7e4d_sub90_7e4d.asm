; ROM6 0x7E4D SUB90_7E4D -- 59w, symbols.yaml data_word.
; Evidence: Entry F074 059E 76F8 2578 0000 7712; BOUND CORRECTED entry-linear: straight-line to first exit retd @0x7E85, bound 7E4D-7E87 (incl delay); was 7EA6 (overclaim); 4 callers F074 @7DC
; ORIGIN 0x7E4D
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	st     #0,*(0x2578)
	stm    #9604,ar2
	stm    #10939,ar3
	stm    #11,ar1
	call   0x7e88
	stm    #9605,ar3
	stm    #10939,ar2
	ld     *ar2,a
	and    #-253,a
	ld     *ar3,b
	sfta   b,2
	and    #252,b
	or     b,a
	stl    a,*ar2+
	stm    #4,brc
	rptb   0x7e6f
	ld     *ar3(0x1),16,a
	or     *ar3,a
	sfta   a,-6
	stl    a,*ar3+
	stm    #3,brc
	rptbd  0x7e80
	stm    #9605,ar3
	ld     *ar3,a
	and    #255,a
	ld     *ar2,b
	or     b,8,a
	stl    a,*ar2+
	ldu    *ar3+,a
	sftl   a,-8
	ld     *ar2,b
	or     b,8,a
	stl    a,*ar2+
	ld     *ar3,a
	and    #255,a
	ld     *ar2,b
	retd
	or     b,8,a
	stl    a,*ar2+
