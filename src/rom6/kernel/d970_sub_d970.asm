; ROM6 0xD970 SUB_D970 -- 87w, symbols.yaml data_word.
; Evidence: Entry 4A07 7707 0740 EA16; first exit retd FE00 @D9C6 entry-linear; Bound D9C7-D9C8 (RETD@D9C6 delay slots — wave-11 spill fix); callers F074 @5477 + @5490 verified; HYPOTHESIS.
; ORIGIN 0xD970
	.sect ".text"
	.mmregs
	.global _start
_start:
	pshm   st1
	stm    #1856,st1
	ld     #22,dp
	stm    #12414,ar2
	rptz   a,#9
	stl    a,*ar2+
	calld  0xd8e3
	st     #4096,0x58
	stm    #3114,ar2
	ld     #410,a
	rpt    #4
	stl    a,*ar2+
	stm    #3119,ar3
	ld     #1,a
	rpt    #4
	stl    a,*ar3+
	sth    a,0x5b
	st     #4096,0x5c
	sth    a,0x5d
	stl    a,0x5e
	sth    a,0x5f
	sth    a,0x60
	sth    a,0x61
	sth    a,0x62
	ld     #-2381,b
	stm    #3096,ar2
	rpt    #3
	stl    b,*ar2+
	stm    #3100,ar2
	st     #44,*ar2+
	st     #37,*ar2+
	st     #22,*ar2+
	st     #12,*ar2
	stm    #-5218,ar2
	stm    #3104,ar1
	stm    #3124,ar3
	stm    #2864,ar4
	stm    #2884,ar5
	stm    #9,brc
	ld     #0,asm
	ld     *ar2+,16,b
	rptbd  0xd9b7
	stm    #2874,ar6
	sth    a,*ar1+
	sth    b,*ar3+
	sth    b,*ar4+
	sth    b,*ar6+
	st     b,*ar5+ || ld     *ar2+,b
	st     #40,0x65
	sth    a,0x66
	stm    #3134,ar2
	rpt    #9
	sth    a,*ar2+
	calld  0xd9fc
	stm    #12825,ar3
	orm    #1,0x68
	popm   st1
	retd
