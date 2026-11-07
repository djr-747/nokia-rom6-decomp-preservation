; ROM6 0x69E4 SUB_69E4 -- 58w, symbols.yaml data_word.
; Evidence: Bound 69E4-6A1D (58w, exit FE00@6A1B + delays); caller F074@5D85 (slice-verified); interior 3x call 0598; HYPOTHESIS.
; ORIGIN 0x69E4
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x598
	stm    #9487,ar2
	ld     #240,a
	and    *ar2,a
	sub    #16,a
	rc     aneq
	cmpm   *ar2,#26
	rc     tc
	cmpm   *(0x2614),#0
	rc     ntc
	cmpm   *(0x53c),#0
	rc     ntc
	ld     *(0x50f),16,a
	sub    #2,16,a,b
	rc     blt
	st     #2,*(0x53c)
	sub    *(0x510),16,a,b
	stm    #9749,ar3
	stm    #1297,ar4
	xc     1,beq
	mvdd   *ar3,*ar4
	mvdd   *ar4,*ar3
	sub    #1,16,a
	sth    a,*(0x50f)
	sub    *(0x510),15,a
	ld     *(0x53d),b
	xc     2,aeq
	add    #1,b
	sub    #41,b,a
	add    #10,b
	xc     1,alt
	ld     b,a
	retd
	stl    a,*(0x53d)
