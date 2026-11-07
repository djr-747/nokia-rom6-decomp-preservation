; ROM6 0x2ED6 SAMPLE_COPY_2ED6 -- 123w, symbols.yaml program_word.
; Evidence: Fall-through from 2ecd frag (prev span); andm/xc flag lanes, ldu/stl split-sample copy lanes, rpt/mvdd fills, xc-gated second fill, dispatcher call/b tails; second entry 2F41 (uploaded 9F5D/9F7E callers) rejoins the tail; no other exterior callers, entries evidenced, flagged.
; ORIGIN 0x2ED6
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #1310,ar3
	bitf   *ar2,#1024
	andm   #-513,*ar3
	xc     2,tc
	orm    #512,*ar3
	stm    #1359,ar4
	bitf   *ar2,#512
	orm    #8,*ar4
	xc     2,ntc
	andm   #-9,*ar4
	bitf   *ar2,#256
	nop
	ld     #0,a
	xc     1,tc
	ld     #1,a
	stl    a,*(0x374)
	stm    #875,ar4
	ld     *ar2+%,a
	and    #255,a
	stl    a,*ar4+
	mvdd   *ar2+0%,*ar4+
	ldu    *ar2+%,a
	stl    a,-8,*(0x36d)
	and    #255,a
	stl    a,*(0x36e)
	ldu    *ar2+%,a
	stl    a,-8,*(0x36f)
	and    #255,a
	stl    a,*(0x375)
	ldu    *ar2+%,a
	stl    a,-8,*(0x370)
	and    #255,a
	stl    a,*(0x371)
	ldu    *ar2+%,a
	stl    a,-8,*(0x372)
	and    #255,a
	stl    a,*(0x373)
	stm    #886,ar4
	ld     *(0x36b),a
	sub    #66,a
	rpt    #19
	mvdd   *ar2+0%,*ar4+
	ld     #6,b
	xc     1,aeq
	ld     #30,b
	ld     *(0x36d),a
	sub    *(0x250d),a
	bc     0x2f2a,alt
	add    #1,b
	stl    b,*(0x565)
	stm    #9551,ar3
	stm    #9496,ar4
	rpt    #34
	mvdd   *ar3+,*ar4+
	bitf   *(0x3ec8),#64
	nop
	nop
	xc     2,tc
	rpt    #3
	mvdd   *ar3+,*ar4+
	orm    #256,*(0x2627)
	call   0x2e2f
	b      0x2e64
	orm    #1024,*(0x54f)
	st     #0,*(0x545)
	stm    #907,ar4
	st     #0,*ar4+
	rpt    #3
	mvdd   *ar2+0%,*ar4+
	call   0x2e2f
	b      0x2e64
