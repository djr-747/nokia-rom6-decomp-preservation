; ROM6 0xE144 BLK_E144 -- 40w, symbols.yaml data_word.
; Evidence: Post-RET head; first-RET @E16B (40w); no callers listed; HYPOTHESIS.
; ORIGIN 0xE144
	.sect ".text"
	.mmregs
	.global _start
_start:
	bcd    0xe15a,beq
	stm    #37,brc
	mar    *ar2-
	mpy    *ar5,*ar3-,a
	rptbd  0xe150
	stm    #-2,ar0
	sfta   a,1
	add    *ar2+,16,a
	st     a,*ar2+0% || mpy    *ar3-,a
	sfta   a,1
	add    *ar2+,16,a
	st     a,*ar2- || ld     *ar5-,a
	sth    a,-2,*ar2
	banzd  0xe120,*ar7-
	stm    #-39,ar0
	mar    *ar2-
	mpy    *ar5,*ar3-,a
	rptbd  0xe162
	stm    #-2,ar0
	sfta   a,3
	add    *ar2+,16,a
	st     a,*ar2+0% || mpy    *ar3-,a
	sfta   a,3
	add    *ar2+,16,a
	st     a,*ar2- || ld     *ar5-,a
	sth    a,*ar2
	banzd  0xe120,*ar7-
	stm    #-39,ar0
	ret
