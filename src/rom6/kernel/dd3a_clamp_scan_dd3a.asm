; ROM6 0xDD3A CLAMP_SCAN_DD3A -- 51w, symbols.yaml data_word.
; Evidence: Entry E903 8362 890E 7712 0EC5 7713 0062; caller F274 calld @D164 verified; first exit ret FC00 @DD6C; interior bcd bneq DD43->DD6D cond over-exit lane (retd DD74); HYPOTHESIS.
; ORIGIN 0xDD3A
	.sect ".text"
	.mmregs
	.global _start
_start:
	ld     #3,b
	sth    b,0x62
	stlm   b,t
	stm    #3781,ar2
	stm    #98,ar3
	ld     *(0xecb),b
	bcd    0xdd6d,bneq
	stm    #99,ar4
	ld     #94,a
	sub    *ar2,a
	ld     *ar2,b
	add    #368,b
	stl    b,*ar4
	mpy    *ar2+,b
	sub    #105,b
	add    *ar2,b
	xc     2,alt
	mvdd   *ar3,*ar2
	ld     *ar4,b
	stl    b,*ar4
	stm    #3785,ar5
	mar    *ar2-
	ld     *ar2,a
	sub    #5,a
	ld     *ar5+,b
	stm    #3783,ar3
	max    a
	stl    a,*ar3
	ld     #9,a
	add    *ar3+,a
	sub    *ar5,a,b
	stl    a,*ar3
	ld     *ar5,a
	sub    #9,a
	xc     2,bgt
	mvdd   *ar5,*ar3-
	stl    a,*ar3
	ld     *ar4,16,a
	ret
