; ROM6 0xA615 SUB_A615 -- 36w, symbols.yaml data_word.
; Evidence: Entry F074 065A; bound A615-A638; interior call 3D79 @A633; inbound call @2932 + post-RET A614; HYPOTHESIS.
; ORIGIN 0xA615
	.sect ".text"
	.mmregs
	.global _start
_start:
	call   0x65a
	ld     *(0x565),a
	sub    *(0x915),a
	bc     0xa623,aneq
	ld     *(0x2629),a
	and    #4096,a
	bc     0xa627,aneq
	bitf   *(0x2628),#256
	rc     ntc
	ld     #12,a
	ld     *(0x260e),b
	stm    #3304,ar1
	cmpm   *(0x250f),#34
	bc     0xa633,ntc
	stm    #3554,ar1
	call   0x3d79
	st     #1,*(0x22a)
	ret
