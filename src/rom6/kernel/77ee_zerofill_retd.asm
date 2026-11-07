; ROM6 0x77EE ZEROFILL_RETD -- 40w, symbols.yaml data_word.
; Evidence: Entry F074 059E; bound 77EE-7815 (FE00 retd@7813 + delays verified); callers 207A/56A0; rptz fills 3AD0/3AD8/3AE0/37E0; HYPOTHESIS.
; ORIGIN 0x77EE
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	cmpm   *(0x250f),#34
	bc     0x780f,ntc
	stm    #15056,ar2
	rptz   a,#3
	stl    a,*ar2+
	stm    #15064,ar2
	rptz   a,#3
	stl    a,*ar2+
	stm    #15072,ar2
	rptz   a,#21
	stl    a,*ar2+
	stm    #14304,ar2
	rptz   a,#21
	stl    a,*ar2+
	stm    #9821,ar2
	mvdk   *ar2,0x34bc
	mvdk   *ar2,0x34bd
	stm    #9802,ar2
	st     #9312,*ar2+
	retd
	st     #9304,*ar2
