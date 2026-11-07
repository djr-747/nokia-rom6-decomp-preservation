; ROM6 0xD365 LEAF_D365 -- 57w, symbols.yaml data_word.
; Evidence: Entry 7313 300D E805 EC27 8293 880E 8205 7605; caller D841 calld; first-RET FC00 @D39D (57w); RPT#39/RPTBD + tmpy, zero subcalls/ports; HYPOTHESIS mpy-loop leaf.
; ORIGIN 0xD365
	.sect ".text"
	.mmregs
	.global _start
_start:
	mvmd   ar3,0x300d
	ld     #5,a
	rpt    #39
	sth    a,*ar3+
	stlm   a,t
	sth    a,0x04
	st     #1,0x05
	st     #2,0x06
	st     #13,0x08
	stm    #4,brc
	rptbd  0xd39c
	st     #7,0x09
	ld     *ar2+,b
	ld     0x09,a
	and    b,a
	stlm   a,ar4
	ld     b,-3,b
	and    0x05,b
	mpy    *ar4(0xfc2c),a
	sfta   a,-1
	add    0x04,a
	stl    a,0x07
	add    0x0d,a
	stlm   a,ar3
	ld     *ar2(0x4),a
	and    0x09,a
	stlm   a,ar4
	ld     #4096,a
	xc     1,bneq
	neg    a
	stl    a,*ar3
	mpy    *ar4(0xfc2c),a
	sfta   a,-1
	add    0x04,a
	sub    0x07,a,b
	add    0x0d,a
	stlm   a,ar4
	ld     *ar3,a
	xc     1,blt
	neg    a
	add    *ar4,a
	stl    a,*ar4
	addm   #1,0x04
	ret
