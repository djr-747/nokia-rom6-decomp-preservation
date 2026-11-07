; ROM6 0x446D DISPATCH_TARGET_D -- 7w, symbols.yaml data_word.
; Evidence: Entry 4913 1084 ldm ar3,b; ld *ar4,a; CALL 4007; 7 words, first-RET FC00 @4473; table-4433 arm; HYPOTHESIS.
; ORIGIN 0x446D
	.sect ".text"
	.mmregs
	.global _start
_start:
	ldm    ar3,b
	ld     *ar4,a
	call   0x4007
	stm    #0,ar6
	ret
