; ROM6 0xA654 SUB_A654 -- 37w, symbols.yaml data_word.
; Evidence: Entry F074 065C; bound A654-A678; interior call 4BA8 @A66D + calld 2282 @A66F; inbound call @B3D4 + post-RET A653; HYPOTHESIS.
; ORIGIN 0xA654
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x65c
	cmpm   *(0x2510),#193
	bc     0xa65e,ntc
	st     #0,*(0x9c6)
	ld     *(0x262d),a
	rc     aeq
	sub    #160,a,b
	bc     0xa66c,bneq
	ld     *(0x36d),b
	sub    *(0x250d),b
	sub    #2,b
	rc     bgeq
	ld     #0,b
	call   0x4ba8
	calld  0x2282
	stm    #9,ar2
	cc     0x70c,tc
	st     #0,*(0x262d)
	ret
