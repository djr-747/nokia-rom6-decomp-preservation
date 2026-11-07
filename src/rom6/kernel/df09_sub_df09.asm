; ROM6 0xDF09 SUB_DF09 -- 155w, symbols.yaml data_word.
; Evidence: Entry 7715 2F00 4A15 4A14 after ret DF08; 6x callers F274 @DE45/DE54/DE63/DE70/DEA2/DEB1; first-RET retd @DFA1 via b DF81 (bound DF09-DFA3); HYPOTHESIS.
; ORIGIN 0xDF09
	.sect ".text"
	.mmregs
	.global _start
_start:
	stm    #12032,ar5
	pshm   ar4
	pshm   ar5
	bcd    0xdf46,tc
	mvdk   0x68,0x1a
	ld     *ar6+,t
	ld     *ar2,16,b
	rptbd  0xdf18
	add    *ar4+0%,*ar2+,a
	mpya   a
	st     a,*ar5+0% || add    *ar4+0%,a
	mpya   a
	st     a,*ar5+0% || ld     *ar2,b
	popm   ar5
	popm   ar4
	mvdk   0x68,0x1a
	mpy    *ar4+,*ar5+,a
	pshm   ar4
	pshm   ar5
	ld     *ar6+,t
	rptbd  0xdf27
	add    *ar4+0%,*ar2-,a
	mpya   a
	st     a,*ar5+0% || add    *ar4+0%,a
	mpya   a
	st     a,*ar5+0% || ld     *ar3,b
	popm   ar5
	popm   ar4
	mvdk   0x68,0x1a
	mpy    *ar4+,*ar5+,a
	pshm   ar4
	pshm   ar5
	ld     *ar7+,t
	rptbd  0xdf36
	add    *ar4+0%,*ar3+,a
	mpya   a
	st     a,*ar5+0% || add    *ar4+0%,a
	mpya   a
	st     a,*ar5+0% || ld     *ar3,b
	popm   ar5
	popm   ar4
	mvdk   0x68,0x1a
	mpy    *ar4+,*ar5+,a
	ld     *ar7+,t
	rptbd  0xdf43
	add    *ar4+0%,*ar3-,a
	mpya   a
	st     a,*ar5+0% || add    *ar4+0%,a
	mpya   a
	b      0xdf81
	ld     *ar6+,a
	neg    a
	stlm   a,t
	ld     *ar2,16,b
	rptbd  0xdf4f
	sub    *ar4+0%,*ar2+,a
	mpya   a
	st     a,*ar5+0% || sub    *ar4+0%,a
	mpya   a
	st     a,*ar5+0% || ld     *ar2,b
	popm   ar5
	popm   ar4
	mvdk   0x68,0x1a
	mpy    *ar4+,*ar5+,a
	pshm   ar4
	pshm   ar5
	ld     *ar6+,a
	neg    a
	stlm   a,t
	rptbd  0xdf60
	sub    *ar4+0%,*ar2-,a
	mpya   a
	st     a,*ar5+0% || sub    *ar4+0%,a
	mpya   a
	st     a,*ar5+0% || ld     *ar3,b
	popm   ar5
	popm   ar4
	mvdk   0x68,0x1a
	mpy    *ar4+,*ar5+,a
	pshm   ar4
	pshm   ar5
	ld     *ar7+,a
	neg    a
	stlm   a,t
	rptbd  0xdf71
	sub    *ar4+0%,*ar3+,a
	mpya   a
	st     a,*ar5+0% || sub    *ar4+0%,a
	mpya   a
	st     a,*ar5+0% || ld     *ar3,b
	popm   ar5
	popm   ar4
	mvdk   0x68,0x1a
	mpy    *ar4+,*ar5+,a
	ld     *ar7+,a
	neg    a
	stlm   a,t
	rptbd  0xdf80
	sub    *ar4+0%,*ar3-,a
	mpya   a
	st     a,*ar5+0% || sub    *ar4+0%,a
	mpya   a
	sth    a,*ar5+0%
	stm    #12032,ar5
	pshm   ar2
	ld     0x68,a
	stlm   a,brc
	add    #1,a
	stl    a,0x69
	stm    #105,ar2
	stm    #26,ar4
	squr   *ar5+,b
	squra  *ar5+,b
	squra  *ar5+,b
	squra  *ar5+,b
	squr   *ar5+,a
	squra  *ar5+,a
	rptbd  0xdf9e
	squra  *ar5+,a
	squra  *ar5+,a
	min    b
	squr   *ar5+,a
	squra  *ar5+,a
	xc     1,nc
	mvdd   *ar4,*ar2
	squra  *ar5+,a
	squra  *ar5+,a
	popm   ar2
	ld     #1,a
	retd
	add    0x68,a
	sub    0x69,a
