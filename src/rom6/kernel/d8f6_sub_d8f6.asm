; ROM6 0xD8F6 SUB_D8F6 -- 21w, symbols.yaml data_word.
; Evidence: Entry F074 0684 4A07 7707 (opens with call 0x684; 0x0684 is zeros per critic caveat -- overlay/dead- code); first exit ret FC00 @D90A; caller F074 @A96A verified; HYPOTHESIS.
; ORIGIN 0xD8F6
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x684
	pshm   st1
	stm    #1856,st1
	stm    #0,bk
	st     #12424,*(0x300a)
	stm    #12356,ar2
	calld  0xd2e2
	stm    #2504,ar3
	stm    #12355,ar2
	stl    a,*ar2+
	popm   st1
	ret
