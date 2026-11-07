; ROM6 0x457F ROUTINE_457F -- 17w, symbols.yaml data_word.
; Evidence: Bound 457F-458F (17w; exit RET FC00@458F byte-verified); entries cc F945@5D35->457F byte-verified (exterior, other gap) + post-RET head (FC00@457E — pre-word of data-killed 4557-45
; ORIGIN 0x457F
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x594
	ld     *(0x529),-8,b
	and    #255,b
	rc     beq
	stm    #1319,ar3
	stm    #12032,ar4
	rpt    #2
	mvdd   *ar3+,*ar4+
	call   0x4533
	ret
