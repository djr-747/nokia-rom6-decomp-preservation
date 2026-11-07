; ROM6 0x71A3 NORM_SEARCH_MPYA -- 53w, symbols.yaml data_word.
; Evidence: Entry F074 0598; bound 71A3-71D7; callers 758A(d, in 7522)/ABD7(d); ar5-table search 3EA1/3ED6 + neg/norm/mpya; HYPOTHESIS.
; ORIGIN 0x71A3
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x598
	ld     *ar2,b
	bitf   *(0x51f),#128
	bcd    0x71be,ntc
	stm    #16033,ar5
	sub    #975,b,a
	bc     0x71b8,alt
	sub    #1024,b,a
	sub    *ar5+,a
	bd     0x71cb
	stm    #16,t
	sub    #124,b,a
	bc     0x71be,aleq
	stm    #16086,ar5
	sub    *ar5+,b,a
	bcd    0x71cb,aleq
	stm    #16,t
	sub    *ar5+,b,a
	mar    *ar5+
	bc     0x71d7,alt
	b      0x71cd
	neg    a
	mar    *ar5+
	norm   a
	mpya   *ar5
	ld     b,8,a
	add    *ar3,16,a,b
	add    #16384,1,b
	st     #0,*(0xb)
	sth    b,*ar3
	ret
