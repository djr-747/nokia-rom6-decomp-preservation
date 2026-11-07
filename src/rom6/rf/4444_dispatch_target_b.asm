; ROM6 0x4444 DISPATCH_TARGET_B -- 12w, symbols.yaml data_word.
; Evidence: Entry rpt#2 mvpd 4450->AR5 lane, stl b *(0x52B), CALL 052A; first-RET FC00 @444F; table-4433 arm; HYPOTHESIS.
; ORIGIN 0x4444
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar3,b
	stm    #1322,ar5
	rpt    #2
	mvpd   0x4450,*ar5+
	stl    b,*(0x52b)
	call   0x52a
	mar    *ar3+
	ret
