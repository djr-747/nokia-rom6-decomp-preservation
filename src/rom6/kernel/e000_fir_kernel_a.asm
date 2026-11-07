; ROM6 0xE000 FIR_KERNEL_A -- 42w, symbols.yaml data_word.
; Evidence: Entry 7662 8000 7714 0C4B 7715 FEFA E726 F272 E028; RPTBD MAC chains; first-RET FC00 @E029 (42w); post-RET head, no callers listed (fall-through only); code/data boundary: code end
; ORIGIN 0xE000
	.sect ".text"
	.mmregs
	.global _start
_start:
	st     #-32768,0x62
	stm    #3147,ar4
	stm    #-262,ar5
	mvmm   ar2,ar6
	rptbd  0xe028
	stm    #3145,ar3
	mpy    *ar4-,*ar5,a
	mpy    *ar4,*ar5+,b
	maca   0x63,b
	mpy    *ar3-,*ar5,a
	mac    *ar3+,*ar5+,b
	maca   0x63,b
	mac    *ar2+,*ar5+,b
	mac    *ar2+,*ar5+,b
	mac    *ar2+,*ar5,b
	sfta   b,3
	sth    b,*ar4
	sub    *ar4+,16,b,a
	sth    a,15,*ar4
	sub    0x62,b
	sth    b,*ar6+
	mpy    *ar2-,*ar5-,b
	mac    *ar2-,*ar5-,b
	mac    *ar2+,*ar5-,b
	mpy    *ar4-,*ar5,a
	mac    *ar4+,*ar5-,b
	maca   0x63,b
	mpy    *ar3-,*ar5,a
	mac    *ar3,*ar5,b
	maca   0x63,b
	sfta   b,3
	sth    b,*ar3
	sub    *ar3+,16,b,a
	sth    a,15,*ar3
	sub    0x62,b
	sth    b,*ar6+
	ret
