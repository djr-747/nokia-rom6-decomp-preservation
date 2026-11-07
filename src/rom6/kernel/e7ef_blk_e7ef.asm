; ROM6 0xE7EF BLK_E7EF -- 29w, symbols.yaml data_word.
; Evidence: Post-RET head; first-RET @E80B (29w); no callers listed; HYPOTHESIS.
; ORIGIN 0xE7EF
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x5b0
	call   0x9ddd
	st     #0,*(0x347f)
	st     #0,*(0x244c)
	st     #0,*(0x3480)
	st     #0,*(0x3b8c)
	st     #0,*(0x3b88)
	st     #0,*(0x3b89)
	calld  0x2262
	stm    #12,ar2
	call   0x5b0
	ret
