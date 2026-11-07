; ROM6 0x4BD7 FILL_2F5D_4BD7 -- 82w, symbols.yaml data_word.
; Evidence: Branch-entered block (0x4BB0 F84C bc 0x4BD7; 0x4BD5 b is PRE-entry not interior, interior exit- branch is 0x4C27); staged fill 4C0D:7712 2F5C + 7692 0000 (stm AR2/st #0,*ar2+) + 77
; ORIGIN 0x4BD7
	.sect ".text"
	.mmregs
	.global _start
_start:
	sub    #193,a,b
	bc     0x4c29,bneq
	stm    #113,ar1
	mvdk   *(0x264c),0x13
	calld  0x5b18
	stm    #12160,ar2
	ld     #2,a
	calld  0x4da7
	stm    #3,ar6
	calld  0x9281
	stm    #12537,ar3
	stm    #12160,ar2
	stm    #11,brc
	rptbd  0x4bf9
	stm    #2504,ar3
	ldu    *ar2+,a
	mvdk   *ar2,0x9
	sfta   a,-3
	stl    a,*ar3+
	andm   #511,*(0x9d3)
	ld     *(0x9d9),a
	stm    #12538,ar2
	stm    #2516,ar3
	calld  0x4f5f
	stm    #4,ar1
	andm   #16383,*(0x9d8)
	orm    #4,*(0x51d)
	stm    #12124,ar2
	st     #0,*ar2+
	stm    #2504,ar3
	rpt    #11
	mvdd   *ar3+,*ar2+
	stm    #12136,ar2
	stm    #12115,ar3
	calld  0x7fdc
	stm    #11,ar1
	calld  0x4f6e
	stm    #12092,ar3
	calld  0x4fc2
	mvmd   ar7,0x2f69
	call   0x4ece
	b      0x4d9c
