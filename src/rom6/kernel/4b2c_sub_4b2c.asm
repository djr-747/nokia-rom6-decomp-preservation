; ROM6 0x4B2C SUB_4B2C -- 59w, symbols.yaml data_word.
; Evidence: Entry F074; bound 4B2C-4B66 (FC00@4B66); callers 2x F274 @4AC0/4AC6 (byte-verified, gap-internal); zero inbound static branches; HYPOTHESIS.
; ORIGIN 0x4B2C
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	stm    #96,ar4
	ld     #-20228,a
	add    *(0x250b),a
	stlm   a,ar4
	ld     *ar2,b
	stl    b,3,*ar3+
	ld     *ar2(0x1),16,b
	or     *ar2+,b
	sth    b,3,*ar3+
	ld     *ar2(0x1),16,b
	or     *ar2+,b
	sth    b,3,*ar3+
	ld     *ar2(0x1),16,b
	or     *ar2+,b
	sfta   b,3
	and    #8191,16,b
	ld     *ar4,16,a
	and    #-8192,16,a
	xor    a,b
	ld     *ar4,a
	and    #127,a
	sth    b,*ar3+
	mvdd   *ar4,*ar3+
	ld     *ar2(0x1),16,b
	or     *ar2+,b
	sfta   b,-3
	and    #-1,7,b
	or     #127,16,a
	xor    a,b
	stl    b,*ar3+
	stm    #2,brc
	rptb   0x4b60
	ld     *ar2(0x1),16,b
	or     *ar2+,b
	sfta   b,-3
	stl    b,*ar3+
	and    #1,16,b
	add    #-16,16,b
	sth    b,*ar3+
	ret
