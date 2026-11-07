; ROM6 0xB6E6 PARAM_BUILDER_B6E6 -- 93w, symbols.yaml data_word.
; Evidence: Entry F074 06AA + call 0xBCC8; param block AR2=0x2AF1 gated cmpm 0x2547/0x2546; tail call 0xBA32; first-RET @0xB742 (len 93); 8 callers 53C5 53DF 5416 5428 547F 5498 B56B C8AA; HYP
; ORIGIN 0xB6E6
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x6aa
	call   0xbcc8
	rptz   a,#38
	mvmd   al,0x2aca
	stm    #10993,ar2
	stm    #8720,ar3
	stm    #16149,ar4
	ld     *ar3,-8,a
	stlm   a,t
	cmpm   *(0x2547),#193
	bcd    0xb70d,tc
	ld     *ar3+,16,a
	ld     *ar4,8,b
	cmpm   *(0x2547),#195
	bcd    0xb70d,tc
	ld     *ar3,8,a
	ld     *ar4+,16,b
	cmpm   *(0x2546),#32
	bcd    0xb70d,tc
	ld     *ar3,16,a
	ld     *ar4,8,b
	ld     *ar4,16,b
	and    #255,16,a
	add    #-2,16,a
	sth    a,*ar2+
	and    #255,16,b
	add    a,b
	add    *(0xe),16,b
	add    #4,16,b
	sth    b,*ar2+
	ld     *(0x220e),a
	exp    a
	st     t,*ar2+
	norm   a
	sfta   a,-1
	sth    a,*ar2+
	ld     #16,a
	rpt    #7
	stl    a,*ar2+
	st     #20,*ar2+
	st     #0,*ar2+
	st     #1,*ar2+
	st     #11264,*ar2+
	st     #100,*ar2+
	sth    a,*ar2+
	ld     *(0x220b),a
	rpt    #3
	stl    a,*ar2+
	ld     #0,a
	ld     #1,b
	add    *(0x2af1),b
	stlm   b,brc
	stm    #12056,ar2
	stm    #12206,ar3
	rptb   0xb73f
	stl    a,*ar2+
	stl    a,*ar3+
	call   0xba32
	ret
