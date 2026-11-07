; ROM6 0x86CF ROUTINE_86CF -- 20w, symbols.yaml data_word.
; Evidence: Bound 86CF-86E2 (20w; exit RET FC00@86E2 byte-verified, exit scan clean); entries call F074@86A2/ 86B6->86CF byte-verified (in SUB_867E — corroborates its inner-call note) + post-R
; ORIGIN 0x86CF
	.sect ".text"
	.mmregs
	.global _start
_start:
	rptz   a,#75
	mvmd   al,0x3090
	stm    #4520,ar2
	rpt    #7
	mvdk   *ar2+,0x3090
	ld     *ar2,a
	stm    #12443,ar2
	stm    #17,ar0
	rpt    #3
	stl    a,*ar2+0
	andm   #-257,*(0x51e)
	ret
