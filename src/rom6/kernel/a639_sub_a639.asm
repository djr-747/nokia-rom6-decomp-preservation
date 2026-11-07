; ROM6 0xA639 SUB_A639 -- 27w, symbols.yaml data_word.
; Evidence: Entry F074 065C; bound A639-A653; interior call 3D79 @A64B; inbound call @2934 + post-RET A638; HYPOTHESIS.
; ORIGIN 0xA639
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x65c
	bitf   *(0x2628),#8192
	rc     ntc
	ld     #9,a
	ld     *(0x260e),b
	stm    #3244,ar1
	cmpm   *(0x250f),#34
	bc     0xa64b,ntc
	stm    #3456,ar1
	call   0x3d79
	andm   #-3073,*(0x2639)
	orm    #1024,*(0x2639)
	ret
