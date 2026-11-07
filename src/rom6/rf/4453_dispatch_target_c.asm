; ROM6 0x4453 DISPATCH_TARGET_C -- 26w, symbols.yaml data_word.
; Evidence: Entry bitf *(0x3EC8)#32 gate, pshm al/ah/ag, CALL 4007 lane; first-RET FC00 @446C; table-4433 arm; HYPOTHESIS.
; ORIGIN 0x4453
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar3,b
	bitf   *(0x3ec8),#32
	bc     0x4463,ntc
	pshm   al
	pshm   ah
	pshm   ag
	sub    #41,b,a
	bc     0x44a6,aeq
	popm   ag
	popm   ah
	popm   al
	stm    #1322,ar5
	rpt    #2
	mvpd   0x44af,*ar5+
	stl    b,*(0x52b)
	call   0x52a
	ret
