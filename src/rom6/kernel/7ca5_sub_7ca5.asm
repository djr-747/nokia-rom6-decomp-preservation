; ROM6 0x7CA5 SUB_7CA5 -- 17w, symbols.yaml data_word.
; Evidence: Entry F074 059E 7713 2A87 1084 F010; zero F074/F274 callers full-image; first exit retd FE00 @7CB3 +delays 7CB4-7CB5 entry-linear; bound 7CA5-7CB5; HYPOTHESIS.
; ORIGIN 0x7CA5
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x59e
	stm    #10887,ar3
	ld     *ar4,a
	sub    #4,a
	ld     #512,b
	xc     2,agt
	ld     #1024,b
	or     *ar3,b
	stl    b,*ar3
	retd
	addm   #-1,*ar4
