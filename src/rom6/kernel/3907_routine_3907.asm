; ROM6 0x3907 ROUTINE_3907 -- 49w, symbols.yaml data_word.
; Evidence: Entry F074/391F call; interior target 0x391F (entry F110/03CF sub #975; 2x F074 callers 3907/3913); F273 390F/391B are bd branches excluded; first-RET FC00 @0x3937; HYPOTHESIS.
; ORIGIN 0x3907
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x391f
	ld     *(0x3ed4),b
	xc     2,aneq
	ld     *(0x3e7f),b
	stlm   a,ar3
	bd     0x38aa
	ld     *(0x60),a
	call   0x391f
	ld     *(0x3ed5),b
	xc     2,aneq
	ld     *(0x3e80),b
	stlm   a,ar3
	bd     0x38aa
	ld     *(0x60),a
	sub    #975,a,b
	mvdm   0x580,ar3
	xc     2,bgeq
	sub    #1024,a
	stl    a,*(0x60)
	bcd    0x392f,bgeq
	sub    #124,a,b
	nop
	ld     #0,a
	xc     1,bleq
	ld     #1,a
	bitf   *(0x263b),#1
	rc     ntc
	stl    a,*ar3+
	mvmd   ar3,0x580
	ret
